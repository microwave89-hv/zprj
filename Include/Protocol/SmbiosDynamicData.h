//**********************************************************************//
//**********************************************************************//
//**                                                                  **//
//**        (C)Copyright 1985-2016, American Megatrends, Inc.         **//
//**                                                                  **//
//**                       All Rights Reserved.                       **//
//**                                                                  **//
//**        5555 Oakbrook Pkwy, Suite 200, Norcross, GA 30093         **//
//**                                                                  **//
//**                       Phone: (770)-246-8600                      **//
//**                                                                  **//
//**********************************************************************//
//**********************************************************************//

//**********************************************************************//
// $Header: /Alaska/BIN/Modules/SMBIOS/SmbiosProtocol/SmbiosDynamicData.h 33    4/07/16 5:50p Davidd $
//
// $Revision: 33 $
//
// $Date: 4/07/16 5:50p $
//**********************************************************************//
// Revision History
// ----------------
// $Log: /Alaska/BIN/Modules/SMBIOS/SmbiosProtocol/SmbiosDynamicData.h $
// 
// 33    4/07/16 5:50p Davidd
// [TAG]  		EIP231162
// [Category]  	New Feature
// [Description]  	Merge Aptio V Smbios -09 changes for Aptio 4
// 4.6.5.5_SMBIOS_40 release
// [Files]  		Smbios.sdl
// SmbiosDynamicData.h
// Smbios.h
// SmbiosStaticData.sdl
// SmbiosStaticData.asm
// SmbData.mac
// SmbMacro.aid
// SmbDesc.def
//
// 32    5/29/13 12:47p Davidd
// [TAG]  		EIP124735
// [Category]  	Spec Update
// [Severity]  	Normal
// [Description]  	SMBIOS 2.8.0 specification support for Aptio 4
// [Files]  		Smb.equ
// Smbdata.mac
// Smbdesc.def
// Smbstruc.def
// Smbios.c
// Smbios.h
// SmbiosDynamicData.h
//
// 31    5/23/13 2:37p Davidd
// [TAG]  		    EIP104836
// [Category]  	New Feature
// [Description]  	DMIEdit support edit type 4
// [Files]  		SmbiosBoard.c
//                 SmbiosDMIEditBoard.sdl
//                 Smbios.c
//                 SmbiosDMIEditFunc.c
//                 Smbios.h
//                 SmbiosDynamicData.h
//
// 30    6/16/11 12:28p Davidd
// [TAG]           EIP61776
// [Category]      Improvement
// [Description]   SMBIOS Type 17 "Type Detail" Registered/Unbuffered,
// needs to be dynamically updated
// [Files]         Smbios.sdl
//                 SmbiosDynamicData.h
//                 Smbios.c
//
// 29    5/04/11 3:34p Davidd
// [TAG]           EIP57144
// [Category]      NEW FEATURE
// [Description]   Allow SMBIOS Type 39 to be modified using DMIEdit
// [Files]         SmbiosBoard.c
//                 Smbios.h
//                 SmbiosDynamicData.h
//                 Smbios.c
//                 SmbiosDmieditFunc.c
//                 SmbiosNvramFunc.c
//
// 28    12/08/10 10:57a Davidd
// [TAG]           EIP48952
// [Category]      Improvement
// [Description]   Customer Request for SMBIOS Type 16
// MemoryErrorCorrection field to be filled out
// [Files]
//    Smbios.c
//    SmbiosDynamicData.h
//
// 27    11/19/10 6:19p Davidd
// [TAG]           EIP46175
// [Category]      Improvement
// [Description]   Redesign SMBIOS to avoid redundant SPD reading
// [Files]
//    Smbios.c
//    SmbiosDynamicData.h
//
// 26    11/15/10 3:56p Davidd
// [TAG]           EIP46175
// [Category]      Improvement
// [Description]   Redesign SMBIOS to avoid redundant SPD reading
// [Files]
//    Smbios.c
//    SmbiosDynamicData.h
//
// 25    11/15/10 2:19p Davidd
// [TAG]           EIP46936
// [Category]      Improvement
// [Description]   Generic Smbios module should have the support to
// disable SMBIOS memory update
// [Files]
//    Smbios.c
//    Smbios.sdl
//    SmbiosBoard.c
//    SmbiosDynamicData.h
//
// 24    10/08/10 8:07p Davidd
// [TAG]		EIP43278
//
// [Category]	Function Request
//
// [Severity]	Normal
//
// [Description]	SMBIOS 2.7 requirement
//
// [Files]		Include\Protocol\Smbios.h
// 		Include\Protocol\SmbiosDynamicData.h
// 		Board\EM\SMBIOS\SMBiosStaticData\SmbiosStaticData.sdl
// 		Board\EM\SMBIOS\SMBiosStaticData\SMBDATA.MAC
// 		Board\EM\SMBIOS\SMBiosStaticData\SMBSTRUC.DEF
// 		Board\EM\SMBIOS\SMBiosStaticData\SMBMACRO.AID
// 		Board\EM\SMBIOS\SMBiosStaticData\Smbdesc.def
// 		Board\EM\SMBIOS\SMBiosStaticData\SMB.EQU
//
// 23    6/02/09 3:52p Davidd
// Updated AMI headers (EIP 22180)
//
// 22    5/19/09 11:01a Davidd
// Changes added to improve memory type 17 porting (EIP 22241).
//
// 21    12/30/08 3:15p Davidd
// Fixed the hanging problem when only SMBIOS binary component is present
// (ref. EIP 18370)
//
// 20    11/14/08 4:42p Davidd
// - Added OemUpdate protocol
//
// 19    10/23/08 6:21p Davidd
// Added changes to support SMBIOS version 2.5 and 2.6.
//
// 18    2/22/08 10:20a Davidd
// Simplified the way the number of memory slots for each physical memory
// array are defined.
//
// 17    2/06/08 3:44p Davidd
// Added NumberOfBatteries field to _EFI_SMBIOS_BOARD_PROTOCOL to hold the
// number of batteries in the system.
//
// 16    2/01/08 11:57a Davidd
// Changes made to support SMBIOS type 17 with multiple memory arrays.
//
// 15    12/17/07 12:20p Davidd
// Added PORTABLE_BATTERY_INFO to EFI_SMBIOS_BOARD_PROTOCOL
//
// 14    11/26/07 5:53p Davidd
// Changes added to dynamically update the Processor Information Type 4.
//
// 13    11/21/07 10:38a Davidd
// Added dynamic data update support for Portable Battery Data structure
// 22.
//
// 12    9/12/07 2:26p Davidd
// Added changes to set memory type and speed to unknown for unoccupied
// memory slot.
//
// 11    6/05/07 4:18p Michaela
// Added AMI_SMBIOS_CPU_INFO_PROTOCOL for dynamic
// updating of CPU information
//
// 10    3/29/07 4:05p Davidd
// Made change to the year in the AMI banner
//
// 9     3/21/07 4:01p Michaela
// Added MemErrInfoHandle field in MEMORY_DEVICE
// structure typedef
//
// 8     12/15/06 1:15p Davidd
// Code cleanup and reformatted to coding  standard.
//
// 7     3/02/06 10:35a Davidd
// Commented out fields deemed to be static.
//
// 6     7/27/05 1:25p Davidd
// Removed conditional compilation switches and added them to
// SmbiosBoardProtocol.
//
// 5     7/18/05 6:07p Davidd
// Added protocol definition for creating the dynamic data.
//
// 4     7/13/05 5:35p Davidd
// Added Processor Manufacturer and Processor Version fields.
//
// 3     7/05/05 12:17p Davidd
// Made SMBIOS variables static so that it can be shared in different
// files.
//
// 2     6/21/05 12:08p Davidd
// Corrected build error.
//
// 1     5/02/05 3:23p Davidd
// Initial Check-in.
//
// 1     4/29/05 2:12p Davidd
// Initial checkin.
//
//**********************************************************************//

#ifndef _SMIBios_Dynamic_H
#define _SMIBios_Dynamic_H

#include <Token.h>
#include <AmiHobs.h>
#include <Protocol/SmBus.h>

#if SMBIOS_SUPPORT
#define EFI_SMBIOS_DYNAMIC_DATA_GUID \
    {0xe380280c, 0x4c35, 0x4aa3, { 0xb9, 0x61, 0x7a, 0xe4, 0x89, 0xa2, 0xb9, 0x26 }}

#define EFI_SMBIOS_BOARD_PROTOCOL_GUID \
    {0x903dd14, 0x2ca0, 0x458a, 0xb5, 0xeb, 0xc, 0xc, 0xa3, 0xd, 0x78, 0x5c}

#define EFI_MEMORY_SUBCLASS_DRIVER_GUID \
  { 0x1767CEED, 0xDB82, 0x47cd, 0xBF, 0x2B, 0x68, 0x45, 0x8A, 0x8C, 0xCF, 0xFF }

#define EFI_MEMORY_SUBCLASS_GUID \
   {0x4E8F4EBB, 0x64B9, 0x4e05, 0x9B, 0x18, 0x4C, 0xFE, 0x49, 0x23, 0x50, 0x97}

// {3D6CDB0A-5B1F-43a3-A43B-441267F9DAB5}
#define AMI_SMBIOS_CPU_INFO_PROTOCOL_GUID \
    {0x3d6cdb0a, 0x5b1f, 0x43a3, 0xa4, 0x3b, 0x44, 0x12, 0x67, 0xf9, 0xda, 0xb5}

#define MAX_NUMBER_OF_MEM_MODULE A1_MEMORY_SOCKETS
#if NO_OF_PHYSICAL_MEMORY_ARRAY >= 2
    #if A2_MEMORY_SOCKETS > MAX_NUMBER_OF_MEM_MODULE
        #undef MAX_NUMBER_OF_MEM_MODULE
        #define MAX_NUMBER_OF_MEM_MODULE A2_MEMORY_SOCKETS
    #endif
#endif
#if NO_OF_PHYSICAL_MEMORY_ARRAY >= 3
    #if A3_MEMORY_SOCKETS > MAX_NUMBER_OF_MEM_MODULE
        #undef MAX_NUMBER_OF_MEM_MODULE
        #define MAX_NUMBER_OF_MEM_MODULE A3_MEMORY_SOCKETS
    #endif
#endif
#if NO_OF_PHYSICAL_MEMORY_ARRAY == 4
    #if A4_MEMORY_SOCKETS > MAX_NUMBER_OF_MEM_MODULE
        #undef MAX_NUMBER_OF_MEM_MODULE
        #define MAX_NUMBER_OF_MEM_MODULE A4_MEMORY_SOCKETS
    #endif
#endif

static CHAR16 *SmbiosBaseBoardVar = L"BASEBOARD DATA";
static CHAR16 *SmbiosChassisVar = L"CHASSIS DATA";
static CHAR16 *SmbiosCpuVar = L"CPU DATA";
static CHAR16 *SmbiosSlotsVar = L"SLOTS DATA";
static CHAR16 *SmbiosOnBoardVar = L"ONBOARD DEV DATA";
static CHAR16 *SmbiosMemVar = L"MEMORY DATA";
static CHAR16 *SmbiosBatteryVar = L"BATTERY DATA";
static CHAR16 *SmbiosOnBoardExtVar = L"ONBOARD DEV EXTENDED DATA";

#pragma pack(1)

//**********************************************************************//
// Base Board Structure
//**********************************************************************//
#if BASE_BOARD_INFO
typedef struct {                                        // Type 2
    CHAR8          *BoardManufacturer;
    CHAR8          *BoardName;
} BASE_BOARD_DATA;
#endif //BASE_BOARD_INFO

//**********************************************************************//
// Chassis Structure
//**********************************************************************//
#if SYS_CHASSIS_INFO
typedef struct {                                        // Type 3
    UINT8                     Type;
} CHASSIS_DATA;
#endif //SYS_CHASSIS_INFO

//**********************************************************************//
// CPU Structure
//**********************************************************************//

typedef struct {                                        // Type 4
    UINT8                     Family;                   // 3.3.5.2
    UINT32                    ProcessorID_1;            // 3.3.5.3 - 1st DWORD
    UINT32                    ProcessorID_2;            // 3.3.5.3 - 2nd DWORD
    UINT8                     Voltage;                  // 3.3.5.4
    UINT16                    ExtClockFreq;             // in MHz
    UINT16                    MaxSpeed;                 // in MHz
    UINT16                    CurrentSpeed;             // in MHz
    UINT8                     Status;                   // pg 43
    UINT8                     Upgrade;                  // 3.3.5.5
    UINT8                     Manufacturer[18];
    UINT8                     Version[48];
    UINT8                     CoreCount;                // 3.3.5.6
    UINT8                     CoreEnabled;              // 3.3.5.7
    UINT8                     ThreadCount;              // 3.3.5.8
    UINT16                    Family2;                  // 3.3.5.2
} CPU_DATA;

typedef struct {                                        // Type 7
    UINT16                    CacheConfig;              // pg 52
    UINT16                    MaxCacheSize;             // pg 52
    UINT16                    InstalledSize;            // pg 52
    UINT16                    SupportSRAM;              // 3.3.8.1
    UINT16                    CurrentSRAM;              // 3.3.8.1
    UINT8                     CacheSpeed;               // in nS
    UINT8                     ErrorCorrectionType;      // 3.3.8.2
    UINT8                     SystemCacheType;          // 3.3.8.3
    UINT8                     Associativity;            // 3.3.8.4
} CACHE_DATA;

typedef struct {                                        // One for each CPU
    CPU_DATA                  CpuData;
    CACHE_DATA                L1Cache;
    CACHE_DATA                L2Cache;
    CACHE_DATA                L3Cache;
} SINGLE_CPU_DATA;

typedef struct {                                        // CPU data structure
    UINT8                     NumberCPU;
    SINGLE_CPU_DATA           CpuData[NO_OF_PROCESSOR_SOCKETS];
} CPU_DYNAMIC_DATA;

typedef CPU_DYNAMIC_DATA SMBIOS_CPU_INFO_PROTOCOL;

//**********************************************************************//
// Slot Structure
//**********************************************************************//

typedef struct {                                        // Type 9
    UINT8                     CurrentUsage[NUMBER_OF_SYSTEM_SLOTS];             // 3.3.10.3
    UINT8                     BusNumber[NUMBER_OF_SYSTEM_SLOTS];
} SYSTEM_SLOT_DYNAMIC_DATA;

//**********************************************************************//
// On-Board Device Structure
//**********************************************************************//

#if ONBOARD_DEVICE_INFO
typedef struct {                                        // Type 10
    UINT8                     OnBoardDev[NUMBER_OF_ONBOARD_DEVICES];            // 3.3.11.1
} ONBOARD_DEV_DYNAMIC_DATA;
#endif

//**********************************************************************//
// Memory Structure
//**********************************************************************//

typedef struct {                                        // Type 18
    UINT8                     ErrorType;                // 3.3.19.1
    UINT8                     ErrorGranularity;         // 3.3.19.2
    UINT8                     ErrorOperation;           // 3.3.19.3
    UINT32                    MemArrayErrorAddress;     // 32-bit physical address (8000 0000h if unknown)
    UINT32                    DeviceErrorAddress;       // 32-bit physical address (8000 0000h if unknown)
    UINT32                    ErrorResolution;          // in bytes
} MEM_ERROR;

typedef struct {                                        // Type 19
    UINT32                    StartingAddress;          // in KB
    UINT32                    EndingAddress;            // in KB
    UINT8                     PartitionWidth;           //
    UINT64                    ExtendedStartAddr;        // in bytes
    UINT64                    ExtendedEndAddr;          // in bytes
} MEM_ARRAY_MAP_ADDR;

#if MEMORY_DEVICE_INFO
typedef struct {                                        // Type 20
    UINT32                    StartingAddress;          // in KB
    UINT32                    EndingAddress;            // in KB
    UINT8                     PartitionRowPosition;     //
    UINT8                     InterleavePosition;       //
    UINT8                     InterleaveDataDepth;      //
    UINT64                    ExtendedStartAddr;        // in bytes
    UINT64                    ExtendedEndAddr;          // in bytes
} MEM_DEV_MAP_ADDR;
#endif

typedef struct {                                        // Type 17
    UINT16                    MemErrInfoHandle;         // Type 18
    UINT16                    TotalWidth;               // in bits (FFFFh if unknown)
    UINT16                    Size;                     // FFFFh if unknown, 7FFFh if size is >= 32GB - 1MB
    UINT8                     DeviceSet;                //
    UINT8                     MemoryType;               //
    UINT16                    Speed;                    // in MHz
    UINT32                    ExtendedSize;             // in megabytes when Size field = 7FFFh, 0 otherwise
    UINT16                    ConfMemClkSpeed;          // in MHz, 0 if unknown
    UINT16                    TypeDetail;               //
    UINT16                    MinimumVoltage;           // Minimum operating voltage in millivolts, 0 if unknown
    UINT16                    MaximumVoltage;           // Maximum operating voltage in millivolts, 0 if unknown
    UINT16                    ConfiguredVoltage;        // Configured voltage in millivolts, 0 if unknown
} MEMORY_DEVICE;

typedef struct {
    MEMORY_DEVICE             Type17;                   // Type 17
    MEM_ERROR                 Type18;                   // Type 18
#if MEMORY_DEVICE_INFO
    MEM_DEV_MAP_ADDR          Type20;                   // Type 20
#endif
} MEMORY_DEVICE_GROUP;

typedef struct {                                        // Type 16
    UINT32                    MaxCapacity;              // in KB (8000 0000h if unknown)
    UINT16                    MemErrInfoHandle;         // Type 18
    MEM_ERROR                 ArrayMemoryError;         // Type 18
    MEM_ARRAY_MAP_ADDR        MemArrayMapAddr;          // Type 19
    MEMORY_DEVICE_GROUP       MemoryDeviceData[MAX_NUMBER_OF_MEM_MODULE];           // Type 17 group
    EFI_SMBUS_DEVICE_ADDRESS  SpdSmBusAddr[MAX_NUMBER_OF_MEM_MODULE];
    UINT64                    ExtMaxCapacity;           // in Bytes when MaxCapacity = 8000 0000h, 0 otherwise
} PHYSICAL_MEM_ARRAY;

typedef struct {
    PHYSICAL_MEM_ARRAY        PhysicalMemArray[NO_OF_PHYSICAL_MEMORY_ARRAY];
} SYSTEM_MEM_ARRAY_DYNAMIC_DATA;

#ifndef AMI_SMBIOS_MEMORY_INFO_HOB_GUID
  #define AMI_SMBIOS_MEMORY_INFO_HOB_GUID \
    {0x7d6b8734, 0xb754, 0x443f, { 0xb5, 0x88, 0x77, 0x43, 0x84, 0x3a, 0xd3, 0xf1 }}
#endif

typedef struct {
    UINT8 Byte2;                                        // Memory Type
    UINT8 Byte5To8[9 - 5];                              // Attribute, Total Width, Data Width (DDR2 & 3)
    UINT8 Byte11To14[15 - 11];                          // ECC Data Width, Data Width (DDR4)
    UINT8 Byte64To71[72 - 64];                          // Manufacturer (DDR2)
    UINT8 Byte73To90[91 - 73];                          // Part Number (DDR2)
    UINT8 Byte95To98[99 - 95];                          // Serial Number (DDR2)
    UINT8 Byte117To118[119 - 117];                      // Manufacturer (DDR3)
    UINT8 Byte122To125[126 - 122];                      // Serial Number (DDR3)
    UINT8 Byte128To145[146 - 128];                      // Part Number (DDR3)
    UINT8 Byte320To321[322 - 320];                      // Manufacturer (DDR4)
    UINT8 Byte325To328[329 - 325];                      // Serial Number (DDR4)
    UINT8 Byte329To348[349 - 329];                      // Part Number (DDR4)
} MEM_SPD_DATA;

//**********************************************************************//
// SPD data needed from NB driver
//**********************************************************************//
//typedef struct {
//	  EFI_HOB_GUID_TYPE           EfiHobGuidType;
//    MEM_SPD_DATA                SpdDataArray[NO_OF_PHYSICAL_MEMORY_ARRAY][MAX_NUMBER_OF_MEM_MODULE];
//} AMI_SMBIOS_MEMORY_INFO_HOB;

//**********************************************************************//
// Portable Battery Structure
//**********************************************************************//

#if PORTABLE_BATTERY_INFO
typedef struct {                                        // One for each Portable Battery
        UINT8                   DeviceName[65];
        UINT16                  DesignCapacity;
        UINT16                  DesignVoltage;
        UINT8                   SbdsVersion[65];
        UINT16                  SbdsSerialNumber;
        UINT16                  SbdsManufacturedDate;
        UINT8                   DesignCapacityMult;
        BOOLEAN					Valid;
} SMBIOS_PORTABLE_BATTERY_DYNAMIC_INFO;

typedef struct {                                        // Type 22
  SMBIOS_PORTABLE_BATTERY_DYNAMIC_INFO  BatteryDynamicData[NO_OF_PORTABLE_BATTERY];
} BATTERY_DYNAMIC_DATA;
#endif

//**********************************************************************//
// On-Board Device Extended Information Structure
//**********************************************************************//

#if ONBOARD_DEVICE_EXTENDED_INFO
typedef struct {                                        // Type 41
    UINT8                     OnBoardDev[ONBOARD_DEVICE_EXT_COUNT];            // 3.3.42
    UINT8                     BusNumber[ONBOARD_DEVICE_EXT_COUNT];
} ONBOARD_DEV_EXT_DYNAMIC_DATA;
#endif

#pragma pack()

typedef struct _EFI_SMBIOS_BOARD_PROTOCOL  EFI_SMBIOS_BOARD_PROTOCOL;

typedef EFI_STATUS (EFIAPI *EFI_SMBIOS_CREATE_BASE_BOARD_DATA_STRUCTURE) (
);

typedef EFI_STATUS (EFIAPI *EFI_SMBIOS_CREATE_CHASSIS_DATA_STRUCTURE) (
);

typedef EFI_STATUS (EFIAPI *EFI_SMBIOS_CREATE_CPU_DATA_STRUCTURE) (
);

typedef EFI_STATUS (EFIAPI *EFI_SMBIOS_CREATE_SYSTEM_SLOT_DATA_STRUCTURE) (
);

typedef EFI_STATUS (EFIAPI *EFI_SMBIOS_CREATE_ONBOARD_DEV_DATA_STRUCTURE) (
);

typedef EFI_STATUS (EFIAPI *EFI_SMBIOS_CREATE_BATTERY_DEV_DATA_STRUCTURE) (
);

typedef EFI_STATUS (EFIAPI *EFI_SMBIOS_CREATE_ONBOARD_DEV_EXT_STRUCTURE) (
);
typedef EFI_STATUS (EFIAPI *EFI_SMBIOS_ENABLE_SMBUS_CONTROLLER) (
);
typedef EFI_STATUS (EFIAPI *EFI_SMBIOS_RESTORE_SMBUS_CONTROLLER) (
);
typedef EFI_STATUS (EFIAPI *EFI_SMBIOS_READ_SPD) (
);
typedef VOID (EFIAPI *EFI_SMBIOS_OEM_UPDATE) (
);

typedef struct _EFI_SMBIOS_BOARD_PROTOCOL {
    UINT8                                           BaseBoardInfoSupport;
    UINT8                                           SysChassisInfoSupport;
    UINT8                                           ProcessorDmiEditSupport;
    UINT8                                           OemStringInfoSupport;
    UINT8                                           SystemConfigOptionInfoSupport;
    UINT8                                           MemoryErrorInfoSupport;
    UINT8                                           OnboardDeviceInfoSupport;
    UINT8                                           PortableBatteryInfoSupport;
    UINT8                                           AdditionalInfoSupport;
    UINT8                                           OnboardDeviceExtInfoSupport;
    UINT8                                           SystemPowerSupplyInfoSupport;
    UINT8                                           NumberOfCPU;
    UINT8                                           NumberOfSystemSlots;
    UINT8                                           NumberOfOnBoardDevices;
    UINT8                                           NumberOfPhysicalMemoryArray;
    UINT8                                           NumberOfBatteries;
    UINT8                                           NumberOfOnboardDevExt;
    EFI_SMBIOS_CREATE_BASE_BOARD_DATA_STRUCTURE     SmbiosCreateBaseBoardData;      // Create Base Board dynamic data
    EFI_SMBIOS_CREATE_CHASSIS_DATA_STRUCTURE        SmbiosCreateChassisData;        // Create Chassis dynamic data
    EFI_SMBIOS_CREATE_CPU_DATA_STRUCTURE            SmbiosCreateCPUData;            // Create CPU dynamic data
    EFI_SMBIOS_CREATE_SYSTEM_SLOT_DATA_STRUCTURE    SmbiosCreateSystemSlotData;     // Create system slot dynamic data
    EFI_SMBIOS_CREATE_ONBOARD_DEV_DATA_STRUCTURE    SmbiosCreateOnBoardDevData;     // Create on-board device dynamic data
    EFI_SMBIOS_CREATE_BATTERY_DEV_DATA_STRUCTURE    SmbiosCreateBatteryDevData;     // Create Portable Battery device dynamic data
    EFI_SMBIOS_CREATE_ONBOARD_DEV_EXT_STRUCTURE     SmbiosCreateOnBoardDevExtInfo;
    EFI_SMBIOS_ENABLE_SMBUS_CONTROLLER              EnableSmbusController;
    EFI_SMBIOS_RESTORE_SMBUS_CONTROLLER             RestoreSmbusController;
    EFI_SMBIOS_READ_SPD                             GetSpdByte;
    EFI_SMBIOS_OEM_UPDATE                           OemUpdate;
    UINT8                                           NumberOfMemorySlots[NO_OF_PHYSICAL_MEMORY_ARRAY];
};

EFI_STATUS CreateBaseBoardDataForSMBios();
EFI_STATUS CreateChassisDataForSMBios();
EFI_STATUS CreateCPUDataForSMBios();
EFI_STATUS CreateSlotDataForSMBios();
EFI_STATUS CreateOnBoardDevDataForSMBios();
EFI_STATUS CreateBatteryDataForSMBios();
EFI_STATUS CreateOnBoardDevExtInfoForSMBios();
EFI_STATUS EnableSmbusController();
EFI_STATUS RestoreSmbusController();
EFI_STATUS GetSpdByte();
VOID       OemUpdate();

#endif    // if SMBIOS_SUPPORT

#endif

//**********************************************************************//
//**********************************************************************//
//**                                                                  **//
//**        (C)Copyright 1985-2016, American Megatrends, Inc.         **//
//**                                                                  **//
//**                       All Rights Reserved.                       **//
//**                                                                  **//
//**        5555 Oakbrook Pkwy, Suite 200, Norcross, GA 30093         **//
//**                                                                  **//
//**                       Phone: (770)-246-8600                      **//
//**                                                                  **//
//**********************************************************************//
//**********************************************************************//
