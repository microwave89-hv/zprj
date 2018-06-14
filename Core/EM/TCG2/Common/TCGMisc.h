//**********************************************************************
//**********************************************************************
//**                                                                  **
//**        (C)Copyright 1985-2013, American Megatrends, Inc.         **
//**                                                                  **
//**                       All Rights Reserved.                       **
//**                                                                  **
//**     5555 Oakbrook Pkwy, Suite 200, Norcross, GA 30093            **
//**                                                                  **
//**                       Phone: (770)-246-8600                      **
//**                                                                  **
//**********************************************************************
//**********************************************************************
//**********************************************************************
// $Header: /Alaska/SOURCE/Modules/TCG2/CommonHeaders/TCGMisc.h 2     6/11/14 4:13p Fredericko $
//
// $Revision: 2 $
//
// $Date: 6/11/14 4:13p $
//**********************************************************************
// Revision History
// ----------------
// $Log: /Alaska/SOURCE/Modules/TCG2/CommonHeaders/TCGMisc.h $
// 
// 2     6/11/14 4:13p Fredericko
// [TAG]  		EIP173073
// [Category]  	Bug Fix
// [Severity]  	Important
// [Symptom]  	PPI operations will fail
// [RootCause]  	EFI spec changes requires that only industry variables
// should use EfiGlobalVariableGuid
// [Solution]  	REF-28609.V2: Clear The TPM via OS test fail /1AQPM037
// (TPM1.2)
// [Files]  		TcgMisc.h
// 
// 1     4/21/14 2:15p Fredericko
// 
// 1     10/08/13 11:59a Fredericko
// Initial Check-In for Tpm-Next module
// 
// 2     8/30/13 11:06p Fredericko
// 
// 1     7/10/13 5:58p Fredericko
// [TAG]  		EIP120969
// [Category]  	New Feature
// [Description]  	TCG (TPM20)
// 
// 34    3/29/13 9:45p Fredericko
// [TAG]  		EIP113715
// [Category]  	Improvement
// [Description]  	Please update the copyright header according to AMI
// copyright rule
// [Files]  		Multiple Files
// 
// [TAG]  		EIP109597
// [Category]  	Improvement
// [Description]  	Add a switch for TPM PPI flag access via BIOS NVRAM
// [Files]  		TCGMisc.h, AmiTcgNvflagSample.c, 
// 
// [TAG]  		EIP118211
// [Category]  	Improvement
// [Description]  	Implement ability to skip Physical presence lock in
// manufacturing mode
// [Files]  		TcgPei.c,  AmiTcgPlatformDxe.c, AmiTcgNvflagSample.c
// 
// 33    11/30/12 7:20p Fredericko
// [TAG]  		EIP104949
// [Category]  	Bug Fix
// [Severity]  	Minor
// [Symptom]  	UEFI 2.3.1 SCT test failed in Generic\EfiCompliant case.
// TpmOldvar is not defined in the Spec.
// 
// 32    5/20/12 2:08p Fredericko
// 
// 31    4/19/12 8:04p Fredericko
// Add Fastboot GUID definition for Internal use
// 
// 30    3/19/12 6:19p Fredericko
// Changes for TcgPerformance Metrics Improvement. 
// Files Changed: Tcg.sdl, TcgMisc.h, TcgDxe.c, TcgCommon.c, TcgCommon.h, 
// AmiTcgPlatformPeiLib.c, AmiTcgPlatformDxe.c, TcgDxe.dxs
// 
// 29    2/03/12 5:11p Fredericko
// [TAG]  		EIP81665
// [Category]  	Improvement
// [Description]  	Support for MOR feature improvement
// [Files]  		Tcg.sdl, AmiTcgPlatformDxe.c, Tcgdxe.c, Tcglegacy.c
// 
// 28    1/17/12 11:22a Fredericko
// Install Tpm_Initialized Ppi in PEI
// 
// 27    11/01/11 4:15a Fredericko
// Fixed spelling changes request for physicalPresenceLock and
// bGlobalLock.
// 
// 26    8/26/11 12:53p Fredericko
// [TAG]  		EIP65710 
// [Category]  	Bug Fix
// [Severity]  	Minor
// [Symptom]  	Wrong structure for TPM and TCM permanent flags
// [RootCause]  	Lower part of structure was not defined properly since we
// don't use them in BIOS
// [Solution]  	Update structure in TcgMisc.h
// [Files]  		TcgMisc.h
// 
// 25    8/09/11 6:13p Fredericko
// [TAG]  		EIP65605
// [Category]  	Bug Fix
// [Severity]  	Minor
// [Symptom]  	None
// [RootCause]  	Tpm Permanent flags Structure needs to be updated
// [Solution]  	Updated the Tpm Permanent Flags structure
// [Files]  		TcgMisc.h
// 
// 24    7/24/11 10:05p Fredericko
// [TAG]  		EIP65177
// [Category]  	Spec Update
// [Severity]  	Minor
// [Description]  	Included sample  protocoldefinition to read and set
// persistent BIOS flags.
// 2. Also include defines for new smi transactions for Ppi.
// 
// 23    4/06/11 6:46p Fredericko
// PPI confirmation Override changes
// 
// 22    4/01/11 10:50a Fredericko
// Added TCG legacy GUID for initializing the TPM in legacy mode
// 
// 21    3/29/11 12:25p Fredericko
// 
// 20    3/28/11 12:22p Fredericko
// [TAG]        EIP 54642
// [Category] Improvement
// [Description] 1. Checkin Files related to TCG function override
// 2. Include TCM and TPM auto detection
// [Files] Affects all TCG files
// 
// 17    8/04/10 5:21p Fredericko
// Added #defines for TCG SMI transactions
// 
// 16    7/09/10 3:26p Fredericko
// EFI_NULL GUID defined
// 
// 15    5/19/10 5:18p Fredericko
// Included File Header
// Code Beautification
// EIP 37653
//
// 14    3/25/10 7:13p Fredericko
// Function definition for ResetPPI variables added
//
// 13    3/23/10 8:40p Fredericko
//
// 12    3/19/10 4:13p Fredericko
// Generic guid defined for legacy MA Driver, Legacy MP driver and TCG
// driver hobs
// Also modified structures Far32Locals, MAStruct, ESPFuncStruc
//
// 11    1/14/10 11:43a Fredericko
// Added TCG NVRAM structure  and guid definitions.
//
// 10    12/03/09 6:23p Fredericko
// added UEFI guid definition for MOR
//
// 9     6/08/09 4:35p Fredericko
// typedefs for STANY_FLAGS
//
// 8     6/01/09 3:54p Fredericko
// changes for TCM support.
//
// 7     4/30/09 6:13p Fredericko
// Updated Header Date
//
// 6     4/30/09 5:30p Fredericko
// AMI company Header Address changes
//
// 5     3/05/09 2:02p Fredericko
// Changes for CoreSources dependency
//
// 4     2/05/09 4:54p Fredericko
// Generic TCG structures added and GUIDs added in favor of building
// without EDK.
//
// 3     26/08/08 10:44a Anandakrishnanl
// Added Sdl Token for the define Equates and Changed the Corresponding
// Codes
//
// 2     2/27/08 5:50p Fredericko
// TCG structures included
//
// 1     7/23/07 10:24a Fredericko
//*************************************************************************
//<AMI_FHDR_START>
//
// Name:  TcgMisc.h
//
// Description: 
//  Miscellaneous Tcg Header file
//
//<AMI_FHDR_END>
//*************************************************************************
//------------------------------------------------------------------------------
//                OEM INFO for TCG structures(Port OEM info)
//------------------------------------------------------------------------------
#ifndef  _TCGMISC_H   //To Avoid this header get compiled twice
#define  _TCGMISC_H
#include <EFI.h>

#define EV_SPECIFICATION_IDENTIFIER        (UINT32)0x000000012
//--------------------AMI_PORTING----------------------------------------------
#define TCG_BIOS_VENDOR           "AMI"
#define TCG_OEM_ID               "ALASKA"
//-----------------------------------------------------------------------------
#define EFI_TCG_WAKE_EVENT_DATA_HOB_GUID \
    {0xBBB810BB, 0x5EF0, 0x4E8F, 0xB2, 0x98, 0xAD, 0x74, 0xAA, 0x50, 0xEF, 0x0A}

#define TCG_EFI_HOB_LIST_GUID \
    { 0x7739f24c, 0x93d7, 0x11d4, 0x9a, 0x3a, 0x0, 0x90, 0x27, 0x3f, 0xc1, 0x4d}

#define EFI_TCG_LOG_HOB_GUID \
    {0x5f7d4e0e, 0x3d6d, 0x42bc, 0xa9, 0x42, 0xe, 0x91, 0xe8, 0x3e, 0x3c, 0x31}

#define AMI_TCG_EFI_OS_VARIABLE_GUID \
    {0xa8a2093b, 0xfefa, 0x43c1, 0x8e, 0x62, 0xce, 0x52, 0x68, 0x47, 0x26, 0x5e}

#define AMI_TCG_RESETVAR_HOB_GUID \
    {0xa8a2093b, 0xfefa, 0x43c1, 0x8e, 0x62, 0xce, 0x52, 0x68, 0x47, 0x26, 0x5e}

#define AMI_TCG_MANUFACTURING_MODE_HOB_GUID \
    {0x5d7f83ee, 0x88e5, 0x4ea8, 0xbe, 0xe8, 0x23, 0x79, 0xa6, 0x3c, 0xff, 0x8}

#define AMI_TCG_CONFIRMATION_FLAGS_GUID \
    {0x7d3dceee, 0xcbce, 0x4ea7, 0x87, 0x09, 0x6e, 0x55, 0x2f, 0x1e, 0xdb, 0xde}

#define AMI_TCG_PERM_FLAGS_GUID \
    {0x2325f2fc, 0x5683, 0x4648, 0x97, 0xc4, 0x9a, 0x52, 0x0d, 0xfb, 0xe3, 0x25}

#define EFI_NULL_GUID \
	{0x00000000, 0x0000, 0x0000, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00}

#define TCG_EFI_GLOBAL_VARIABLE_GUID \
    { \
         0x135902e7, 0x9709, 0x4b41, 0x8f, 0xd2, 0x40, 0x69, 0xda, 0xf0, 0x54,\
        0x6a \
    }

#define TCG_VARIABLE_GUID \
    {0x9868b77b, 0x607e, 0x4cb7, 0xa6, 0xce, 0xe1, 0xd5, 0x29, 0xd4, 0x41, 0x64}

#define EFI_TCM_MPDriver_GUID \
    { 0x3EB9F0D3, 0x40D0, 0x435b, 0xB6, 0x92, 0x80, 0x91, 0x51, 0x80, 0x7F,\
      0xF4}

#define EFI_TCM_MADriver_GUID \
    { 0xca0d6ff6, 0x62a7, 0x4b1f, 0xbb, 0x90, 0x52, 0xee, 0xca, 0x1,  0xa9,\
      0x9f}

#define AMI_TCM_CALLBACK_GUID \
    { 0x91c74e50, 0x361d, 0x4cda, 0xa1, 0x6b, 0xc9, 0x2b, 0xe4, 0xbf, 0x16,\
      0xee}

#define AMI_TPM_LEGACY_GUID \
    { 0xa1c85085, 0x3053, 0x4c4b, 0xa9, 0xf6, 0x72, 0x4d, 0x22, 0xa7, 0x6e,\
      0xf9}

#define PEI_TPM_INITIALIZED_PPI_GUID \
  { \
    0xe9db0d58, 0xd48d, 0x47f6, 0x9c, 0x6e, 0x6f, 0x40, 0xe8, 0x6c, 0x7b, 0x41 \
  }

#define TPM20_HOB_GUID \
  { \
    0x7cea4f7e, 0x2052, 0x46ed, 0xbe, 0xfd, 0xe2, 0x2a, 0x44, 0xdc, 0x65, 0xe7 \
  }

#define FAST_BOOT_VARIABLE_GUID \
    { 0xb540a530, 0x6978, 0x4da7, 0x91, 0xcb, 0x72, 0x7, 0xd7, 0x64, 0xd2, 0x62 }


typedef struct
{
    UINT8 RQST;
    UINT8 RCNT;
    UINT8 ERROR;
    UINT8 Flag;
    UINT8 AmiMisc;
} AMI_PPI_NV_VAR;

typedef struct _mem_in
{
    UINTN  datat;       //0=use_32;1=use_64;2=use_both; 3=dont_use
    UINT64 address;     //Start Memory address
    UINTN  size;        //Memory block Size
} mem_in;

#pragma pack (1)
typedef struct tdVendorInfoStruct
{
    UINT8 *TCGBIOSVENDOR[6];
    UINT8 *TCGOEMID[8];
} TCG_VendorInfoStruct;

typedef struct tdPCClientSpecIdEventStruct
{
    UINT8  PlatformClass;
    UINT8  BIOSTypeInterface;
    UINT8  BIOSTypeMapping;
    UINT8  SpecVersionMajor;
    UINT8  SpecVersionMinor;
    UINT8  SpecErrata;
    UINTN  Reserved;
    UINTN  VendorInfoSize;
    TCG_VendorInfoStruct *VendorInfo;
} TCG_PCClientSpecIDEventStruct;
#pragma pack()


#pragma pack (1)
typedef struct
{
    UINT16 Signature;             // 0xaa55
    UINT32 CodeP;                 // Pointer to beginning of code ( offset to entry point for driver)
    UINT16 Size;                  //Total size of the driver in bytes including header
    UINT32 BaseAddress;           //base address of the TPM(as set by BIOS)
    UINT32 BaseAddress2;          //optional second base address of the TPM(as set by BIOS)
    UINT8  TcgIrqL;               //IRQ level
    UINT8  DMACH;                 //DMA channel
    UINT8  checksum;              //XOR checksum
    UINT8  Reserved;
    UINT32 PCIPFA;                //IRQ level
    UINT32 Other;                 //Cardbus, USB etc
    UINT32 TpmPort;               //location of TPM configuration port
    UINT16 VID;                   //vendor ID
    UINT16 DID;                   //device ID
} MPDRIVER_LEGHEADER;
#pragma pack ()



#define  EfiBootservicesData   0x04

#pragma pack(1)

typedef struct
{
    UINTN                   NumberOfTables;
    EFI_CONFIGURATION_TABLE TableEntry[1];
} TCG_EFI_HANDOFF_TABLE_POINTERS;

//
// EFI_VARIABLE_DATA
//
// This structure serves as the header for measuring variables. The name of the
// variable (in Unicode format) should immediately follow, then the variable
// data.
//
typedef struct
{
    EFI_GUID VariableName;
    UINTN    UnicodeNameLength;
    UINTN    VariableDataLength;
    CHAR16   UnicodeName[1];
    INT8     VariableData[1]; // Driver or platform-specific data
} TCG_EFI_VARIABLE_DATA;
#pragma pack()

#define INTERNAL_SHA_ARRAY_LENGTH            0x500 //500 bytes per SHA update or extend

//-----------------------------------------------------------------------------

#define EFI_TCG_CAP_HOB_GUID \
    { 0xd05f8ff9, 0x8498, 0x4673, 0x84, 0x17, 0x7b, 0x9c, 0xce, 0x3d, 0xdb,\
      0x9b}

#define EFI_TCG_MPDriver_HOB_GUID \
    { 0xbaaead09, 0x2a0,  0x4131, 0x9e, 0xd,  0xbc, 0x52, 0x9e, 0xf0, 0xff,\
      0x2a}

#define EFI_TCG_MADriver_HOB_GUID \
    { 0xb58a69fe, 0x163e, 0x4cc0, 0xa4, 0x87, 0x30, 0x4d, 0x34, 0xd5, 0x48,\
      0x9f}

#define EFI_TCG_MPDriver_GUID \
    { 0x0515BC05, 0x2959, 0x4e91, 0x89, 0xC6, 0x6B, 0x3A, 0x3F, 0x1F, 0xCB,\
      0x65}

#define EFI_TCG_MADriver_GUID \
    { 0x92ba9255, 0x2819, 0x4479, 0x86, 0x7a, 0x1c, 0x58, 0xf0, 0x72, 0xc5,\
      0xb2}

#define EFI_TCM_MPDriver_GUID \
    { 0x3EB9F0D3, 0x40D0, 0x435b, 0xB6, 0x92, 0x80, 0x91, 0x51, 0x80, 0x7F,\
      0xF4}

#define EFI_TCM_MADriver_GUID \
    { 0xca0d6ff6, 0x62a7, 0x4b1f, 0xbb, 0x90, 0x52, 0xee, 0xca, 0x1,  0xa9,\
      0x9f}

#define  EFI_TCG_PEI_READ_ONLY_VARIABLE_PPI_GUID\
   {0x3cdc90c6, 0x13fb, 0x4a75, 0x9e, 0x79, 0x59, 0xe9, 0xdd, 0x78, 0xb9, 0xfa}

#define AMI_TCG_FV_HOB_GUID \
    { 0x69275410, 0x9be7, 0x4df2, 0xb7, 0xbb, 0x54, 0x50, 0x65, 0xb6, 0x70,\
      0xa4}

#define AMI_TCG_INTERFACE_VAR_GUID \
    { 0x6e6ebc2d, 0x77ab, 0x46cf, 0xb2, 0xa7, 0xcc, 0x96, 0x8b, 0xe, 0x8a,\
      0xf3}

#define AMI_PPI_INTERNAL_VAR_GUID \
    { 0x78097bb6, 0x48cf, 0x449b, 0x9b, 0xdb, 0xf6, 0x38, 0x49, 0x85, 0x64,\
      0x60}

#define AMI_PROTOCOL_INTERNAL_HLXE_GUID \
    { 0x78092548, 0x48cf, 0x449b, 0x9b, 0xdb, 0xf6, 0x38, 0x49, 0x85, 0x64,\
      0x60}


#define CMOS_BANK1_INDEXREG     0x70
#define CMOS_BANK2_INDEXREG     0x72
#define CMOS_BANK1_SIZE         0x80

// *****************************************************************************************************************************/
//         PHYSICAL PRESENCE INTERFACE
// *****************************************************************************************************************************/
#define TCPA_PPI_USERABORT       0xFFF0
#define TCPA_PPI_BIOSFAIL        0xFFF1

#define TCPA_PPIOP_ENABLE                       1
#define TCPA_PPIOP_DISABLE                      2
#define TCPA_PPIOP_ACTIVATE                     3
#define TCPA_PPIOP_DEACTIVATE                   4
#define TCPA_PPIOP_CLEAR                        5
#define TCPA_PPIOP_ENABLE_ACTV                  6
#define TCPA_PPIOP_DEACT_DSBL                   7
#define TCPA_PPIOP_OWNER_ON                     8
#define TCPA_PPIOP_OWNER_OFF                    9
#define TCPA_PPIOP_ENACTVOWNER                  10
#define TCPA_PPIOP_DADISBLOWNER                 11
#define TCPA_PPIOP_UNOWNEDFIELDUPGRADE          12
#define TCPA_PPIOP_SETOPAUTH                    13
#define TCPA_PPIOP_CLEAR_ENACT                  14
#define TCPA_PPIOP_SETNOPPIPROVISION_FALSE      15
#define TCPA_PPIOP_SETNOPPIPROVISION_TRUE       16
#define TCPA_PPIOP_SETNOPPICLEAR_FALSE          17
#define TCPA_PPIOP_SETNOPPICLEAR_TRUE           18
#define TCPA_PPIOP_SETNOPPIMAINTENANCE_FALSE    19
#define TCPA_PPIOP_SETNOPPIMAINTENANCE_TRUE     20
#define TCPA_PPIOP_ENABLE_ACTV_CLEAR            21
#define TCPA_PPIOP_ENABLE_ACTV_CLEAR_ENABLE_ACTV   22

#define PPIXOP_ENABLE            0x01
#define PPIXOP_DISABLE           0x02
#define PPIXOP_ACTIVATE          0x04
#define PPIXOP_DEACTIVATE        0x08
#define PPIXOP_OWNER_ON          0x10
#define PPIXOP_OWNER_OFF         0x20
#define PPIXOP_CLEAR             0x40

#define PPIXOP_EN_FLAG           (PPIXOP_ENABLE | PPIXOP_DISABLE)
#define PPIXOP_A_FLAG            (PPIXOP_ACTIVATE | PPIXOP_DEACTIVATE)
#define PPIXOP_O_FLAG            (PPIXOP_OWNER_ON | PPIXOP_OWNER_OFF)

#define PPI_MAX_BASIC_OP         5
#define PPI_FEATURE_ON           1
#define PPI_FEATURE_OFF          2
#define PPI_FEATURE_CHANGE        (PPI_FEATURE_ON | PPI_FEATURE_OFF)


//
// TSS event strings
//
#define TSS_ACTION_CALLING_INT19             "Calling INT 19h"
#define TSS_ACTION_RETURNED_INT19            "Returned INT 19h"
#define TSS_ACTION_RETURNED_INT18            "Return via INT 18h"
#define TSS_ACTION_BOOTING_BCV_DEVICE        "Booting BCV Device "
#define TSS_ACTION_BOOTING_BEV_DEVICE        "Booting BEV Device "
#define TSS_ACTION_ROM_BASED_SETUP           "Entering ROM Based Setup"
#define TSS_ACTION_BOOTING_PARTIES           "Booting to Parties "
#define TSS_ACTION_USER_PASSWORD             "User Password Entered"
#define TSS_ACTION_ADMINISTRATOR_PASSWORD    "Administrator Password Entered"
#define TSS_ACTION_PASSWORD_FAILURE          "Password Failure"
#define TSS_ACTION_WAKE_EVENT                "Wake Event n"
#define TSS_ACTION_BOOT_SEQ_INTERVENTION     "Boot Sequence User Intervention"
#define TSS_ACTION_CHASSIS_INTRUSION         "Chassis Intrusion"
#define TSS_ACTION_NON_FATAL_ERROR           "Non Fatal Error"
#define TSS_ACTION_OPROM_SCAN                "Start Option ROM Scan"
#define TSS_ACTION_UNHIDEING_OPROM           "Unhiding Option ROM Code"

#define TSS_ACTION_IPL_PARTITION             "Booting from "
#define TSS_ACTION_IPL_LEGACY_PARTITION      "Booting from Legacy "


//-----------------------------------------------------------------------------
// Internal Tcg Capabilities Headers and Struct
//-----------------------------------------------------------------------------
VOID* LocateATcgHob (
    UINTN                   NoTableEntries,
    EFI_CONFIGURATION_TABLE *ConfigTable,
    EFI_GUID                *HOB_guid );

#pragma pack (1)
typedef struct
{
    UINT16 Tag;
    UINT32 ParamSize;
    UINT32 CommandCode;
    UINT32 caparea;
    UINT32 subCapSize;
    UINT32 subCap;
} TPM_GetCapabilities_Input;

typedef struct
{
    UINT16 Tag;
    UINT32 ParamSize;
    UINT32 RetCode;
    UINT32 respSize;
    UINT16 tag;
    UINT8  disabled;
    UINT8  ownership;
    UINT8  deactivated;
    UINT8  readPubek;
    UINT8  disableOwnerClear;
    UINT8 allowMaintenance;
    UINT8 physicalPresenceLifetimeLock;
    UINT8 physicalPresenceHWEnable;
    UINT8 physicalPresenceCMDEnable;
    UINT8 CEKPUsed;
    UINT8 TPMpost;
    UINT8 TPMpostLock;
    UINT8 FIPS;
    UINT8 Operator;
    UINT8 enableRevokeEK;
    UINT8 nvLocked;
    UINT8 readSRKPub;
	UINT8 tpmEstablished;
	UINT8 maintenanceDone;
	UINT8 disableFullDALogicInfo;
} TPM_Capabilities_PermanentFlag;

#define NTC_ORD_GET_TPM_STATUS   ((UINT32) 0x20000021)
typedef struct
{
    UINT16 Tag;
    UINT32 ParamSize;
    UINT32 RetCode;
    UINT8  isdisabled;
    UINT8  isdeactivated;
    UINT8  isEkSet;
    UINT8  isOwnerSet;
    UINT8  preConfigSet;
    //ami specific we 
    //don't need rest of structure
} NUVOTON_SPECIFIC_FLAGS;


typedef struct
{
    UINT16 Tag;
    UINT32 ParamSize;
    UINT32 RetCode;
    UINT32 respSize;
    UINT16 tag;
    UINT8  deactivated;
    UINT8  disableForceClear;
    UINT8  physicalPresence;
    UINT8  physicalPresenceLock;
    UINT8  bGlobalLock;
} TPM_VOLATILE_FLAGS;



typedef struct
{
    UINT16 Tag;
    UINT32 ParamSize;
    UINT32 RetCode;
    UINT32 respSize;
    UINT16 tag;
    UINT8  disabled;
    UINT8  ownership;
    UINT8  deactivated;
    UINT8  readPubek;
    UINT8  disableOwnerClear;
    UINT8 physicalPresenceLifetimeLock;
    UINT8 physicalPresenceHWEnable;
    UINT8 physicalPresenceCMDEnable;
    UINT8 CEKPUsed;
    UINT8 TPMpost;
    UINT8 TPMpostLock;
    UINT8 Operator;
    UINT8 enableRevokeEK;
    UINT8 nvLocked;
    UINT8 tpmEstablished;
    UINT8 writeEkCertLock;
} TCM_Capabilities_PermanentFlag;


typedef struct _TPMTransmitEntryStruct
{
    UINT32 pbInBuf;
    UINT32 dwInLen;
    UINT32 pbOutBuf;
    UINT32 dwOutLen;
} TPMTransmitEntryStruct;


#define PCI_EXPANSION_ROM_HEADER_SIGNATURE       0xaa55

#define     READTRANSACTION                          0x01
#define     WRITETRANSACTION                         0x02
#define     GETCONFTRANSACTION                       0x03
#define     RQSTVAR                                  0x10
#define     RCNTVAR                                  0x20
#define     ERRORVAR                                 0x30
#define     CONFIRMATION                             0x40
#define     ERRORVAR2                                0x50
#define     WRITEMOR                                 0x20
#define     WRITERQST                                0x10
#define     WRITEENDRQSTFLAG                         0x01
#define     WRITEENDMORFLAG                          0x02
#define     READENDCONFLAG                           0x03
#define	    TRANSACTION_MASK                         0x0F
#define     TYPE_MASK 	                             0xF0

typedef struct
{
    UINT16 Signature;   // 0xaa55
    UINT16 InitializationSize;
    UINT32 EfiSignature; // 0x0EF1
    UINT16 EfiSubsystem;
    UINT16 EfiMachineType;
    UINT16 CompressionType;
    UINT8  Reserved[8];
    UINT16 EfiImageHeaderOffset;
    UINT16 PcirOffset;
} EFI_PCI_EXPANSION_ROM_HEADER;

#define SCAN_F1         EFI_SCAN_F1
#define SCAN_F2         EFI_SCAN_F2
#define SCAN_F3         EFI_SCAN_F3
#define SCAN_F4         EFI_SCAN_F4
#define SCAN_F5         EFI_SCAN_F5
#define SCAN_F6         EFI_SCAN_F6
#define SCAN_F7         EFI_SCAN_F7
#define SCAN_F8         EFI_SCAN_F8
#define SCAN_F9         EFI_SCAN_F9
#define SCAN_F10        EFI_SCAN_F10
#define SCAN_F11        EFI_SCAN_F11
#define SCAN_F12        EFI_SCAN_F12
#define SCAN_ESC        EFI_SCAN_ESC

typedef struct _TCG_LOG_HOB_
{
    UINT32 TableMaxSize;
    UINT32 TableSize;
    UINT32 EventNum;
    UINT32 Reserved;
} TCG_LOG_HOB;

#pragma pack()
//--------------------------------------------------------------------------
// END_OF Internal Tcg Capabilities Headers and Struct
//--------------------------------------------------------------------------

//--------------------------------------------------------------------------
//USED PE/COFF image headers
//--------------------------------------------------------------------------
typedef struct
{
    UINTN   Signature;
    BOOLEAN FreeBuffer;
    VOID    *Source;
    UINTN   SourceSize;
} IMAGE_FILE_HANDLE;


#define EFI_IMAGE_ERROR_SUCCESS                      0
#define EFI_IMAGE_ERROR_IMAGE_READ                   1
#define EFI_IMAGE_ERROR_INVALID_PE_HEADER_SIGNATURE  2
//--------------------------------------------------------------------------
//--------------------------------------------------------------------------
//
//
//----------------------------------------------------------------------------
// Description: TCG ACPI table. Requires PORTING: OEM data
// Input: None
// Output: None
//----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
//PORTING STARTS
//-----------------------------------------------------------------------------
#define TCG_TBL_REV          0x02
#define TCG_OEMID            "APTIO4"            //; 6 charachters that identify the OEM
#define TCG_TBL_OEM_ID       0x4653414150414E    //"NAPAASF" //; 8 charachters as OEM manufacturer model ID
#define TCG_TBL_OEM_REV      01                  //; DWORD - Revision Number of this table,
#define TCG_CREATOR_ID       0x5446534D          // "MSFT"
#define TCG_CREATOR_REVISION 0x01000013          // TBD
#define TCG_PLATFORM_CLASS   0x0

//-----------------------------------------------------------------------------
//Assuming we are in 32bit mode in PEI and the selectors are set up in real mode
//-----------------------------------------------------------------------------
#define SEL_flatDS      0x8
#define SEL_flatCS      0x10

typedef struct
{
    UINT32 Offset;
    UINT16 Selector;
    UINT32 Codep;
    UINT32 Size;
} FAR32LOCALS;

typedef struct
{
    UINT32 Offset;
    UINT16 Selector;
    UINT32 Codep;
} MASTRUCT;

typedef struct
{
    UINT16  Tag;
    UINT32  ParamSize;
    UINT32  RetCode;
    UINT32  respSize;
    UINT16  tag;
    BOOLEAN postInitialise;
    UINT32  localityModifier;
    BOOLEAN transportExclusive;
    BOOLEAN TOSPresent;
} IntTPM_STANY_FLAGS;


typedef struct
{
    UINT32 ReturnAddress;
    UINT32 Header;
    UINT8  FuncNum;
} ESPFUNCSTRUCT;


typedef struct
{
    UINT8  NoPpiProvision;
    UINT8  NoPpiClear;
    UINT8  NoPpiMaintenance;
} PERSISTENT_BIOS_TPM_FLAGS;

typedef struct
{
    UINT8  Interface : 1; //0=TpmNv, 1= BIOSNv
    UINT8  Reserved1  : 1;
    UINT8  Reserved2  : 1;
    UINT8  Reserved3  : 1;
    UINT8  Reserved4  : 1;
    UINT8  Reserved5  : 1;
    UINT8  Reserved6  : 1;
    UINT8  Reserved7  : 1;
} INTERNAL_BIOS_TPM_PPI_INTERFACE;


typedef
UINT8
(EFIAPI * CONFIRM_USER)(
);

typedef struct _AMI_CONFIRMATION_OVERRIDE_PROTOCOL
{
    CONFIRM_USER                  ConfirmUser;
} AMI_CONFIRMATION_OVERRIDE_PROTOCOL;


typedef
EFI_STATUS
(EFIAPI * READ_PERSISTENT_BIOS_TPM_FLAGS)(
   PERSISTENT_BIOS_TPM_FLAGS *
);

typedef
EFI_STATUS
(EFIAPI * SET_PERSISTENT_BIOS_TPM_FLAGS)(
   PERSISTENT_BIOS_TPM_FLAGS *
);


typedef struct _TPM_PERM_FLAGS
{
    TPM_Capabilities_PermanentFlag  Capabilities;                       
} TPM_PERM_FLAGS;

typedef struct _PERSISTENT_BIOS_TPM_MANAGEMENT_FLAGS_PROTOCOL
{
    READ_PERSISTENT_BIOS_TPM_FLAGS                 ReadBiosTpmflags;
    SET_PERSISTENT_BIOS_TPM_FLAGS                  SetBiosTpmflags;
} PERSISTENT_BIOS_TPM_MANAGEMENT_FLAGS_PROTOCOL;


#define MA_FUNCTION_INIT   0x01
#define MP_FUNCTION_CLOSE  0x02
#define MP_FUNCTION_GET_STATUS  0x03
#define MP_FUNCTION_TRANSMIT    0x04
//-----------------------------------------------------------------------------
//PORTING ENDS
//-----------------------------------------------------------------------------

#endif
//**********************************************************************
//**********************************************************************
//**                                                                  **
//**        (C)Copyright 1985-2013, American Megatrends, Inc.         **
//**                                                                  **
//**                       All Rights Reserved.                       **
//**                                                                  **
//**     5555 Oakbrook Pkwy, Suite 200, Norcross, GA 30093            **
//**                                                                  **
//**                       Phone: (770)-246-8600                      **
//**                                                                  **
//**********************************************************************
//**********************************************************************
