//**********************************************************************
//**********************************************************************
//**                                                                  **
//**        (C)Copyright 1985-2015, American Megatrends, Inc.         **
//**                                                                  **
//**                       All Rights Reserved.                       **
//**                                                                  **
//**        5555 Oakbrook Pkwy, Suite 200, Norcross, GA 30093         **
//**                                                                  **
//**                       Phone: (770)-246-8600                      **
//**                                                                  **
//**********************************************************************
//**********************************************************************
//**********************************************************************
// $Header: /Alaska/SOURCE/Modules/SecureBoot_WIN8/SecureBootMod.c 80    5/14/15 9:45a Alexp $
//`
// $Revision: 80 $
//
// $Date: 5/14/15 9:45a $
//**********************************************************************
// Revision History
// ----------------
// $Log: /Alaska/SOURCE/Modules/SecureBoot_WIN8/SecureBootMod.c $
// 
// 80    5/14/15 9:45a Alexp
// InstallSecureVariables() Update Default Provision logic to handle no
// key defaults mode. 
// SecureBootMod_Init() Do not issue system reset if BootMode = FlUpdate
// or Recovery
// 
// 79    3/09/15 5:05p Alexp
// 1. Implement User prompt to install Secure Boot key defaults 
//     while switching of Secure Boot mode from Custom to Standard 
//     (per Windows8+ Hardware Certification requirements).
//     Add callback on SECURE_BOOT_MODE_CHANGE_KEY
// 2. EIP#200639: When the token DEFAULT_PROVISION_SECURE_VARS enable,
//     the secure boot status is Not Active when first enter setup.
//   [Resolution] Issue SystemReset after initial Secure Boot provisioning
// 3. EIP#201422: set SecVariables_SUPPORT = 0, code will build fail
// 
// 78    10/08/14 3:11p Alexp
// FillAuthhdr(): Default times for Append and Set Variables are
// different.
// -Append uses time "2010.1.1.1" in order not to change var time during
// updates.
// -Set uses time of BIOS creation(original implementation) 
// 
// 77    4/11/14 10:20a Alexp
// EIP#163153: [APTIO4] update 4.6.5.5_TCG_43 is build error.
// Bug: Global var name NvramControl was shared with
// TpmClearOnRollbackOfbd..
// Fix:   define variable as static
// 
// 76    4/07/14 2:47p Alexp
// Add Hii event SECURE_BOOT_MENU_REFRESH on entering of Secure Boot menu
// The callback to this event refreshes the state of internal Secure Boot
// setup flags.
// UpdateSecureVariableBrowserInfo()
// 
// 75    11/15/13 11:38a Alexp
// TSE Callbacks return EFI_UNSUPPORTED for unsupported browser actions
//  Always clear RT attribute for SecureBootSetup var. 
// 
// 73    11/04/13 1:13p Alexp
// ForceSetupModeCallback() . Load defaults fail with new TSE.
// Return UNSUPPORTED for new TSE 2.16.1240 TSE callback event
// EFI_BROWSER_ACTION_DEFAULT_STANDARD 
// 
// 72    10/04/13 12:49p Alexp
// Define EXPOSE_SECURE_BOOT_SETUP_VAR_IF_NOT_SECURE_BOOT_MODE 
// switch to allow OS tools to gain access to Secure Boot setup control 
// only while system is not in Secure Boot mode
// 
// 71    10/03/13 5:27p Alexp
// SecureBootMod_Init()
// Change the logic for clearing of RT attrib for SecureBoot Setup var:
// only clear it if SecureBoot is active, else let OEM OS tools to see the
// var
// 
// 70    10/01/13 10:26a Alexp
// 1. EIP#134931 :The value of "Secure Boot Option" items on 
//     setup menu cannot be kept after flashed BIOS by AFU tool
// 2. Prevent Preserve-, RestoreSecureVariables to be called out of order.
// 
// 69    9/30/13 11:49a Alexp
// EIP#137818 :SecureBootSetup variables are not preserved after flash
// update even though PRESERVE_SECURE_VARIABLES enabled.
// Fix: temporary toggle internal SMM NVRAM flag to gain access to non-RT
// variables 
// 
// 68    8/15/13 10:09a Alexp
// add handling of x509_SHAxx cert types while adding new certs to dbx
// variable
// 
// 67    7/26/13 3:32p Alexp
// 1. EIP#118850: ECR1009: enable dbt dialogs.
// 2. Allow selective Key var provisioning. e.g dbx or dbt are optional 
// 
// 66    6/24/13 5:29p Alexp
// EIP127292: Erase SecureBootSetupVar before setting it with no RT
// attribute
// 
// 65    6/22/13 12:24p Alexp
// EIP:127292: Remove RT attribute from SecureBootSetupVar.
// 
// 64    5/17/13 6:06p Alexp
// 1. Add action on KEY_PROVISION_CHANGE_KEY Enable. Prompt user to
//      install keys immediately
// 2. Always install default Secure Keys as volatile vars based on SDL
//     Token
// 3. EIP#118850: ECR1009: Add placeholder defines for "dbt"
// 
// 62    5/01/13 1:54p Alexp
// InstallSecureVariables() fix build errors if Secure Boot Vars module
// not detected
// 
// 61    3/22/13 4:59p Alexp
// Optimized order in menu selecting option: Key Certificate before Efi
// Variable
// 
// 60    12/24/12 12:33p Alexp
// EIP#108982 : "Secure Boot" Multilanguage Support missing
// Move all local string defines under .uni
// Retrieve strings using updated GetHiiString() function
// 
// 59    12/17/12 3:08p Alexp
// code fixes according to "cppcheck" style & performance suggestions
// 
// 58    12/07/12 4:20p Alexp
// Update Key Management page layout
// 
// 56    11/26/12 10:45a Alexp
// EIP#104961: UEFI 2.3.1 SCT test failed in Generic\EfiCompliant case.
// Fix build warning with PRESERVE_SECURE_VARIABLES flag enabled. 
// 
// 54    11/19/12 4:40p Alexp
// Fix for Win8 SecureBoot logo requirement: restore Secure Boot state
// across flash updates.
// Move all secure boot Setup settings to a separate varstore variable.
// Preserve var across re-flash
// 
// 53    11/16/12 7:16p Alexp
// Fixed ValidateSignatureList() return status for Zero Data or Size
// 
// 52    11/01/12 5:44p Alexp
// bug fix: ValidateSignatureList () returned Success even if no sig
// detected if file size = 0
// 
// 51    10/22/12 3:53p Alexp
// Fix interactive menus for Set/Append Key operations
// 
// 50    10/22/12 10:49a Alexp
// SetMode callback: fix dependency on SetupMode for SecureBoot Enable
// switch.
// 
// 49    10/19/12 5:15p Alexp
// Serve both Set and Append Hii callbacks with common routine SetAppendDb
// 
// 48    10/16/12 3:16p Alexp
// 1. replaced wrong return types for Hi iCallback routines from
// EFI_SUCCESS to EFI_STATUS
// 2. Removed Authenticated attribute from generic R/O UEFI Variables
// PKDefault, etc.
// 
// 47    9/24/12 12:29p Alexp
// 1. Update all callback functions to return EFI_STATUS according to
//     newer 4.6.5.4.1 Setup module
// 2. Block Secure Boot switch from being enabled if CSM is enabled or
//     platform is in Setup Mode: ForceSetupModeCallback()
// 41    9/07/12 5:13p Alexp
// Remove dependency on newer Cores 4.6.5.0+:
// CORE_COMBINED_VERSION  >= 0x4028a
// Win8 compliant BIOS must have upgraded 
// Core components, TSE 
// 
// 40    8/23/12 5:42p Alexp
// Add user selection for supported file formats in Append SecureBoot
// operations
// 
// 39    8/15/12 4:48p Alexp
// 1. Modify Secure Boot page controls. Hide all controls under new
// sub-page 
// 2. Refrash Secure Boot Setup screens upon user load Defaults/Previous
// values
// 3. 
// 
// 38    8/01/12 3:55p Alexp
// Link KEY_PROVISION_CHANGE_KEY event with common
// ForceSetupModeCallback()
// 
// 37    7/30/12 10:59a Alexp
//  Added code to address UEFI ECR874: Install Factory defaults as
// Read-only volatile variables for key distribution.
//  Update Secure Boot page layout
//     1. Security Page
//       1.3 Replaced standalone SecureBootMode Option to an added value
// in
//   Secure Boot list (on/off/custom)
//       1.4 Display SecureBootMode Standard/Custom Status
//     2. Key Management Page
//       2.1 Add Append Certificate Options along with Append from File
//            New functions append new Certificates from different types
// of
//            input Certs (x509, RSA2048 & SHA256) and Signature List
// blobs
//       2.2 Use single Save to files option for all Sec Variables
//       2.3 Set Variable Option gets a Key from a File Browser or a
//             Factory  Default storage.
// 
// 
// 34    7/09/12 2:40p Alexp
// HiiAddString
// Fix build error if warning level=3
// 
// 33    6/13/12 10:01a Alexp
// Fix build warning for uninitialized VarSize in
// PreserveSecureVariables()
// 
// 32    6/11/12 3:21p Alexp
// EIP:90468 UEFI Secure Boot implementation inquiry. When I export the
// PK, KEK, DB, and DBX files from the Setup menu, I can't reload them. 
// FIX: Added logic to append dummy AuthHdr on top of exportable Variable
// data in order to make file importable by Key Management page.
// 
// 31    6/05/12 4:26p Alexp
// EIP:91587 Function HiiLibSetBrowserData always return error under new
// tse
//    Fix in UpdateSecureVariableBrowserInfo() -> call
// HiiLibSetBrowserData() only when called form HiiCallback
// 
// 30    5/15/12 9:46a Alexp
// Preserve/Restore SecureVariables(). Use properly formatted Auth
// Variable data block. 
// 
// 29    4/20/12 5:03p Alexp
// EIP:88261: Default Secure Variables are being reinstalled on each
// system reboot when "DEFAULT_PROVISION_SECURE_VARS" is enabled 
// Fix: Replaced usage of FORCE_SETUP_KEY and FORCE_DEFAULT_KEY with
// dynamicaly generated values to fixed enum types RESET_NV_KEYS=1,
// SET_NV_DEFAULT_KEYS
// 
// 27    3/16/12 12:04p Alexp
// made "PKeyFileGuid" names "static" to avoid double names across linked
// modules
// 
// 26    3/09/12 3:29p Alexp
// Implementation to PRESERVE_SECURE_VARIABLES on Flash Update is moved
// here from SecSmiFlash component
// 
// 25    2/14/12 7:35p Alexp
// SecureBootMod_Init: Update browser info after DefaultKeys are
// provisioned.
// 
// 24    2/02/12 12:59p Alexp
// 1. AppendSecureBootDBCallback. Removed DEL attribute when do Append
// 2. SetSecureVariable. optimized the logic
// 
// 23    12/12/11 6:37p Alexp
// Add check if "DEFAULT_PROVISION_SECURE_VARS" is defined.
// Fix build error for condition SET_SECURE_VARS = 0
// 
// 22    11/18/11 11:13a Alexp
// ForceSetupModeCallback: Initialize Status as not all execution path
// update this variable
// 
// 21    11/10/11 4:02p Alexp
// conditionallly compile all callback related code if
// CORE_COMBINED_VERSION
//  >=0x4028a (4.6.5.0+)
// 
// 19    11/08/11 3:05p Alexp
// fix spelling errors in displayed messages
// 
// 18    11/07/11 6:26p Alexp
// Add Key Management controls to add/get/append and delete Secure
// Variables from the Setup page
// 
// 17    11/03/11 6:30p Alexp
// SecureBootMod.c(sdl, .sd, .uni) Change the appearance of Secure Boot
// items on Setup Security page. Added information on currently installed
// Secure Variables.
// 
// 16    10/17/11 6:55p Alexp
// Add warning message if User Mode can't be reset due to the lock set on
// Secure Variable update
// 
// 13    8/25/11 8:30a Alexp
//  -ForceSetupModeCallback: proceed inside the function after check for
//  action-EFI_BROWSER_ACTION_CHANGING
//  -force manufacturing defaults during first boot if
//  DEFAULT_PROVISION_SECURE_VARS set to 1
// 
// 11    8/23/11 4:50p Alexp
//
// 9     8/22/11 5:19p Alexp
// restored CallBack notification method to set Manufacturing defaults
// from TSE SetupPage
// 
// 8     8/19/11 5:25p Alexp
//  removed callback events on Security Page updates
//  Use static Setup Flags to Update Secure Variables at boot time
// 
// 5     8/05/11 3:15p Alexp
// use globally defined names for PK, KEK,.. variable
// 
// 4     7/18/11 9:57a Alexp
// Added new protocol SECURITY_VARIABLE_INSTALL_PROTOCOL
// 
// 3     7/01/11 1:30p Alexp
// ForceSetupModeCallback: fix for EFI_REVISION < 2.1builds 
// 
// 
// 1     6/30/11 3:49p Alexp
// Add provisioning of factory default Secure variables. Used Setup page
// to add/remove sec variables
// 
// 3     5/16/11 1:07p Alexp
// include SDL switch to control provisioning of Platform Key EFI
// variable.
// 
// 2     5/10/11 5:12p Alexp
// removed include statement
// 
// 1     5/10/11 10:01a Alexp
// 
// 6     4/18/11 7:23p Alexp
// draft. may not need this file at all
// 
// 
//**********************************************************************
#include <Token.h>
#include <AmiDxeLib.h>
#include <ImageAuthentication.h>
#include <AmiCertificate.h>
#include <Protocol\AmiDigitalSignature.h>
#include <Setup.h>
#include <SecureBootMod.h>

#include "timestamp.h"

#include <AutoId.h>
#include <SetupStrTokens.h>

#include <Protocol\AmiPostMgr.h>
#include <Protocol\simplefilesystem.h>    
#ifdef SETUP_COMPILE
#include <Protocol\HiiString.h>
#include <Protocol\devicepath.h>
#endif

extern EFI_RUNTIME_SERVICES *pRS;

#if defined(CORE_COMBINED_VERSION) && CORE_COMBINED_VERSION >=0x4028b
#define RETURN(status) {return status;}
#else
#define RETURN(status) {return ;}
#endif
//
// Global variables
//
static EFI_GUID gAmiPostManagerProtocolGuid = AMI_POST_MANAGER_PROTOCOL_GUID;
static EFI_GUID gSimpleFileSystemGuid       = EFI_SIMPLE_FILE_SYSTEM_PROTOCOL_GUID;
static EFI_GUID gEfiGlobalVariableGuid      = EFI_GLOBAL_VARIABLE;

//static EFI_GUID gEfiCertX509Sha256Guid = EFI_CERT_X509_SHA256_GUID;
//static EFI_GUID gEfiCertX509Sha384Guid = EFI_CERT_X509_SHA384_GUID;
//static EFI_GUID gEfiCertX509Sha512Guid = EFI_CERT_X509_SHA512_GUID;

static EFI_GUID PKeyFileGuid  = //CC0F8A3F-3DEA-4376-9679-5426BA0A907E
{ 0xCC0F8A3F, 0x3DEA,  0x4376, 0x96, 0x79, 0x54, 0x26, 0xba, 0x0a, 0x90, 0x7e };
static EFI_GUID KekFileGuid  =  // {9FE7DE69-0AEA-470a-B50A-139813649189}
{ 0x9fe7de69, 0xaea, 0x470a, 0xb5, 0xa, 0x13, 0x98, 0x13, 0x64, 0x91, 0x89 };
static EFI_GUID DbFileGuid  =  // {FBF95065-427F-47b3-8077-D13C60710998}
{ 0xfbf95065, 0x427f, 0x47b3, 0x80, 0x77, 0xd1, 0x3c, 0x60, 0x71, 0x9, 0x98 };
static EFI_GUID DbxFileGuid  =  // {9D7A05E9-F740-44c3-858B-75586A8F9C8E}
{ 0x9d7a05e9, 0xf740, 0x44c3, 0x85, 0x8b, 0x75, 0x58, 0x6a, 0x8f, 0x9c, 0x8e };
static EFI_GUID DbtFileGuid  =  // {C246FBBF-F75C-43F7-88A6-B5FD0CF1DB7F}
{ 0xC246FBBF, 0xF75C, 0x43F7, 0x88, 0xa6, 0xb5, 0xfd, 0x0c, 0xf1, 0xdb, 0x7f };

static AMI_POST_MANAGER_PROTOCOL *mPostMgr = NULL;

static EFI_GUID *SecureVariableFileGuid [] = {
    &DbxFileGuid,
    &DbtFileGuid,
    &DbFileGuid,
    &KekFileGuid,
    &PKeyFileGuid,
    NULL
};

static CHAR16* SecureVariableFileName[] = {
    EFI_IMAGE_SECURITY_DATABASE1,
    EFI_IMAGE_SECURITY_DATABASE2,
    EFI_IMAGE_SECURITY_DATABASE,
    EFI_KEY_EXCHANGE_KEY_NAME,
    EFI_PLATFORM_KEY_NAME,
    NULL
};

static CHAR16* SecureVariableFileNameDefault[] = {
    EFI_IMAGE_SECURITY_DATABASE1_DEFAULT,
    EFI_IMAGE_SECURITY_DATABASE2_DEFAULT,
    EFI_IMAGE_SECURITY_DATABASE_DEFAULT,
    EFI_KEY_EXCHANGE_KEY_NAME_DEFAULT,
    EFI_PLATFORM_KEY_NAME_DEFAULT,
    NULL
};

static SECURE_BOOT_SETUP_VAR SecureBootSetup = {
    DEFAULT_SECURE_BOOT_ENABLE, 
    DEFAULT_SECURE_BOOT_MODE, 
#ifdef DEFAULT_PROVISION_SECURE_VARS
    DEFAULT_PROVISION_SECURE_VARS,
#else
    0,
#endif
    LOAD_FROM_FV,
    LOAD_FROM_OROM,
    LOAD_FROM_REMOVABLE_MEDIA,
    LOAD_FROM_FIXED_MEDIA};

static EFI_GUID guidSecurity = SECURITY_FORM_SET_GUID;
static UINT8 bKey[5] = {0, 0, 0, 0, 0};
typedef enum { RESET_NV_KEYS=1, SET_NV_DEFAULT_KEYS=2, SET_RT_DEFAULT_KEYS=4};

EFI_STATUS InstallSecureVariables (UINT16);
VOID UpdateSecureVariableBrowserInfo (VOID);
VOID UpdateSecureBootBrowserInfo (VOID);

// 
//
// AMI_EFI_VARIABLE_AUTHENTICATION_2 descriptor
//
// A time-based authentication method descriptor template
//
#pragma pack(1)
#ifndef AMI_EFI_VARIABLE_AUTHENTICATION_2
typedef struct {
    EFI_TIME                            TimeStamp;
    WIN_CERTIFICATE_UEFI_GUID_1         AuthInfo;
} AMI_EFI_VARIABLE_AUTHENTICATION_2;
#endif
typedef struct {
    AMI_EFI_VARIABLE_AUTHENTICATION_2   AuthHdr;
    EFI_SIGNATURE_LIST                  SigList;
    EFI_SIGNATURE_DATA                  SigData;
} EFI_VARIABLE_SIG_HDR_2;
#pragma pack()

#define EFI_CERT_TYPE_RSA2048_SIZE        256
#define EFI_CERT_TYPE_SHA256_SIZE         32
#define EFI_CERT_TYPE_CERT_X509_SHA256_GUID_SIZE        48
#define EFI_CERT_TYPE_CERT_X509_SHA384_GUID_SIZE        64
#define EFI_CERT_TYPE_CERT_X509_SHA512_GUID_SIZE        80

static EFI_GUID  mSignatureSupport[SIGSUPPORT_NUM] = {SIGSUPPORT_LIST};

#ifdef TSEBIN_COMPILE
extern BOOLEAN gBrowserCallbackEnabled;
#else
BOOLEAN gBrowserCallbackEnabled = FALSE;
#endif

// InstallVars
#define SET_SECURE_VARIABLE_DEL 1
#define SET_SECURE_VARIABLE_SET 2
#define SET_SECURE_VARIABLE_APPEND 4

//#############################################################################################################################
#ifdef SETUP_COMPILE
//#############################################################################################################################
typedef struct
{
    UINT64 Type;
    UINTN Size;
    CHAR16 *Name;
    STRING_REF Token;
} FILE_TYPE;

static BOOLEAN gValidOption = FALSE;
static EFI_HII_STRING_PROTOCOL *HiiString = NULL;
static EFI_HII_HANDLE gHiiHandle;

#define StrMaxSize 200
static CHAR16 StrTitle[StrMaxSize], StrMessage[StrMaxSize];
static CHAR16 StrTemp[StrMaxSize];

EFI_STATUS DevicePathToStr(EFI_DEVICE_PATH_PROTOCOL *Path,CHAR8    **Str);
EFI_STATUS FileBrowserLaunchFileSystem(BOOLEAN bSelectFile, OUT EFI_HANDLE **outFsHandle, OUT CHAR16 **outFilePath, OUT UINT8 **outFileBuf,OUT UINTN *size );
VOID GetHiiString(IN EFI_HII_HANDLE HiiHandle, IN STRING_REF Token, UINTN DataSize, CHAR16  * pData);
#endif

//<AMI_PHDR_START>
//----------------------------------------------------------------------------
// Procedure:   UpdateSecureBootBrowserInfo
//
// Description: Update Secure Boot flags status
//
// Input:       none
//
// Output:      none
//
// Modified:
//
// Referrals:
//
// Notes:
//----------------------------------------------------------------------------
//<AMI_PHDR_END>
VOID UpdateSecureBootBrowserInfo ()
{
#if (defined(SETUP_COMPILE) || defined (TSEBIN_COMPILE)) && EFI_SPECIFICATION_VERSION >= 0x2000A
    EFI_STATUS  Status;
    UINTN       Size;
    UINT8       Byte=0;
    UINT32      Attributes=0;
    BOOLEAN     tmpBrowserCallbackEnabled = gBrowserCallbackEnabled;

    gBrowserCallbackEnabled = TRUE;
    Status = HiiLibSetBrowserData( sizeof(bKey), &bKey, &guidSecurity, AMI_SECURE_VAR_PRESENT_VAR);
    Size = 1;
    Status=pRS->GetVariable(EFI_SECURE_BOOT_NAME, &gEfiGlobalVariableGuid, (UINT32*)&Attributes, &Size, &Byte);
    TRACE((-1,"SecureBoot=%x,  status=%r\n",  Byte, Status));
    Status = HiiLibSetBrowserData(Size, &Byte, &gEfiGlobalVariableGuid, EFI_SECURE_BOOT_NAME);
    Size = 1;
    Status=pRS->GetVariable(EFI_SETUP_MODE_NAME, &gEfiGlobalVariableGuid, (UINT32*)&Attributes, &Size, &Byte);
    TRACE((-1,"SetupMode=%x, Status %r\n",  Byte, Status));
    Status = HiiLibSetBrowserData( Size, &Byte, &gEfiGlobalVariableGuid, EFI_SETUP_MODE_NAME);
    gBrowserCallbackEnabled = tmpBrowserCallbackEnabled;
#endif
}

//<AMI_PHDR_START>
//----------------------------------------------------------------------------
// Procedure:   UpdateSecureVariableBrowserInfo
//
// Description: Detect 5 EFI Variables: PK, KEK, db, dbx, dbt(TBD)
//
// Input:       none
//
// Output:      none
//
// Modified:
//
// Referrals:
//
// Notes:
//----------------------------------------------------------------------------
//<AMI_PHDR_END>
VOID UpdateSecureVariableBrowserInfo ()
{
    EFI_STATUS  Status;
    UINTN       Size;
    UINT8       Index;
    EFI_GUID    *EfiVarGuid;

    Index = 0;
    while(SecureVariableFileName[Index] != NULL)
    {
        if(Index < 3)
            EfiVarGuid = &gEfiImageSecurityDatabaseGuid;
        else
            EfiVarGuid = &gEfiGlobalVariableGuid;

        Size = 0;
        bKey[Index] = 0;
        Status = pRS->GetVariable( SecureVariableFileName[Index], EfiVarGuid, NULL, &Size, NULL);
        TRACE((-1,"NV Var %S,  status=%r\n",  SecureVariableFileName[Index], Status));
        if(Status == EFI_BUFFER_TOO_SMALL)
             bKey[Index] = 1;

        Index++;
    }
    pRS->SetVariable(AMI_SECURE_VAR_PRESENT_VAR,&guidSecurity, EFI_VARIABLE_BOOTSERVICE_ACCESS, sizeof(bKey), &bKey);

    UpdateSecureBootBrowserInfo();
}

#if SET_SECURE_VARS == 1

//**********************************************************************
//<AMI_PHDR_START>
//
// Procedure:  CryptoGetRawImage
//
// Description:    Loads binary from RAW section of X firmware volume
//
//  Input:
//               NameGuid  - The guid of binary file
//               Buffer    - Returns a pointer to allocated memory. Caller must free it when done.
//               Size      - Returns the size of the binary loaded into the buffer.
//
// Output:         Buffer - returns a pointer to allocated memory. Caller
//                        must free it when done.
//               Size  - returns the size of the binary loaded into the
//                        buffer.
//               EFI_NOT_FOUND  - Can't find the binary.
//               EFI_LOAD_ERROR - Load fail.
//               EFI_SUCCESS    - Load success.
//
//<AMI_PHDR_END>
//**********************************************************************
EFI_STATUS
CryptoGetRawImage (
  IN      EFI_GUID       *NameGuid,
  IN OUT  VOID           **Buffer,
  IN OUT  UINTN          *Size
  )
{
  EFI_STATUS                    Status;
  UINTN                         HandleCount;
  UINTN                         Index;
  EFI_FIRMWARE_VOLUME_PROTOCOL  *Fv;
  EFI_HANDLE                    *HandleBuff;
  UINT32                        AuthenticationStatus;

 *Buffer=0;
 *Size=0;
  Status = pBS->LocateHandleBuffer (ByProtocol,&gEfiFirmwareVolumeProtocolGuid,NULL,&HandleCount,&HandleBuff);
  if (EFI_ERROR (Status) || HandleCount == 0) {
    return EFI_NOT_FOUND;
  }
  //
  // Find desired image in all Fvs
  //
  for (Index = 0; Index < HandleCount; Index++) {
    Status = pBS->HandleProtocol (HandleBuff[Index],&gEfiFirmwareVolumeProtocolGuid,&Fv);

    if (EFI_ERROR (Status)) {
       continue;//return EFI_LOAD_ERROR;
    }
    //
    // Try a raw file
    //
    Status = Fv->ReadSection (
                  Fv,
                  NameGuid,
                  EFI_SECTION_RAW,
                  0,    //Instance
                  Buffer,
                  Size,
                  &AuthenticationStatus
                  );

    if (Status == EFI_SUCCESS) break;
  }

  pBS->FreePool(HandleBuff);

  if (Index >= HandleCount) {
    return EFI_NOT_FOUND;
  }

  return EFI_SUCCESS;
}
#endif

//<AMI_PHDR_START>
//----------------------------------------------------------------------------
// Procedure:   InstallSecureVariables
//
// Description: Install 4 EFI Variables: PK, KEK, db, dbx & dbt(TBD)
//
// Input:       BOOLEAN InstallVars
//                  TRUE  - attempt to install 4 secure variables
//                  FALSE - erase 4 secure variables
//
// Output:      EFI_STATUS
//
// Modified:
//
// Referrals:
//
// Notes:
//----------------------------------------------------------------------------
//<AMI_PHDR_END>
EFI_STATUS
InstallSecureVariables (
    UINT16    InstallVars
)
{
    EFI_STATUS  Status = EFI_SUCCESS;
    UINT8      *pVarBuffer = NULL;
    UINT8       Index;
    EFI_GUID    *EfiVarGuid;
    UINT32      Attributes;
    UINTN       FileSize = 0;
#if SET_SECURE_VARS == 1
    UINTN       Size, Offset;
    AMI_EFI_VARIABLE_AUTHENTICATION_2 *AuthHdr2;
#endif
///////////////////////////////////////////////////////////////////////////////
// Initial provisioning of Authenticated non-volitile EFI Variables 
////////////////////////////////////////////////////////////////////////////////
    Attributes = EFI_VARIABLE_RUNTIME_ACCESS |
                 EFI_VARIABLE_BOOTSERVICE_ACCESS; 
    Index = 0;
    while(/*!EFI_ERROR(Status) &&*/ SecureVariableFileName[Index] != NULL)
    {
        if(Index < 3) 
            EfiVarGuid = &gEfiImageSecurityDatabaseGuid;
        else
            EfiVarGuid = &gEfiGlobalVariableGuid;
// if SET_NV_DEFAULT_KEYS set
/*
1. check if File is present CryptoGetRawImage
2. if not - skip to next var
3. if present -> move to Erase... .
*/        
#if SET_SECURE_VARS == 1
        if(InstallVars & (SET_NV_DEFAULT_KEYS | SET_RT_DEFAULT_KEYS)) {
            pVarBuffer = NULL;
            FileSize = 0 ; 
            Status = CryptoGetRawImage( SecureVariableFileGuid[Index], &pVarBuffer, (UINTN*)&FileSize);
            if(EFI_ERROR(Status)) {
                Index++;
                continue;
            }
         }
#endif
        if((InstallVars & RESET_NV_KEYS)== RESET_NV_KEYS) {
        // try to erase. should succeed if system in pre-boot and Admin mode
            Status = pRS->SetVariable(SecureVariableFileName[Index],EfiVarGuid,0,0,NULL);
            TRACE((-1,"Clear NV Var %S, Status %r\n",SecureVariableFileName[Index], Status));
            if(EFI_ERROR(Status) && Status == EFI_NOT_FOUND) 
                Status = EFI_SUCCESS;
        }
#if SET_SECURE_VARS == 1
        if((InstallVars & (SET_NV_DEFAULT_KEYS | SET_RT_DEFAULT_KEYS)) &&
            pVarBuffer && FileSize 
        ){
            if(InstallVars & (SET_RT_DEFAULT_KEYS)) {
                AuthHdr2 = (AMI_EFI_VARIABLE_AUTHENTICATION_2*)pVarBuffer;
                Offset = sizeof(EFI_TIME) + AuthHdr2->AuthInfo.Hdr.dwLength;
                Status = pRS->SetVariable(SecureVariableFileNameDefault[Index],
                       &gEfiGlobalVariableGuid,
                        Attributes,
                        FileSize - Offset,
                        (UINT8*)pVarBuffer + Offset
                );
                TRACE((-1,"Set RT Var %S, Status %r\n",SecureVariableFileNameDefault[Index], Status));
            }
            if(InstallVars & (SET_NV_DEFAULT_KEYS)) {
                Size = 0;
                Status = pRS->GetVariable( SecureVariableFileName[Index], EfiVarGuid, NULL, &Size, NULL);
                if(EFI_ERROR(Status) && Status == EFI_NOT_FOUND ) {
                    Status = pRS->SetVariable(SecureVariableFileName[Index],
                            EfiVarGuid,
                            (UINT32)(Attributes | EFI_VARIABLE_NON_VOLATILE | EFI_VARIABLE_TIME_BASED_AUTHENTICATED_WRITE_ACCESS),
                            FileSize,
                            pVarBuffer
                    );
                    TRACE((-1,"Set NV Var %S, Status %r\n",SecureVariableFileName[Index], Status));
                }
            }
            pBS->FreePool(pVarBuffer);
        }
#endif
        Index++;
    }

    return Status;
}


//<AMI_PHDR_START>
//----------------------------------------------------------------------
// Procedure:   FillAuthHdr
//
// Description: 
//
// Input:       NONE
//
// Output:      NONE
//
// Returns:     NONE
//
//----------------------------------------------------------------------
//<AMI_PHDR_END>
static VOID FillAuthHdr(
    UINT8*  pVar,
    UINT8   VarSetMode
)
{
    AMI_EFI_VARIABLE_AUTHENTICATION_2 *AuthHdr2;
    static EFI_TIME EfiTime = {
    FOUR_DIGIT_YEAR_INT,
    TWO_DIGIT_MONTH_INT,
    TWO_DIGIT_DAY_INT,
    TWO_DIGIT_HOUR_INT,
    TWO_DIGIT_MINUTE_INT,
    TWO_DIGIT_SECOND_INT,0,0,0,0,0};

    AuthHdr2 = (AMI_EFI_VARIABLE_AUTHENTICATION_2*)pVar;
    MemCpy (&AuthHdr2->TimeStamp, &EfiTime, sizeof (EFI_TIME));
    if((VarSetMode & SET_SECURE_VARIABLE_APPEND)== SET_SECURE_VARIABLE_APPEND)
        AuthHdr2->TimeStamp.Year = 2000; // append should not change the original date the var was created
    AuthHdr2->AuthInfo.Hdr.dwLength = sizeof(WIN_CERTIFICATE_UEFI_GUID_1);
    AuthHdr2->AuthInfo.Hdr.wRevision = 0x200;
    AuthHdr2->AuthInfo.Hdr.wCertificateType = WIN_CERT_TYPE_EFI_GUID;
    AuthHdr2->AuthInfo.CertType = gEfiCertTypePkcs7Guid;

    return;
}  
//<AMI_PHDR_START>
//----------------------------------------------------------------------
// Procedure:   FillAuthVarHdr
//
// Description: 
//
// Input:       NONE
//
// Output:      NONE
//
// Returns:     NONE
//
//----------------------------------------------------------------------
//<AMI_PHDR_END>
VOID FillAuthVarHdr(
    UINT8 *pVar,
    UINT8 *pCert,
    UINTN CertSize,
    UINT8 VarSetMode
)
{
    EFI_VARIABLE_SIG_HDR_2 *AuthHdr2;    
    static EFI_GUID    AmiSigOwner = AMI_APTIO_SIG_OWNER_GUID;

    AuthHdr2 = (EFI_VARIABLE_SIG_HDR_2*)pVar;

    // Append AuthHdr to Var data.
    FillAuthHdr(pVar, VarSetMode); // Append AuthHdr to Var data.

    //      CopyMem (&AuthHdr2->SigList.SignatureType, gEfiCertSha256Guid, sizeof (EFI_GUID));
    if(CertSize == EFI_CERT_TYPE_SHA256_SIZE)
        AuthHdr2->SigList.SignatureType = gEfiCertSha256Guid;
    if(CertSize == EFI_CERT_TYPE_CERT_X509_SHA256_GUID_SIZE)
        AuthHdr2->SigList.SignatureType = gEfiCertX509Sha256Guid;
    if(CertSize == EFI_CERT_TYPE_CERT_X509_SHA384_GUID_SIZE)
        AuthHdr2->SigList.SignatureType = gEfiCertX509Sha384Guid;
    if(CertSize == EFI_CERT_TYPE_CERT_X509_SHA512_GUID_SIZE)
        AuthHdr2->SigList.SignatureType = gEfiCertX509Sha512Guid;
    if(CertSize == EFI_CERT_TYPE_RSA2048_SIZE)
        AuthHdr2->SigList.SignatureType = gEfiCertRsa2048Guid;
    if(CertSize > EFI_CERT_TYPE_RSA2048_SIZE)
        AuthHdr2->SigList.SignatureType = gEfiCertX509Guid;

    AuthHdr2->SigList.SignatureSize = (UINT32)(sizeof(EFI_GUID)+CertSize);
    AuthHdr2->SigList.SignatureListSize = AuthHdr2->SigList.SignatureSize+sizeof(EFI_SIGNATURE_LIST);
    AuthHdr2->SigList.SignatureHeaderSize = 0;
    AuthHdr2->SigData.SignatureOwner = AmiSigOwner;

TRACE((TRACE_ALWAYS,"SigList GUID: %g\nSigSize=%x\nListSize=%x", AuthHdr2->SigList.SignatureType,  AuthHdr2->SigList.SignatureSize, AuthHdr2->SigList.SignatureListSize));

//    MemCpy(AuthHdr2->SigData.SignatureData, pCert, CertSize);

    return;
}   

//<AMI_PHDR_START>
//----------------------------------------------------------------------------
// Procedure:   ValidateSignatureList
//
// Description: 
//              Validate the data payload begins with valid Signature List header
//              and based on the results returns Status.
//
// Input:
//              IN VOID *Data - pointer to the Var data
//              IN UINTN DataSize - size of Var data
//
// Output:      EFI_STATUS
//              UINTN RealDataSize - only the size of the combined length of Signature Lists
//
//----------------------------------------------------------------------------
//<AMI_PHDR_END>
EFI_STATUS ValidateSignatureList (
    IN VOID         *Data,
    IN UINTN        DataSize
)
{
    EFI_STATUS            Status;
    EFI_SIGNATURE_LIST   *SigList;
    UINTN                 Index;

    Status = EFI_SECURITY_VIOLATION;

    if(DataSize == 0 || Data == NULL)
        return Status; // Sig not found

    SigList  = (EFI_SIGNATURE_LIST *)Data;

// loop till end of DataSize for all available SigLists

// Verify signature is one from SigDatabase list mSignatureSupport / sizeof(EFI_GUID)
// SigData begins with SigOwner GUID
// SignatureHdrSize = 0 for known Sig Types

    while ((DataSize > 0) && (DataSize >= SigList->SignatureListSize)) {

        for (Index = 0; Index < SIGSUPPORT_NUM; Index++) {
            if (!guidcmp ((EFI_GUID*) &(SigList->SignatureType), &mSignatureSupport[Index]))
                break;
        }
TRACE((TRACE_ALWAYS,"SigList.Type-"));
        if(Index >= SIGSUPPORT_NUM)
            return EFI_SECURITY_VIOLATION; // Sig not found

TRACE((TRACE_ALWAYS,"OK\nSigList.Size-"));
        if(SigList->SignatureListSize < 0x4C || // Min size for SHA2 Hash Certificate sig list
           SigList->SignatureListSize > NVRAM_SIZE)
            return EFI_SECURITY_VIOLATION; 

TRACE((TRACE_ALWAYS,"OK\nSigList.HdrSize-"));
        if(SigList->SignatureHeaderSize != 0)
            return EFI_SECURITY_VIOLATION; // Sig not found

TRACE((TRACE_ALWAYS,"OK\n"));
        DataSize -= SigList->SignatureListSize;
        SigList = (EFI_SIGNATURE_LIST *) ((UINT8 *) SigList + SigList->SignatureListSize);

        Status = EFI_SUCCESS;
    }
    
    return Status;
}

#ifdef SMIFLASH_COMPILE

#if defined(PRESERVE_SECURE_VARIABLES) && PRESERVE_SECURE_VARIABLES==1

static EFI_GUID AmiNvramControlProtocolGuid = { 0xf7ca7568, 0x5a09, 0x4d2c, { 0x8a, 0x9b, 0x75, 0x84, 0x68, 0x59, 0x2a, 0xe2 } };
typedef EFI_STATUS (*SHOW_BOOT_TIME_VARIABLES)(BOOLEAN Show);

typedef struct{
    SHOW_BOOT_TIME_VARIABLES ShowBootTimeVariables;
} AMI_NVRAM_CONTROL_PROTOCOL;

static AMI_NVRAM_CONTROL_PROTOCOL *NvramControl = NULL;

// Array of pointers to Secure Variables in TSEG.
static UINT8* SecureFlashVar[6];
static UINTN SecureFlashVarSize[6];
static UINT32 SecureFlashVarAttr[6];
static UINT32 SecBootVar_Attr=0;
//<AMI_PHDR_START>
//----------------------------------------------------------------------
// Procedure:   PreserveSecureVariables
//
// Description: Save the PK-KEK-db-dbx
//
// Input:       NONE
//
// Output:      NONE
//
// Returns:     NONE
//
//----------------------------------------------------------------------
//<AMI_PHDR_END>
VOID PreserveSecureVariables(VOID)
{
    EFI_STATUS  Status;
    UINT8       Index;
    EFI_GUID    *EfiVarGuid;
    UINTN       VarSize;

TRACE((TRACE_ALWAYS,"PreserveVar:\n"));
// 1. Preserve Secure Boot variables.
    Index = 0;
    while(SecureVariableFileName[Index] != NULL)
    {
        if(Index < 3) 
            EfiVarGuid = &gEfiImageSecurityDatabaseGuid;
        else
            EfiVarGuid = &gEfiGlobalVariableGuid;

        SecureFlashVar[Index] = NULL;
        SecureFlashVarSize[Index] = 0;
        SecureFlashVarAttr[Index] = 0;
        Status = pRS->GetVariable( SecureVariableFileName[Index], EfiVarGuid, &SecureFlashVarAttr[Index], &SecureFlashVarSize[Index], SecureFlashVar[Index]);
        if(Status == EFI_BUFFER_TOO_SMALL)
        {
            VarSize = SecureFlashVarSize[Index]+sizeof(AMI_EFI_VARIABLE_AUTHENTICATION_2);
            Status = pSmst->SmmAllocatePool(0, VarSize, (void**)&SecureFlashVar[Index]);
            if(!EFI_ERROR(Status))
                Status = pRS->GetVariable( 
                    SecureVariableFileName[Index], 
                    EfiVarGuid, 
                    &SecureFlashVarAttr[Index], 
                    &SecureFlashVarSize[Index], 
                    SecureFlashVar[Index]+sizeof(AMI_EFI_VARIABLE_AUTHENTICATION_2));

            SecureFlashVarSize[Index] = VarSize;
            FillAuthHdr(SecureFlashVar[Index], SET_SECURE_VARIABLE_SET);
      
TRACE((TRACE_ALWAYS,"%S (%r) Size=%x\n", SecureVariableFileName[Index], Status, SecureFlashVarSize[Index]));
        }
        Index++;
    }
// 2. Preserve Secure Boot Setup variables
    // Set "Show BootTime Variables" flag
    if (NvramControl == NULL)   // first time?
        NvramControl = GetSmstConfigurationTable(&AmiNvramControlProtocolGuid);
    if (NvramControl == NULL) 
        return;
    // Set "Show BootTime Variables" flag
    NvramControl->ShowBootTimeVariables(TRUE);

    VarSize = sizeof(SECURE_BOOT_SETUP_VAR);
    Status = pRS->GetVariable (AMI_SECURE_BOOT_SETUP_VAR,&guidSecurity,&SecBootVar_Attr,&VarSize,&SecureBootSetup);
TRACE((TRACE_ALWAYS,"SecureBootSetup (%r) Size=%x, SecBoot-%d, SecMode-%d,DefaultProvision-%d\n", Status, VarSize, SecureBootSetup.SecureBootSupport, SecureBootSetup.SecureBootMode,SecureBootSetup.DefaultKeyProvision));

    // Clear "Show Boot Time Variables"
    NvramControl->ShowBootTimeVariables(FALSE);

}

//<AMI_PHDR_START>
//----------------------------------------------------------------------
// Procedure:   RestoreSecureVariables
//
// Description: Restore previous PK-KEK-db-dbx
//
// Input:       NONE
//
// Output:      NONE
//
// Returns:     NONE
//
//----------------------------------------------------------------------
//<AMI_PHDR_END>
VOID RestoreSecureVariables (VOID)
{
    EFI_STATUS  Status;
    UINT8       Index;
    EFI_GUID    *EfiVarGuid;

TRACE((TRACE_ALWAYS,"RestoreVar:\n"));
// 1. Restore Secure Boot variables.
    Index = 0;
    while(SecureVariableFileName[Index] != NULL)
    {
        if(SecureFlashVar[Index] && SecureFlashVarSize[Index])
        {
            if(Index < 3) 
                EfiVarGuid = &gEfiImageSecurityDatabaseGuid;
            else
                EfiVarGuid = &gEfiGlobalVariableGuid;

            Status = pRS->SetVariable(SecureVariableFileName[Index],
                    EfiVarGuid,
                    SecureFlashVarAttr[Index],
                    SecureFlashVarSize[Index], 
                    SecureFlashVar[Index]
            );
TRACE((TRACE_ALWAYS,"%S (%r) Size=%x Attr=%x\n", SecureVariableFileName[Index], Status, SecureFlashVarSize[Index], SecureFlashVarAttr[Index]));
            pSmst->SmmFreePool(SecureFlashVar[Index]);
            SecureFlashVar[Index] = NULL;
        }
        Index++;
    }
// 2. Restore Secure Boot Setup variables
    // Set "Show BootTime Variables" flag
    if (NvramControl == NULL) 
        return;
    // Set "Show BootTime Variables" flag
    NvramControl->ShowBootTimeVariables(TRUE);
    
    Status = pRS->SetVariable (AMI_SECURE_BOOT_SETUP_VAR, &guidSecurity,SecBootVar_Attr, sizeof(SECURE_BOOT_SETUP_VAR),&SecureBootSetup);
TRACE((TRACE_ALWAYS,"SecureBootSetup (%r)\n", Status));

    // Clear "Show Boot Time Variables"
    NvramControl->ShowBootTimeVariables(FALSE);

}
#endif //#if defined(PRESERVE_SECURE_VARIABLES) && PRESERVE_SECURE_VARIABLES==1
#endif // #ifdef SMIFLASH_COMPILE

//#############################################################################################################################
#ifdef SETUP_COMPILE
//#############################################################################################################################
#ifndef EFI_LEGACY_BIOS_PROTOCOL_GUID
//  ## Include/Protocol/LegacyBios.h
#define EFI_LEGACY_BIOS_PROTOCOL_GUID  \
{ 0xdb9a1e3d, 0x45cb, 0x4abb, { 0x85, 0x3b, 0xe5, 0x38, 0x7f, 0xdb, 0x2e, 0x2d }}
#endif

//<AMI_PHDR_START>
//----------------------------------------------------------------------------
//
// Procedure:    IsCsmEnabled
// 
// Description:  This function checks if CSM is enabled
//               
//  Input:
//     None
//
//  Output:
//  0 - CSM is disabled
//  1 - CSM is enabled
//
//----------------------------------------------------------------------------
//<AMI_PHDR_END>
BOOLEAN
IsCsmEnabled(VOID)
{
    EFI_STATUS Status;
    UINTN Size = sizeof(EFI_HANDLE);
    EFI_HANDLE Handle;
    static EFI_GUID EfiLegacyBiosProtocolGuid = EFI_LEGACY_BIOS_PROTOCOL_GUID;

    Status = pBS->LocateHandle(ByProtocol, &EfiLegacyBiosProtocolGuid, NULL, &Size, &Handle);
    return (EFI_ERROR(Status)) ? 0 : 1;
}

//<AMI_PHDR_START>
//----------------------------------------------------------------------------
// Procedure:   ForceSetupModeCallback
//
// Description: 
//
// Input:       none
//
// Output:      VOID
//
// Modified:
//
// Referrals:
//
// Notes:
//----------------------------------------------------------------------------
//<AMI_PHDR_END>
// 4.6.5.1
#if defined(CORE_COMBINED_VERSION) && CORE_COMBINED_VERSION >=0x4028b
EFI_STATUS
#else
VOID 
#endif
ForceSetupModeCallback(EFI_HII_HANDLE HiiHandle, UINT16 Class, UINT16 SubClass, UINT16 Key)
{
    EFI_STATUS  Status;
    UINT8       Sel = 0;
    UINTN       Size;
    UINT32      Attributes=0;

#if EFI_SPECIFICATION_VERSION>0x20000
    CALLBACK_PARAMETERS *Callback;
    EFI_BROWSER_ACTION_REQUEST *rq;

    Callback = GetCallbackParameters();
    TRACE((-1,"\n====ForceSetupModeCallback==== Key = %d, Callback %x, Value %d\n",  Key, Callback, Callback->Value->u8));
    if(!Callback || Callback->Action != EFI_BROWSER_ACTION_CHANGING)
        RETURN(EFI_UNSUPPORTED)
#endif
    if(mPostMgr == NULL)
    {
        Status = pBS->LocateProtocol(&gAmiPostManagerProtocolGuid, NULL, &mPostMgr);
        if(EFI_ERROR(Status) || !mPostMgr) {
            RETURN(EFI_UNSUPPORTED)
        }
    }
    Status = EFI_SUCCESS;
    switch(Key) {
        case  SECURE_BOOT_MENU_REFRESH:
            UpdateSecureBootBrowserInfo();
            break;
        case  KEY_MANAGEMENT_MENU_REFRESH:
            UpdateSecureVariableBrowserInfo();
            break;
#if EFI_SPECIFICATION_VERSION>0x20000
        case SECURE_BOOT_SUPPORT_CHANGE_KEY:
            if( Callback->Value->u8 == 1) // trying to switch Secure Boot from Disable to Enable
            {
                rq = Callback->ActionRequest;
                *rq = EFI_BROWSER_ACTION_REQUEST_NONE;
                Size = 1;
                Status=pRS->GetVariable(EFI_SETUP_MODE_NAME, &gEfiGlobalVariableGuid, (UINT32*)&Attributes, &Size, &Sel);
                if(Sel) {
                    GetHiiString(HiiHandle, STRING_TOKEN(STR_ENABLE_ERROR_MODE_TITLE), sizeof(StrTitle), StrTitle);
                    GetHiiString(HiiHandle, STRING_TOKEN(STR_ENABLE_ERROR_MODE), sizeof(StrMessage),StrMessage);
                    mPostMgr->DisplayMsgBox( StrTitle,  StrMessage, MSGBOX_TYPE_OK,NULL);
        #if DEFAULT_SECURE_BOOT_ENABLE == 0
                    Status = EFI_UNSUPPORTED;
        #endif
                }  else
                    if (IsCsmEnabled()) {
                        GetHiiString(HiiHandle, STRING_TOKEN(STR_CSM_LOAD_TITLE), sizeof(StrTitle),StrTitle);
                        GetHiiString(HiiHandle, STRING_TOKEN(STR_CSM_LOAD), sizeof(StrMessage),StrMessage);
                        mPostMgr->DisplayMsgBox( StrTitle,  StrMessage, MSGBOX_TYPE_OK,NULL);
/* this should be enough, but TSE has a bug that doesn't support FORM_DISCARD action try a workaround instead 
                       {
                           SETUP_DATA Setup;
                           UINTN Size = sizeof(Setup);
                           static EFI_GUID SetupGuid = SETUP_GUID;
                           Status = HiiLibGetBrowserData(&Size, &Setup, &SetupGuid, L"Setup");
                            TRACE((-1, "Setup.CsmSupport=: %x, Size = %x\n", Setup.CsmSupport, Size));
                           if(!EFI_ERROR(Status) && Setup.CsmSupport == 1) {
                               GetHiiString(HiiHandle, STRING_TOKEN(STR_CSM_LOAD_TITLE), sizeof(StrTitle),StrTitle);
                               GetHiiString(HiiHandle, STRING_TOKEN(STR_CSM_LOAD), sizeof(StrMessage),StrMessage);
                               mPostMgr->DisplayMsgBox( StrTitle,  StrMessage, (UINT8)MSGBOX_TYPE_YESNO, &Sel);
                               if (Sel == 1) {
                                   Setup.CsmSupport = 0;
                                   Status = HiiLibSetBrowserData(Size, &Setup, &SetupGuid, L"Setup");
//                                    pRS->SetVariable ( L"Setup", &SetupGuid, Attributes, Size, &Setup);                                   
                               }
                           }
                       }
end of workaround */
                        
        #if DEFAULT_SECURE_BOOT_ENABLE == 0
                       Status = EFI_UNSUPPORTED;
        #endif
                    }
            }
            break;
#endif
        case SECURE_BOOT_MODE_CHANGE_KEY:
            if( Callback->Value->u8 == 1) // trying to switch from Custom to Standard
                break;
        case KEY_PROVISION_CHANGE_KEY:
            if(Key == KEY_PROVISION_CHANGE_KEY && 
                Callback->Value->u8 == 0) // trying to switch from Disable to Enable
                break;
        case FORCE_SETUP_KEY:
        case FORCE_DEFAULT_KEY:
            if (Key == FORCE_SETUP_KEY)
            {
                GetHiiString(HiiHandle, STRING_TOKEN(STR_FORCE_SETUP_MODE), sizeof(StrTitle),StrTitle);
                GetHiiString(HiiHandle, STRING_TOKEN(STR_RESET_TO_SETUP), sizeof(StrMessage),StrMessage);
                mPostMgr->DisplayMsgBox( StrTitle,  StrMessage, (UINT8)MSGBOX_TYPE_YESNO, &Sel);
                if (Sel == 0)
                   Status = InstallSecureVariables(RESET_NV_KEYS);    // erase
            }
#if SET_SECURE_VARS == 1
            if (Key == FORCE_DEFAULT_KEY || Key == KEY_PROVISION_CHANGE_KEY || Key == SECURE_BOOT_MODE_CHANGE_KEY)
            {
                GetHiiString(HiiHandle, STRING_TOKEN(STR_LOAD_DEFAULT_VARS_TITLE), sizeof(StrTitle),StrTitle);
                GetHiiString(HiiHandle, STRING_TOKEN(STR_LOAD_DEFAULT_VARS), sizeof(StrMessage),StrMessage);
                mPostMgr->DisplayMsgBox( StrTitle,  StrMessage, (UINT8)MSGBOX_TYPE_YESNO, &Sel);
                if (Sel == 0)
                    Status = InstallSecureVariables(RESET_NV_KEYS | SET_NV_DEFAULT_KEYS);    // erase+set
            }
#endif
            UpdateSecureVariableBrowserInfo();
            if (EFI_ERROR(Status))
            {
                GetHiiString(HiiHandle, STRING_TOKEN(STR_VAR_UPDATE_LOCKED_TITLE), sizeof(StrTitle),StrTitle);
                GetHiiString(HiiHandle, STRING_TOKEN(STR_VAR_UPDATE_LOCKED), sizeof(StrMessage),StrMessage);
                mPostMgr->DisplayMsgBox( StrTitle,  StrMessage, MSGBOX_TYPE_OK,NULL);
                Status = EFI_SUCCESS;
            }
            break;

        default: 
            break;   
    }
    RETURN(Status)
}
// ==========================================
// (4.6.5.0+)
// #if defined(CORE_COMBINED_VERSION) && CORE_COMBINED_VERSION >=0x4028a
// ==========================================

EFI_STATUS SetSecureVariable(UINT8 Index, UINT16 InstallVars, UINT8 *pVarBuffer, UINTN VarSize )
{
    EFI_STATUS  Status = EFI_SUCCESS;
    EFI_GUID    *EfiVarGuid;
    UINT32      Attributes;

///////////////////////////////////////////////////////////////////////////////
// Initial provisioning of Authenticated non-volitile EFI Variables 
///////////////////////////////////////////////////////////////////////////////
    if(SecureVariableFileName[Index] != NULL)
    {
        if(Index < 3) 
            EfiVarGuid = &gEfiImageSecurityDatabaseGuid;
        else
            EfiVarGuid = &gEfiGlobalVariableGuid;

        if((InstallVars & SET_SECURE_VARIABLE_DEL) == SET_SECURE_VARIABLE_DEL) {
        // try to erase. should succeed if system in pre-boot and Admin mode
            Status = pRS->SetVariable(SecureVariableFileName[Index],EfiVarGuid,0,0,NULL);
            TRACE((-1,"Set(0) Var %S, Status %r\n",SecureVariableFileName[Index], Status));
        }
        if((InstallVars & SET_SECURE_VARIABLE_SET)==SET_SECURE_VARIABLE_SET &&
            pVarBuffer && VarSize) {

            Attributes = EFI_VARIABLE_RUNTIME_ACCESS |
                         EFI_VARIABLE_NON_VOLATILE | 
                         EFI_VARIABLE_BOOTSERVICE_ACCESS |
                         EFI_VARIABLE_TIME_BASED_AUTHENTICATED_WRITE_ACCESS; 

            if((InstallVars & SET_SECURE_VARIABLE_APPEND)== SET_SECURE_VARIABLE_APPEND)
                Attributes |= EFI_VARIABLE_APPEND_WRITE;

            Status = pRS->SetVariable(SecureVariableFileName[Index], EfiVarGuid, Attributes, VarSize, pVarBuffer);
            TRACE((-1,"Set Var %S, Status %r\n",SecureVariableFileName[Index], Status));
        }
    }

    UpdateSecureVariableBrowserInfo();

    return Status;
}

//<AMI_PHDR_START>
//----------------------------------------------------------------------------
// Procedure:   GetHiiString
//
// Description: This function Reads a String from HII
//
// Input:       IN EFI_HII_HANDLE   HiiHandle - Efi Hii Handle
//              IN STRING_REF       Token     - String Token
//              IN OUT UINTN        *pDataSize - Length of the StringBuffer
//              OUT EFI_STRING      *ppData - The buffer to receive the characters in the string.
//
// Output:      EFI_STATUS - Depending on result
//
//----------------------------------------------------------------------------
//<AMI_PHDR_END>
VOID GetHiiString(
    IN EFI_HII_HANDLE HiiHandle,
    IN STRING_REF Token,
    IN  UINTN DataSize,
    IN OUT CHAR16  *ppData
    )
{
    EFI_STATUS Status;

    if (!ppData) return;
    
    Status = HiiLibGetString(HiiHandle, Token, &DataSize, (EFI_STRING)ppData);
    ASSERT_EFI_ERROR (Status);
    if (EFI_ERROR (Status)) ppData=L"??? ";

TRACE((-1,"%r, StrRef '%S', Size %d, Token=%d\n",Status, ppData, DataSize, Token));
}

// 4.6.5.1
#if defined(CORE_COMBINED_VERSION) && CORE_COMBINED_VERSION >=0x4028b
EFI_STATUS
#else
VOID 
#endif
SetAppendSecureBootDBCallback(EFI_HII_HANDLE HiiHandle, UINT16 Class, UINT16 SubClass, UINT16 Key)
{
    EFI_STATUS Status;
    EFI_HANDLE *FsHandle;
    UINT8 *FileBuf=NULL;
    UINT8 *Data=NULL;
    UINTN size, VarSize;
    CHAR16 *FilePath=NULL;
    UINT8 index;
    UINT8 Sel = 1;
    UINT16 CertSel = 0, AddSize;
    POSTMENU_TEMPLATE MenuList[2];
    UINT8  VarSetMode = SET_SECURE_VARIABLE_SET;

#if EFI_SPECIFICATION_VERSION>0x20000
    CALLBACK_PARAMETERS *Callback;

    Callback = GetCallbackParameters();
    if(!Callback || Callback->Action != EFI_BROWSER_ACTION_CHANGING)
        RETURN(EFI_UNSUPPORTED)
#endif

    switch(Key)
    {
    case APPEND_KEK_KEY:
                    index = 3;
                    VarSetMode |= SET_SECURE_VARIABLE_APPEND;
                    break;
    case APPEND_DB_KEY:
                    index = 2;
                    VarSetMode |= SET_SECURE_VARIABLE_APPEND;
                    break;
    case APPEND_DBT_KEY:
                    index =1;
                    VarSetMode |= SET_SECURE_VARIABLE_APPEND;
                    break;
    case APPEND_DBX_KEY:
                    index = 0;
                    VarSetMode |= SET_SECURE_VARIABLE_APPEND;
                    break;
    case SET_PK_KEY:
                    index = 4;
                    VarSetMode |= SET_SECURE_VARIABLE_DEL;
                    break;
    case SET_KEK_KEY:
                    index = 3;
                    VarSetMode |= SET_SECURE_VARIABLE_DEL;
                    break;
    case SET_DB_KEY:
                    index = 2;
                    VarSetMode |= SET_SECURE_VARIABLE_DEL;
                    break;
    case SET_DBT_KEY:
                    index = 1;
                    VarSetMode |= SET_SECURE_VARIABLE_DEL;
                    break;
    case SET_DBX_KEY:
                    index = 0;
                    VarSetMode |= SET_SECURE_VARIABLE_DEL;
                    break;
    default:
        RETURN(EFI_SUCCESS)
    }

    if(mPostMgr == NULL)
    {
        RETURN(EFI_SUCCESS)
    }

    gHiiHandle = HiiHandle;

    MemSet(StrTemp, sizeof(StrTemp), 0);

#if SET_SECURE_VARS == 1
    Sel = 1; // No
//    DataSize = sizeof(StrTitle);
    if(VarSetMode & SET_SECURE_VARIABLE_APPEND)
//        HiiLibGetString(HiiHandle, STRING_TOKEN(STR_SECURE_APPEND), &DataSize, (EFI_STRING)StrTitle);
        GetHiiString(HiiHandle, STRING_TOKEN(STR_SECURE_APPEND), sizeof(StrTitle), StrTitle);
    else
        GetHiiString(HiiHandle, STRING_TOKEN(STR_SECURE_SET), sizeof(StrTitle), StrTitle);

    GetHiiString(HiiHandle, STRING_TOKEN(STR_UPDATE_FROM_DEFAULTS),sizeof(StrMessage), StrMessage);
    Swprintf_s(StrTemp, sizeof(StrTemp), StrMessage ,  SecureVariableFileName[index]);
    mPostMgr->DisplayMsgBox( StrTitle, StrTemp, (UINT8)MSGBOX_TYPE_YESNO, &Sel);

    if(Sel == 0)
    {
        size = 0 ; 
        Status = CryptoGetRawImage( SecureVariableFileGuid[index], &FileBuf, (UINTN*)&size);
    } else
#endif
    {
        size = 0;
        AddSize = 0;
        Status = FileBrowserLaunchFileSystem(TRUE, &FsHandle, &FilePath, &FileBuf, &size);
        if(!EFI_ERROR(Status) && FileBuf)
        {
            // Clear the memory allocated 
            MemSet(MenuList, sizeof(MenuList), 0);
            MenuList[0].ItemToken = STRING_TOKEN(STR_SECURE_CER);
            MenuList[1].ItemToken = STRING_TOKEN(STR_SECURE_VAR);
    
            // Call post manager to display the menu
            Status = mPostMgr->DisplayPostMenu(gHiiHandle,
                                                STRING_TOKEN(STR_SECURE_TITLE), // Change this
                                                0,
                                                MenuList,
                                                2,
                                                &CertSel);
    
            if(!EFI_ERROR(Status))
            {
                GetHiiString(HiiHandle, STRING_TOKEN(STR_UPDATE_FROM_FILE), sizeof(StrMessage), StrMessage);
                Swprintf_s(StrTemp, sizeof(StrTemp),StrMessage, SecureVariableFileName[index],FilePath);

                if(CertSel==0) {
                    AddSize = sizeof(EFI_VARIABLE_SIG_HDR_2)-1; // decrement by 1 byte as SIG_DATA adds 1 dummy byte
                }
        
                // Validate Signature List integrity 
                if(!EFI_ERROR(ValidateSignatureList (FileBuf, size))) {
                    CertSel=2;
                    AddSize = sizeof(AMI_EFI_VARIABLE_AUTHENTICATION_2);
                }
                //
                // form an AuthVar Hdr on top of Var
                //
                //Allocate new Size
                VarSize = size+AddSize;
                Status = pBS->AllocatePool(EfiBootServicesData, VarSize, &Data);
                ASSERT_EFI_ERROR (Status);
                // Append AuthHdr to Var data.
                if(CertSel==0)
                    FillAuthVarHdr(Data,FileBuf,size, VarSetMode);
                else 
                    if(CertSel==2) // unsupported - append from SigList
                    FillAuthHdr(Data, VarSetMode);

                MemCpy ((VOID*)((UINTN)Data+AddSize), FileBuf, size);
                if(FileBuf)
                    pBS->FreePool(FileBuf);
                FileBuf = Data;
                size = VarSize;
            }
        }
    }

    if(!EFI_ERROR(Status) && FileBuf){
        if(Sel == 1)
            mPostMgr->DisplayMsgBox( StrTitle, StrTemp, (UINT8)MSGBOX_TYPE_YESNO, &Sel);

        if(Sel == 0)
        {
            Status = SetSecureVariable(index, VarSetMode, FileBuf, size);
            if(!EFI_ERROR(Status)){
                GetHiiString(HiiHandle, STRING_TOKEN(STR_SUCCESS), sizeof(StrMessage),StrMessage);
            }
            else
            {
                GetHiiString(HiiHandle, STRING_TOKEN(STR_FAILED), sizeof(StrMessage),StrMessage);
            }
            mPostMgr->DisplayMsgBox( StrTitle,StrMessage , MSGBOX_TYPE_OK, NULL );
        }
    }
    if(FileBuf)
        pBS->FreePool(FileBuf);

    if(FilePath)
        pBS->FreePool(FilePath);
        
     RETURN(EFI_SUCCESS)
}
// 4.6.5.1
#if defined(CORE_COMBINED_VERSION) && CORE_COMBINED_VERSION >=0x4028b
EFI_STATUS
#else
VOID 
#endif
GetSecureBootDBCallback(EFI_HII_HANDLE HiiHandle, UINT16 Class, UINT16 SubClass, UINT16 Key)
{
    EFI_STATUS Status;
    EFI_HANDLE *FsHandle;
    UINT8 *FileBuf=NULL;
    UINTN size;
    CHAR16 *FilePath=NULL;
    UINT8 Index, nVars;
    EFI_SIMPLE_FILE_SYSTEM_PROTOCOL *pSFP;
    EFI_FILE_PROTOCOL *pRoot,*FileHandle;
    EFI_GUID    *EfiVarGuid;
    UINT8       *Data=NULL;
    BOOLEAN     bFound = TRUE;

#if EFI_SPECIFICATION_VERSION>0x20000
    CALLBACK_PARAMETERS *Callback;

    Callback = GetCallbackParameters();
    if(!Callback || Callback->Action != EFI_BROWSER_ACTION_CHANGING)
        RETURN(EFI_UNSUPPORTED)
#endif

    gHiiHandle = HiiHandle;
    size = 0;
    Status = FileBrowserLaunchFileSystem(FALSE, &FsHandle, &FilePath, &FileBuf, &size);
    if(EFI_ERROR(Status))
       goto Done;

    Index = 0;
    nVars = 0;
    MemSet(StrTemp, sizeof(StrTemp), 0);
    while(bFound && SecureVariableFileName[Index] != NULL)
    {
        if(Index < 3) 
            EfiVarGuid = &gEfiImageSecurityDatabaseGuid;
        else
            EfiVarGuid = &gEfiGlobalVariableGuid;

        size = 0;  
        Status = pRS->GetVariable( SecureVariableFileName[Index], EfiVarGuid, NULL, &size, NULL);
        if(Status == EFI_BUFFER_TOO_SMALL)
        {
            // Append AuthHdr to Var data.
            //Allocate Size
            Status = pBS->AllocatePool(EfiBootServicesData, size, &Data);
            ASSERT_EFI_ERROR (Status);

            // Read the Variable
            Status = pRS->GetVariable( SecureVariableFileName[Index], EfiVarGuid, NULL, &size, Data);
            if (!EFI_ERROR(Status)) 
            {
                Status = pBS->HandleProtocol( FsHandle, &gSimpleFileSystemGuid, &pSFP );
                if (!EFI_ERROR(Status)) 
                {
                    Status = pSFP->OpenVolume(pSFP,&pRoot);
                    if (!EFI_ERROR(Status)) 
                    {
                        Status = pRoot->Open(pRoot,&FileHandle,SecureVariableFileName[Index],
                            EFI_FILE_MODE_READ | EFI_FILE_MODE_WRITE | EFI_FILE_MODE_CREATE,0);
                        if(!EFI_ERROR(Status))
                        {
                            // Write
                            FileHandle->Write(FileHandle,&size, Data);
                            FileHandle->Close(FileHandle);
                            nVars++;
                        }
                    }
                }
    
               if (EFI_ERROR(Status)) {
                    bFound = FALSE;
                    Swprintf_s(StrTemp, sizeof(StrTemp), L" %s ", SecureVariableFileName[Index]);
                    GetHiiString(HiiHandle, STRING_TOKEN(STR_WRITE_ERROR_TITLE), sizeof(StrTitle),StrTitle);
                    mPostMgr->DisplayMsgBox( StrTitle, StrTemp, MSGBOX_TYPE_OK, NULL );
                }
            }
            if(Data!=NULL)
                pBS->FreePool(Data);
        }

        Index++;
    }
    if (Index==5 && bFound) {
        GetHiiString(HiiHandle, STRING_TOKEN(STR_SAVE_SEC_KEY),sizeof(StrMessage), StrMessage);
        Swprintf_s(StrTemp, sizeof(StrTemp), StrMessage, nVars);
        GetHiiString(HiiHandle, STRING_TOKEN(STR_SAVE_SEC_KEY_TITLE),sizeof(StrTitle), StrTitle);
        mPostMgr->DisplayMsgBox(StrTitle , StrTemp, MSGBOX_TYPE_OK, NULL );
    }

Done:
 
    if(FileBuf)
        pBS->FreePool(FileBuf);

    if(FilePath)
        pBS->FreePool(FilePath);

    RETURN(EFI_SUCCESS)
}

// 4.6.5.1
#if defined(CORE_COMBINED_VERSION) && CORE_COMBINED_VERSION >=0x4028b
EFI_STATUS
#else
VOID 
#endif
DeleteSecureBootDBCallback(EFI_HII_HANDLE HiiHandle, UINT16 Class, UINT16 SubClass, UINT16 Key)
{
    EFI_STATUS Status;
    UINT8 index;
    UINT8 Sel = 0;    

#if EFI_SPECIFICATION_VERSION>0x20000
    CALLBACK_PARAMETERS *Callback;

    Callback = GetCallbackParameters();
    if(!Callback || Callback->Action != EFI_BROWSER_ACTION_CHANGING)
        RETURN(EFI_UNSUPPORTED)
#endif

    switch(Key)
    {
    case DELETE_PK_KEY:
                    index = 4;
                    break;
    case DELETE_KEK_KEY:
                    index = 3;
                    break;
    case DELETE_DB_KEY:
                    index = 2;
                    break;
    case DELETE_DBT_KEY:
                    index = 1;
                    break;
    case DELETE_DBX_KEY:
                    index = 0;
                    break;
    default:
        RETURN(EFI_SUCCESS)
    }

    if(mPostMgr == NULL)
    {
         RETURN(EFI_SUCCESS)
    }

    gHiiHandle = HiiHandle;

    MemSet(StrTemp, sizeof(StrTemp), 0);
    
    GetHiiString(HiiHandle, STRING_TOKEN(STR_DELETE_SEC_KEY_TITLE), sizeof(StrTitle),StrTitle);
    GetHiiString(HiiHandle, STRING_TOKEN(STR_DELETE_SEC_KEY), sizeof(StrMessage),StrMessage);
    Swprintf_s(StrTemp, sizeof(StrTemp), StrMessage, SecureVariableFileName[index]);
    mPostMgr->DisplayMsgBox( StrTitle,  StrTemp, (UINT8)MSGBOX_TYPE_YESNO, &Sel);

    if(Sel == 0)
    {
        Status = SetSecureVariable(index,SET_SECURE_VARIABLE_DEL, NULL, 0);

        if(!EFI_ERROR(Status)){
            GetHiiString(HiiHandle, STRING_TOKEN(STR_SUCCESS), sizeof(StrMessage),StrMessage);
        }
        else
        {
            GetHiiString(HiiHandle, STRING_TOKEN(STR_FAILED), sizeof(StrMessage),StrMessage);
        }            
        mPostMgr->DisplayMsgBox( StrTitle, StrMessage, MSGBOX_TYPE_OK, NULL );
    }

    RETURN(EFI_SUCCESS)
}
//############################################################################################################
static VOID EfiStrCat (
    IN CHAR16   *Destination,
    IN CHAR16   *Source
    )
{   
    Wcscpy (Destination + Wcslen (Destination), Source);
}

static CHAR16 *StrDup8to16( CHAR8 *string )
{
    CHAR16  *text;
    UINTN   i;

    if ( string == NULL )
        return NULL;

    pBS->AllocatePool(EfiBootServicesData, (1 + Strlen( string )) * sizeof(CHAR16), &text);

    if ( text != NULL )
    {
        i=0;
        while(text[i] = (CHAR16)string[i])
            i++;
    }

    return text;
}
 

EFI_STRING_ID HiiAddString(IN EFI_HII_HANDLE HiiHandle,IN CHAR16 *String)
{
    EFI_STATUS Status;
    CHAR8* Languages = NULL;
    UINTN LangSize = 0;
    CHAR8* CurrentLanguage;
    BOOLEAN LastLanguage = FALSE;
    EFI_STRING_ID  StringId = 0;
    CHAR8          *SupportedLanguages=NULL;

    if(HiiString == NULL) {
        Status = pBS->LocateProtocol(&gEfiHiiStringProtocolGuid, NULL, (VOID **) &HiiString);
        if(EFI_ERROR(Status))
            return 0;
    }

    if(SupportedLanguages == NULL) {
        Status = HiiString->GetLanguages(HiiString, HiiHandle, Languages, &LangSize);
        if(Status == EFI_BUFFER_TOO_SMALL) {
            Status = pBS->AllocatePool(EfiBootServicesData, LangSize, &Languages);
            if(EFI_ERROR(Status))
                return 0;        //not enough resources to allocate string
            Status = HiiString->GetLanguages(HiiString, HiiHandle, Languages, &LangSize);
        }
        if(EFI_ERROR(Status))
            return 0;
    } else {
        Languages = SupportedLanguages;
     }

    while(!LastLanguage) {
        CurrentLanguage = Languages;        //point CurrentLanguage to start of new language
        while(*Languages != ';' && *Languages != 0)
            Languages++;

        if(*Languages == 0) {       //last language in language list
            LastLanguage = TRUE;
            if(StringId == 0)
                Status = HiiString->NewString(HiiString, HiiHandle, &StringId, CurrentLanguage, NULL, String, NULL);
            else
                Status = HiiString->SetString(HiiString, HiiHandle, StringId, CurrentLanguage, String, NULL);
            if(EFI_ERROR(Status))
                return 0;
        } else {
            *Languages = 0;         //put null-terminator
            if(StringId == 0)
                Status = HiiString->NewString(HiiString, HiiHandle, &StringId, CurrentLanguage, NULL, String, NULL);
            else
                Status = HiiString->SetString(HiiString, HiiHandle, StringId, CurrentLanguage, String, NULL);
            *Languages = ';';       //restore original character
            Languages++;
            if(EFI_ERROR(Status))
                return 0;
        }
    }
    return StringId;        
}


//<AMI_PHDR_START>
//----------------------------------------------------------------------------
// Procedure:    EfiLibAllocateCopyPool
//
// Description:    Allocate BootServicesData pool and use a buffer provided by 
//                    caller to fill it.
//
// Input:    AllocationSize  - The size to allocate
//                    Buffer          - Buffer that will be filled into the buffer allocated
//
// Output:    Pointer of the buffer allocated.
//
//----------------------------------------------------------------------------
//<AMI_PHDR_END>
VOID *
EfiLibAllocateCopyPool (
  IN  UINTN   AllocationSize,
  IN  VOID    *Buffer
  )
{
    VOID  *Memory;
    
    Memory = NULL;
    pBS->AllocatePool (EfiBootServicesData, AllocationSize, &Memory);
    if (Memory != NULL) {
        pBS->CopyMem (Memory, Buffer, AllocationSize);
    }
    
    return Memory;
}

//<AMI_PHDR_START>
//----------------------------------------------------------------------
// Procedure:   CleanFileTypes
//
// Description: Frees all allocated memory associated with the FILE_TYPE structure
//      and resets the InternalString current strings next available string token
//      to be the first dynamically added string
//
// Input:   FILE_TYPE **FileList - The array of FILE_TYPE structures found in 
//              a directory
//          UINTN *FileCount - pointer to the number of entries in the FileList
//
// Output:
//
// Returns:
//
//----------------------------------------------------------------------
//<AMI_PHDR_END>
VOID CleanFileTypes(FILE_TYPE **FileList, UINTN *FileCount)
{
    UINTN i;
    for(i = 0; i<*FileCount; i++) pBS->FreePool((*FileList)[i].Name);
    if(FileList!=NULL && (*FileList!=NULL) && (*FileCount>0)) pBS->FreePool(*FileList);
    if(FileList!=NULL) *FileList = NULL;
    *FileCount = 0;
}
//<AMI_PHDR_START>
//----------------------------------------------------------------------
// Procedure:   CheckDirectoryType
//
// Description: Checks if the EFI_FILE_INFO is a directory (and not the current directory)
//
// Input:   EFI_FILE_INFO *File
//
// Output:  
//
// Returns: BOOLEAN - TRUE - item is a directory, and not the current directory
//                    FALSE - item is not a directory, or is the current directory
//
//----------------------------------------------------------------------
//<AMI_PHDR_END>
BOOLEAN CheckDirectoryType(EFI_FILE_INFO *File)
{
    BOOLEAN Status = FALSE;

    if((File->Attribute & EFI_FILE_DIRECTORY) && (Wcscmp(File->FileName, L".") != 0)) {

        Status = TRUE;
    }

    return Status;
}

//<AMI_PHDR_START>
//----------------------------------------------------------------------
// Procedure:   CheckExtension
//
// Description: Check is the EFI_FILE_INFO has the same extension as the 
//      extension passed in the second parameter
//
// Input:   EFI_FILE_INFO *File - The file entry whose extension should be checked
//          CHAR16 *ExtensionEfi - the extension
//
// Output:
//
// Returns: BOOLEAN - TRUE - The extension matches
//                    FALSE - the extension does not match
//
//----------------------------------------------------------------------
//<AMI_PHDR_END>
BOOLEAN CheckExtension(EFI_FILE_INFO *File, CHAR16 *ExtensionEfi)
{
    BOOLEAN Status = FALSE;
    UINTN Length = Wcslen(File->FileName);

    if((File->Attribute & EFI_FILE_DIRECTORY) != EFI_FILE_DIRECTORY && Length > 3)
        if((((File->FileName[Length-1])&0xdf) == ((ExtensionEfi[2])&0xdf)) &&
           (((File->FileName[Length-2])&0xdf) == ((ExtensionEfi[1])&0xdf)) &&
           (((File->FileName[Length-3])&0xdf) == ((ExtensionEfi[0])&0xdf)))
            Status = TRUE;
    return Status;    
}

//<AMI_PHDR_START>
//----------------------------------------------------------------------
// Procedure:   FindInsertionIndex
//
// Description: Finds the inded where directories items turn into file items
//
// Input:   FILE_TYPE *List - the current array of File Type structures
//          UINTN FileCount - the count of File Type structures in the array
//
// Output:
//
// Returns: the index to insert a new item
//
//----------------------------------------------------------------------
//<AMI_PHDR_END>
UINTN FindInsertionIndex(FILE_TYPE *List, UINTN FileCount)
{
    UINTN i = 0;
    
    if(FileCount <= 1) return 0;

    for(i = 1; i < (FileCount-1); i++)
    {
        if(List[i-1].Type != List[i].Type)
        break;
    }

    return i;
}

//<AMI_PHDR_START>
//----------------------------------------------------------------------
// Procedure:   AddFileTypeEntry
//
// Description: Creates a new entry in the FILE_TYPE array and adds the current File into
//      the array.
//
// Input:   FILE_TYPE **List - Array of FILE_TYPE structures alread found
//          UINTN *FileCount - number of entries in the FILE_TYPE array
//          EFI_FILE_INFO *FileInfo - file info of the file that should be added
//
// Output:
//
// Returns:
//
//----------------------------------------------------------------------
//<AMI_PHDR_END>
static VOID AddFileTypeEntry(FILE_TYPE **List, UINTN *FileCount, EFI_FILE_INFO *FileInfo)
{
    FILE_TYPE *NewList=NULL;
    UINTN Length;
    UINTN Index = 0;

    Length = (Wcslen(FileInfo->FileName)+3)*sizeof(CHAR16);

    // Allocate space for a new list entry plus all the previous list items
    NewList = EfiLibAllocateCopyPool(sizeof(FILE_TYPE)*(++(*FileCount)), NewList);
    if (NewList != NULL) 
    {
        // Clear the memory of the entire list
        MemSet(NewList, sizeof(FILE_TYPE)*(*FileCount), 0);
    
        // Copy the old entries (if there are any old entries to copy)
        if(*List != NULL) 
        {
            Index = FindInsertionIndex(*List, *FileCount);

            pBS->CopyMem(NewList, *List, sizeof(FILE_TYPE)*(Index));
            pBS->CopyMem(&(NewList[Index+1]), &((*List)[Index]), sizeof(FILE_TYPE)*((*FileCount)-Index-1));

            pBS->FreePool(*List);
        }

        // Store the type of this FILE_TYPE entry (non-zero is directory)
        NewList[Index].Type = ((FileInfo->Attribute) & EFI_FILE_DIRECTORY);

        // Store the size of the file
        NewList[Index].Size = (UINTN)FileInfo->FileSize;

        // Allocate space for the string
        NewList[Index].Name = EfiLibAllocateCopyPool(Length, NewList[Index].Name);
        if((NewList[Index].Name) != NULL )
        {
            // Clear the allocated memory
            MemSet(NewList[Index].Name, Length, 0);

            // Create either a Dir string or a File string for addition to the HiiDataBase
            if(NewList[Index].Type == EFI_FILE_DIRECTORY)
                 Swprintf_s(NewList[Index].Name, Length, L"<%s>", FileInfo->FileName);
            else
                 Swprintf_s(NewList[Index].Name, Length, L"%s", FileInfo->FileName);

            // Add the string to the HiiDataBase
            ///NewList[Index].Token = AddStringToHii(FileInfo->FileName, &gInternalStrings);    ///Just by trying using the following line
            NewList[Index].Token =     HiiAddString(gHiiHandle, NewList[Index].Name );

            // Clear the memory and create the string for the File Structure
            MemSet(NewList[Index].Name, Length, 0);
             Swprintf_s(NewList[Index].Name, Length, L"%s", FileInfo->FileName);            
        }
        *List = NewList;
    }
}

//<AMI_PHDR_START>
//----------------------------------------------------------------------
// Procedure:   CreateFileList
//
// Description: Parse all the files in the current directory and add valid files to the
//      FILE_TYPE list and update the filecount
//
// Input:   EFI_FILE_PROTOCOL *FileProtocol - the current direcotry to parse
//
// Output:  FILE_TYPE **FileList - pointer in which to return the array of FileType items
//          UINTN *FileCount - the count of filetype items discovered
//
// Returns: EFI_STATUS
//
//----------------------------------------------------------------------
//<AMI_PHDR_END>
static EFI_STATUS CreateFileList(EFI_FILE_PROTOCOL *FileProtocol, FILE_TYPE **FileList, UINTN *FileCount)
{
    EFI_STATUS Status = EFI_SUCCESS;

    UINTN   BufferSize = 1;
    EFI_FILE_INFO *File = NULL;

//    CHAR16 ExtensionEfi[] = L"EFI";

    // Continue parsing the directory until we no longer read valid files
    while(BufferSize != 0 && !EFI_ERROR(Status))
    {
        BufferSize = 0;
        Status = FileProtocol->Read(FileProtocol, &BufferSize, NULL);

        if(!EFI_ERROR(Status)) break;

        if(Status == EFI_BUFFER_TOO_SMALL)
        {
            File = EfiLibAllocateCopyPool(BufferSize, File);
            if(File != NULL) {
                    MemSet(File, BufferSize, 0);
                }
        }

        Status = FileProtocol->Read(FileProtocol, &BufferSize, File);

        // Check if a valid file was read
        if(!EFI_ERROR(Status) && BufferSize != 0)
        {
            // check if the file read was a directory or a ".efi" extension
//            if(CheckDirectoryType(File) ||  CheckExtension(File, ExtensionEfi))
//            {
                // the file was valid, add it to the file list
                AddFileTypeEntry(FileList, FileCount, File);
//            }
        }

        // free the space allocated for readin the file info structure
        pBS->FreePool(File);

        // set the pointer to null to prevent the chance of memory corruption
        File = NULL;
    }

    if(*FileCount == 0) Status = EFI_NOT_FOUND;

    return Status;
}

//<AMI_PHDR_START>
//----------------------------------------------------------------------
// Procedure:   DisplayFileListMenu
//
// Description: Display a menu of the FILE_TYPE items and return the selected item
//              in the Selection
//
// Input:   FILE_TYPE *FileList - List of FILE_TYPE items to display in the menu
//          UINTN FileCount - the number of FILE_TYPE items in the list
//
// Output:  UINT16 *Selection - The index of the selected FILE_TYPE item
//
// Returns:
//
//----------------------------------------------------------------------
//<AMI_PHDR_END>
static EFI_STATUS DisplayFileListMenu(FILE_TYPE *FileList, UINTN FileCount, UINT16 *Selection)
{
    EFI_STATUS Status = EFI_SUCCESS;

    UINT16 i = 0;

    POSTMENU_TEMPLATE *List = NULL;

    // Check there are any files to display
    if(FileCount != 0 && FileList != NULL)
    {
        // allocate space for the POSTMENU_TEMPLATE items
        List = EfiLibAllocateCopyPool(sizeof(POSTMENU_TEMPLATE)*FileCount, List);
        if(List != NULL)
        {
            // Clear the memory allocated 
            MemSet(List, sizeof(POSTMENU_TEMPLATE)*FileCount, 0);

            // Add the STRING_REF tokens to the POSTMENU_TEMPLATE structures
            for(i = 0; i < FileCount; i++)
                List[i].ItemToken = FileList[i].Token;
        }

        // Call post manager to display the menu
        Status = mPostMgr->DisplayPostMenu(gHiiHandle,
                                            STRING_TOKEN(STR_FILE_SELECT), // Change this
                                            0,
                                            List,
                                            (UINT16)FileCount,
                                            Selection);
    }
    return Status;
}

//<AMI_PHDR_START>
//----------------------------------------------------------------------
// Procedure:   UpdateFilePathString
//
// Description: To create the File Path string based on the file selected.
//
// Input:   CHAR16 *FilePath  - Buffer to fill with the file path
//          CHAR16 * CurFile  - current file selected
//          UINT16 idx        - Index of the file in the current directory
//
// Output:  CHAR16 *FilePath - Updated File Path
//
// Returns:
//
//----------------------------------------------------------------------
//<AMI_PHDR_END>
VOID UpdateFilePathString(CHAR16 *FilePath, CHAR16 * CurFile, UINT16 idx)
{
    UINTN Length=0;

    if(Wcslen(FilePath))
    {
        if( idx==0 ) {
            if(Wcscmp(CurFile,L".."))  {
                EfiStrCat(FilePath,L"\\");
                EfiStrCat(FilePath,CurFile);
            }
            else {
                
                for ( Length = Wcslen(FilePath); ( Length!= 0 ) && (FilePath[Length-1] != L'\\') ; Length -- ); 
                    if ( Length )
                        FilePath[Length-1] = L'\0';
                    else
                        FilePath[Length] = L'\0';    
            }
        }
        else {
            EfiStrCat(FilePath,L"\\");
            EfiStrCat(FilePath,CurFile);
        }
    }
    else {
        Wcscpy(FilePath,CurFile);
    }
}

EFI_STATUS FileBrowserLaunchFilePath(IN EFI_HANDLE *FileHandle, OUT CHAR16 **outFilePath, OUT UINT8 **outFileBuf,OUT UINTN *size );

//<AMI_PHDR_START>
//----------------------------------------------------------------------
// Procedure:   FileBrowserLaunchFileSystem
//
// Description: To select the File System for the new boot option with the help of file browser.
//
// Input:   BOOLEAN bSelectFile - TRUE  - Select FSHandle and File path
//                                FALSE - Select only FSHandle
//
// Output:  Selected File System Index
//
// Returns: EFI_STATUS
//
//----------------------------------------------------------------------
//<AMI_PHDR_END>
EFI_STATUS FileBrowserLaunchFileSystem(BOOLEAN bSelectFile, OUT EFI_HANDLE **outFsHandle,OUT CHAR16 **outFilePath, OUT UINT8 **outFileBuf,OUT UINTN *size )
{
    EFI_STATUS Status;
    UINTN Count = 0;
    UINT16 i = 0;
    EFI_HANDLE *gSmplFileSysHndlBuf = NULL;    
    UINT16 gSelIdx=0;

    EFI_DEVICE_PATH_PROTOCOL *Dp = NULL;

    POSTMENU_TEMPLATE *PossibleFileSystems = NULL;

    if(mPostMgr == NULL)
        return EFI_UNSUPPORTED;
    
    // To launch the files from the selected file system
    if(!size)
        return EFI_INVALID_PARAMETER;

    // Locate all the simple file system devices in the system
    Status = pBS->LocateHandleBuffer(ByProtocol, &gSimpleFileSystemGuid, NULL, &Count, &gSmplFileSysHndlBuf);
    if(!EFI_ERROR(Status))
    {
        // allocate space to display all the simple file system devices
        PossibleFileSystems = EfiLibAllocateCopyPool(sizeof(POSTMENU_TEMPLATE)*Count,PossibleFileSystems);
        if(PossibleFileSystems != NULL)
        {
            // clear the allocated space
            MemSet(PossibleFileSystems, sizeof(POSTMENU_TEMPLATE)*Count, 0);
            for(i = 0; i < Count; i++)
            {
                // get the device path for each handle with a simple file system
                Status = pBS->HandleProtocol(gSmplFileSysHndlBuf[i], &gEfiDevicePathProtocolGuid, &Dp);
                if(!EFI_ERROR(Status))
                {
                    CHAR16 *Name;
                    CHAR8  *Name8; 
                    // Get the name of the driver installed on the handle
                    // GetControllerName(gHandleBuffer[i],&Name);

                    Name8 = NULL;
                    Status  = DevicePathToStr(Dp, &Name8 );
                    Name = StrDup8to16(Name8);

                    // Add the name to the Hii Database
                    ///PossibleFileSystems[i].ItemToken = AddStringToHii(Name);
                    PossibleFileSystems[i].ItemToken = HiiAddString(gHiiHandle, Name ); 

                    PossibleFileSystems[i].Attribute = AMI_POSTMENU_ATTRIB_FOCUS;
                    pBS->FreePool(Name);
                    pBS->FreePool(Name8);
                }
                else
                {
                    PossibleFileSystems[i].ItemToken = 0;
                    PossibleFileSystems[i].Attribute = AMI_POSTMENU_ATTRIB_HIDDEN;
                }
            }
            // Reset the item selected to be the first item
            gSelIdx = 0;

            // Display the post menu and wait for user input
            Status = mPostMgr->DisplayPostMenu(gHiiHandle,
                                                STRING_TOKEN(STR_FILE_SYSTEM),
                                                0,
                                                PossibleFileSystems,
                                                (UINT16)Count,
                                                &gSelIdx);


            // A valid item was selected by the user
            if(!EFI_ERROR(Status))
            {
                    gValidOption = TRUE;
            }
        }
    }
    
    else {
        GetHiiString(gHiiHandle, STRING_TOKEN(STR_NO_VALID_FS_TITLE),  sizeof(StrTitle) ,StrTitle);
        GetHiiString(gHiiHandle, STRING_TOKEN(STR_NO_VALID_FS), sizeof(StrMessage),StrMessage);
        mPostMgr->DisplayMsgBox( StrTitle, StrMessage, MSGBOX_TYPE_OK, NULL );//EIP:41615  To display Warning message when there is no file system connected.
    }
    
    // Free the allocated menu list space
    if(PossibleFileSystems != NULL) 
        pBS->FreePool(PossibleFileSystems);

     *outFsHandle = gSmplFileSysHndlBuf[gSelIdx];

     *size = 0; 
     if(bSelectFile)
         Status = FileBrowserLaunchFilePath(*outFsHandle,outFilePath, outFileBuf,size );//EIP:41615 Returning the status of Filebrowselaunchfilepath

     if(gSmplFileSysHndlBuf != NULL) 
        pBS->FreePool(gSmplFileSysHndlBuf);

    return Status;
}

//<AMI_PHDR_START>
//----------------------------------------------------------------------
// Procedure:   FileBrowserLaunchFilePath
//
// Description: To select the Boot file for the new boot option with the help of file browser.
//
// Input:   VOID
//
// Output:  File Path string
//
// Returns: EFI_STATUS
//
//----------------------------------------------------------------------
//<AMI_PHDR_END>
EFI_STATUS FileBrowserLaunchFilePath(IN EFI_HANDLE *FileHandle,OUT CHAR16 **outFilePath, OUT UINT8 **outFileBuf,OUT UINTN *size )
{
    EFI_STATUS Status;

    EFI_SIMPLE_FILE_SYSTEM_PROTOCOL *SimpleFs = NULL;
    EFI_FILE_PROTOCOL *NewFs = NULL;
    FILE_TYPE *FileList = NULL;
    UINTN FileCount = 0;
    UINT16 i = 0;
    CHAR16 FilePath[120];
    EFI_FILE_PROTOCOL *gFs = NULL;

    // Attempt to locate the post manager protocol
    if(mPostMgr == NULL)
        return EFI_UNSUPPORTED;

    if( gValidOption == TRUE ) 
    {
        gValidOption = FALSE;

        // Get the simple file system protocol 
        Status = pBS->HandleProtocol(FileHandle, &gSimpleFileSystemGuid, &SimpleFs);
        if(!EFI_ERROR(Status))
        {
            // And open it and return the efi file protocol
            Status = SimpleFs->OpenVolume(SimpleFs, &gFs);
        }
    }
    else {
            return EFI_UNSUPPORTED;
    }

    // clean up the file list and strings used in getting the file system
    CleanFileTypes(&FileList, &FileCount);

    while(!EFI_ERROR(Status) && gFs != NULL)
    {
        i = 0;
        MemSet(FilePath, sizeof(FilePath), 0);

        // Create a list of the files in the current directory
        Status = CreateFileList(gFs, &FileList, &FileCount);
        if(!EFI_ERROR(Status))
        {
            // Display the list in a menu and allow the user to select
            Status = DisplayFileListMenu(FileList, FileCount, &i);
            if(!EFI_ERROR(Status))
            {
                // The user selected something, attempt to open it
                Status = gFs->Open(  gFs,
                                    &NewFs,
                                    FileList[i].Name,
                                    EFI_FILE_MODE_READ,
                                    0);

                // close the old file system protocol and set it to null
                gFs->Close(gFs);
                gFs = NULL;

                // Create the File Path based on the file selected
                UpdateFilePathString(FilePath, FileList[i].Name, i);

                // the newly selected item was opened correctly
                if(!EFI_ERROR(Status))
                {
                    // check what type was opened
                    if(FileList[i].Type != EFI_FILE_DIRECTORY)
                    {

                        
                        Status = pBS->AllocatePool(EfiBootServicesData,FileList[i].Size, (VOID**)outFileBuf);
                        if(!EFI_ERROR(Status))
                        {
                            *size = FileList[i].Size;
                            // The user selected something, attempt to open it
                            Status = NewFs->Read( NewFs, size, *outFileBuf); }

                        // the file was read, close the file system protocol and set it to null
                        NewFs->Close(NewFs);
                        NewFs = NULL;
                        //Swprintf_s (FileName, 50, L"%s", FileList[i].Name);
                        //ShowPostMsgBox( L"Selected Boot File Name", FileName, MSGBOX_TYPE_OK, &SelOpt );
                    }
                    gFs = NewFs;
                }
            }
        }

        if(FileCount <= 0) {
            GetHiiString(gHiiHandle, STRING_TOKEN(STR_NO_VALID_FILE_TITLE),sizeof(StrTitle), StrTitle);
            GetHiiString(gHiiHandle, STRING_TOKEN(STR_NO_VALID_FILE),sizeof(StrMessage),StrMessage);
            mPostMgr->DisplayMsgBox( StrTitle, StrMessage, MSGBOX_TYPE_OK, NULL );//EIP:41615 Warning message to show unavailability of the selected file
        }

        // clean the strings that were used and free allocated space
        CleanFileTypes(&FileList, &FileCount);

        if(Status == EFI_ABORTED) {
            return Status;//EIP:41615 Returning the status if its aborted.
        }
    }
    // Set the File path for the new boot option added.
    Status = pBS->AllocatePool(EfiBootServicesData, ((Wcslen(FilePath)+1)*sizeof(CHAR16)), outFilePath);
    Wcscpy (*outFilePath, FilePath);

    return Status;
}
//#endif //#if defined(CORE_COMBINED_VERSION) && CORE_COMBINED_VERSION >=0x4028a (4.6.5.0)
#endif // #ifdef SETUP_COMPILE

//<AMI_PHDR_START>
//----------------------------------------------------------------------------
// Procedure:   SecureMod_Init
//
// Description: Entry point of Secure Module DXE driver
//
// Input:       EFI_HANDLE           ImageHandle,
//              EFI_SYSTEM_TABLE     *SystemTable
//
// Output:      EFI_STATUS
//
// Modified:
//
// Referrals:
//
// Notes:
//----------------------------------------------------------------------------
//<AMI_PHDR_END>
EFI_STATUS
SecureBootMod_Init (
    IN EFI_HANDLE         ImageHandle,
    IN EFI_SYSTEM_TABLE   *SystemTable
)
{
    EFI_STATUS Status;
    UINTN      DataSize;
    UINT8      Byte;
    UINT32     Attributes;
    VOID      *pHobList;
    static EFI_GUID gHobListGuid  = HOB_LIST_GUID;

    InitAmiLib(ImageHandle, SystemTable);

    Byte        = 0;
    Attributes  = EFI_VARIABLE_BOOTSERVICE_ACCESS | EFI_VARIABLE_NON_VOLATILE;
    //
    // Look up for Secure Boot policy in "SecureBootSetup" variable. If not defined - create one with SDL defaults
    //
    DataSize = sizeof(SECURE_BOOT_SETUP_VAR);
    Status = pRS->GetVariable (AMI_SECURE_BOOT_SETUP_VAR, &guidSecurity,&Attributes,&DataSize,&SecureBootSetup);
//TRACE((TRACE_ALWAYS,"SecureBootSetup (%r) Attrib=%x, SecBoot-%d, SecMode-%d,DefaultProvision-%d\n", Status, Attributes, SecureBootSetup.SecureBootSupport, SecureBootSetup.SecureBootMode,SecureBootSetup.DefaultKeyProvision));    
    // Default variable is created with RT attribute which violates 
    // Intel's Secure Boot technical advisory #527669 and MS Windows Secure Boot requirements
    if((!EFI_ERROR(Status) && 
        (Attributes & EFI_VARIABLE_RUNTIME_ACCESS)==EFI_VARIABLE_RUNTIME_ACCESS)
        || Status == EFI_NOT_FOUND) // Var is not yet initialized
    {
        // Clear RT attributes if set for "SecureBootSetup" 
        pRS->SetVariable (AMI_SECURE_BOOT_SETUP_VAR, &guidSecurity, 0, 0, NULL);
        pRS->SetVariable (AMI_SECURE_BOOT_SETUP_VAR, &guidSecurity,(Attributes & ~EFI_VARIABLE_RUNTIME_ACCESS), DataSize, &SecureBootSetup);
    }

    DataSize = 1;
    Byte = USER_MODE;
    // Provision of defaults only if in Setup mode
    Status = pRS->GetVariable(EFI_SETUP_MODE_NAME, &gEfiGlobalVariableGuid, NULL, &DataSize, &Byte);
    if(SecureBootSetup.DefaultKeyProvision == 1 && 
        !EFI_ERROR(Status) && Byte == SETUP_MODE)
    {
        Status = InstallSecureVariables(SET_NV_DEFAULT_KEYS);
        // Status of last key to be installed - PK
        TRACE((TRACE_ALWAYS,"Provision Sec Vars(%r)\n", Status));
        // Issue reset after key provision only during normal boot with system is in User Mode and SecureBootSupport flag is enabled
        if(!EFI_ERROR(Status) && SecureBootSetup.SecureBootSupport)
        {
            Status = pRS->GetVariable(EFI_SETUP_MODE_NAME, &gEfiGlobalVariableGuid, NULL, &DataSize, &Byte);
            if(!EFI_ERROR(Status) && Byte == USER_MODE) 
            //Get Boot Mode
            pHobList = GetEfiConfigurationTable(SystemTable, &gHobListGuid);
            if (pHobList)
            {
                if (((EFI_HOB_HANDOFF_INFO_TABLE*)pHobList)->BootMode!=BOOT_IN_RECOVERY_MODE && 
                    ((EFI_HOB_HANDOFF_INFO_TABLE*)pHobList)->BootMode!=BOOT_ON_FLASH_UPDATE
                ) 
                    pRS->ResetSystem(EfiResetCold, Status, 0, NULL);
            }
        }
    }
#if ALWAYS_INSTALL_DEFAULT_RT_KEYS == 0
    if(Byte == SETUP_MODE)
#endif
        InstallSecureVariables(SET_RT_DEFAULT_KEYS);

    return EFI_SUCCESS;
}

//**********************************************************************
//**********************************************************************
//**                                                                  **
//**        (C)Copyright 1985-2015, American Megatrends, Inc.         **
//**                                                                  **
//**                       All Rights Reserved.                       **
//**                                                                  **
//**        5555 Oakbrook Pkwy, Suite 200, Norcross, GA 30093         **
//**                                                                  **
//**                       Phone: (770)-246-8600                      **
//**                                                                  **
//**********************************************************************
//**********************************************************************
