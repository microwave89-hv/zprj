//**********************************************************************
//**********************************************************************
//**                                                                  **
//**        (C)Copyright 1985-2010, American Megatrends, Inc.         **
//**                                                                  **
//**                       All Rights Reserved.                       **
//**                                                                  **
//**      5555 Oakbrook Parkway, Suite 200, Norcross, GA 30093        **
//**                                                                  **
//**                       Phone: (770)-246-8600                      **
//**                                                                  **
//**********************************************************************
//**********************************************************************

//**********************************************************************
// $Header: /Alaska/BIN/Board/Setup/Setup.c 67    10/04/12 4:50p Artems $
//
// $Revision: 67 $
//
// $Date: 10/04/12 4:50p $
//**********************************************************************
// Revision History
// ----------------
// $Log: /Alaska/BIN/Board/Setup/Setup.c $
// 
// 67    10/04/12 4:50p Artems
// [TAG]  		EIP N/A
// [Category]  	Spec Update
// [Severity]  	Minor
// [Description]  	Added missing function headers for CHM builder
// [Files]  		Setup.c
// 
// 66    8/29/12 2:42p Artems
// [TAG]  		EIP N/A
// [Category]  	Bug Fix
// [Severity]  	Normal
// [Symptom]  	setup control interactive callback doesn't work
// [RootCause]  	When there are no runtime-registered callbacks,
// build-time callbacks don't present in callback list
// [Solution]  	Fixed code logic to handle situation with no runtime
// callbacks
// [Files]  		AmiSetupProtocol.c Setup.c
// 
// 65    8/28/12 4:10p Artems
// [TAG]  		EIP N/A
// [Category]  	New Feature
// [Description]  	Add infrastructure to support runtime registration of
// setup controls callbacks
// [Files]  		Setup.c Setup.h Setup.cif AmiSetupProtocol.c
// AmiSetupProtocol.h
// 
// 64    4/12/12 4:41p Artems
// [TAG]  		EIP81090
// [Category]  	Improvement
// [Description]  	Show specification version in 2 or 3 digits format
// depending on value (i.e. 2.1 or 2.3.1)
// [Files]  		Setup.c
// 
// 63    7/01/11 3:15p Artems
// Added project build number to project version string
// 
// 62    6/21/11 9:24a Felixp
// EIP58960: Callback function is updateed to return status of the eLink
// based callback routine back to the browser.
// 
// 61    3/21/11 4:15p Felixp
// Enhancement: Callback function is updated to set ActionRequest to NONE.
// 
// 60    3/08/11 12:09p Felixp
// Bug fix (EIP 55443):  Password length restriction message is updated 
// to work properly during language switch.
// 
// 59    2/08/11 3:32p Artems
// Reduced function header comment line to fit CHM file
// 
// 58    2/07/11 5:25p Artems
// EIP 53374: Replaced tabs with spaces
// 
// 57    2/04/11 7:59p Artems
// Added PI 1.1 support
// 
// 1     2/02/11 5:16p Artems
// 
// 56    9/07/10 11:05p Felixp
// Minor fix: Spelling error (EIP 39919)
// 
// 55    2/24/10 11:50a Felixp
// Use CORE_COMBINED_VERSION token.
// Initialize UEFI Specification compliancy string
// Initialize min/max password length string
// 
// 54    2/05/10 2:11p Felixp
// 
// 53    2/05/10 2:10p Felixp
// Improvements in the Setup Callback Mechanism.
//    - The definition of the type of the Setup Callback Handling
// function, 
//       registered using ITEM_CALLBACK eLink, is moved from Setup.c to
// Setup.h(Core file). 
//       The type is renamed from  UPDATE_ITEM to
// SETUP_ITEM_CALLBACK_HANDLER. 
//    - The return type of the Setup Callback Handling function is changed
// from VOID to EFI_STATUS. 
//       The status only matters for UEFI 2.1 Configurations. If UEFI 2.1
// callback handler returns 
//        any status other   than EFI_UNSUPPORTED, processing of the
// callback handler list, 
//        defined by the SetupItemCallbacks eLink, is terminated and
// control is returned back to the HII browser.
//    - New GetCallbackParameters function is added. The function provides
// access to all callback 
//      parameters received from the HII browser.
// 
// 52    11/25/09 11:40a Felixp
// 
// 51    11/25/09 11:36a Felixp
// Action parameter of the Callback function is updated  based on UEFI
// errata
// 
// 50    11/23/09 5:03p Felixp
// SetupCallBack structure is updated to use formset GUID from Setup.h.
// DEFAULT_LANGUAGE is replaced with DEFAULT_LANGUAGE_CODE, which is
// passed from make file using /D
// 
// 49    10/21/09 3:21p Felixp
// LastLang/LastLangCodes - use different variable for UEFI 2.0 and UEFI
// 2.1 modes
// 
// 48    10/21/09 3:15p Felixp
// 
// 46    10/09/09 6:43p Felixp
// UEFI 2.1 Support (the component is updated to support Framework and
// UEFI 2.1 HII).
// 
// 45    7/01/09 2:34p Felixp
// SetupEntry updated to use absence of LastLangCodes variable (instead of
// Lang or Setup) as an indication of the first boot.
// 
// 44    6/30/09 2:33p Robert
// comment corrections
// 
// 43    6/30/09 2:28p Robert
// Comment updates
// 
// 42    6/30/09 11:42a Robert
// Added Comment and updated parts for coding standards
//
// 41    5/22/09 6:46p Felixp
// Minor bug fix in InitStrings function
//
// 40    2/23/09 10:18a Oleksiyy
// Bug fix (EIP 18214) Build process failed if too many SetupItemCallbacks
// in one command line. Solution is to
// forward SETUP_ITEM_CALLBACK_LIST definition into SetupCallbackList.h
// file, generated during the build process (in Setup.mak), and include it
// into Setup.c.
//
// 39    10/10/08 4:44p Felixp
// UEFI2.0 Language Variable added and code to sync up values of the new
// and old language varaibles.
//
// 38    4/18/08 6:32p Felixp
// Undo previous status code reporting changed.
// They are not needed because the same status codes are reported by the
// TSE included with Core 4.6.3.2
//
// 36    2/21/08 5:19p Felixp
// 1. CMOS handling code removed because it's platform specific and does
// not belong in generic Setup module.
// 2. Core version string updated to use CORE_BUILD_NUMBER
//
// 33    1/24/08 1:21p Felixp
// ALWAYS_PUBLISH_HII_RESOURCES SDL token added
//
// 32    10/30/07 11:24a Felixp
// SDL tokens to hide advanced, chipset, and security formsets added
//
// 31    9/05/07 8:31p Felixp
// Bug fix in Lang variable initialization.
//
// 28    8/31/07 12:43a Felixp
// SetupEntry updated to support defaults generated during build process.
//
// 27    3/19/07 8:50a Felixp
// Bug fix in SetupEntry
//
// 26    3/18/07 12:42p Felixp
// 1. Code clean up
// 2. Initialization of LangCodes variable when SetupCallback is not
// invoked
//
// 25    3/06/07 3:12p Vyacheslava
// Support for initialization of the Lang and LangCodes variables based on
// available languages in HII.
//
// 22    12/05/06 12:25p Felixp
// Use date/time stamps from TimeStamp.h instead of C __DATE__ macro
//
// 20    10/30/06 7:16p Felixp
// Bug fix in Setup variable initialization (HII 0.92 related changes)
//
// 19    10/30/06 5:45p Felixp
// Updated to be complient with HII Spec. 0.92 (used to be 0.91)
//
// 18    10/07/06 11:13a Felixp
// Add "x64" to the BIOS version in x64 mode
//
// 17    5/23/06 4:20a Felixp
// FW Verion extraction logic changed
//
// 12    2/06/06 6:30p Felixp
// Support for Callbacks added
//
// 11    11/08/05 5:13a Felixp
// 1. Now resources are only loaded if Setup is about to be launched
// 2. Support for unconditional (w/o user intervention) launch of Setup
// when NVRAM is blank
//
// 8     7/19/05 10:09p Felixp
// 1. InitString modified to update string for all languages
// 2. Memory information removed (moved to NB)
//
// 6     7/14/05 7:06p Felixp
// Setup variable initialization with default values added
//
// 2     5/31/05 11:21a Felixp
// CPU frequency display disabled
//
// 10    5/24/05 3:07p Felixp
// Modular setup framework implemented
//
// 7     3/25/05 7:12p Felixp
// SetupInit Protocol installed
//
// 5     3/17/05 7:50p Felixp
// form callback support added
//
// 4     3/17/05 2:00p Felixp
// 1. LoadResources updated to support multiple form sets
// 2. Setup variable created
//
// 2     3/07/05 7:06p Felixp
// support for embedded resources added
//
//**********************************************************************
//<AMI_FHDR_START>
//
// Name:    Setup.c
//
// Description: 
//  This file contains supporting functions, data types and data that
//  correspond to the Setup driver.
//
//<AMI_FHDR_END>
//**********************************************************************

//=======================================================================
//  Includes
#include <DXE.h>
#include <AmiDxeLib.h>
#include <Protocol/LoadedImage.h>
#include <Protocol/DevicePath.h>
#include <Protocol/Cpu.h>
#include <Protocol/SimpleTextOut.h >
#include <Protocol/AmiSetupProtocol.h >
#include <AmiHobs.h>
#include <TimeStamp.h>
#if EFI_SPECIFICATION_VERSION>0x20000
#include <Protocol/HiiString.h>
#include <Protocol/HiiDatabase.h>
#else
#include <Protocol/Hii.h>
#endif
#include "SetupPrivate.h"
#include <SetupCallbackList.h>
#include <LangList.h>

//=======================================================================
// MACROs
#define STR CONVERT_TO_WSTRING

#if EFI_SPECIFICATION_VERSION>0x20000
#define LastLangCodes L"PlatformLastLangCodes"
#define LastLang L"PlatformLastLang"
#define NativeLangCodes L"PlatformLangCodes"
#define CompatLangCodes L"LangCodes"
#define NativeLang L"PlatformLang"
#define CompatLang L"Lang"
#define LangNativeListToCompatList RfcListToIsoList
#define LangToCompat RfcToIso
#define LangToNative IsoToRfc
#define GetFirstLang GetFirstRfcLang
#else
#define LastLangCodes L"LastLangCodes"
#define LastLang L"LastLang"
#define NativeLangCodes L"LangCodes"
#define CompatLangCodes L"PlatformLangCodes"
#define NativeLang L"Lang"
#define CompatLang L"PlatformLang"
#define LangNativeListToCompatList IsoListToRfcList
#define LangToCompat IsoToRfc
#define LangToNative RfcToIso
#define GetFirstLang GetFirstIsoLang
#endif

//=======================================================================
// GUIDs
static EFI_GUID guidSetup = SETUP_GUID;
static EFI_GUID guidEfiVar = EFI_GLOBAL_VARIABLE;

//=======================================================================
// Module specific global variables
EFI_HANDLE ThisImageHandle = NULL;
#if EFI_SPECIFICATION_VERSION>0x20000
static EFI_HII_STRING_PROTOCOL *HiiString=NULL;
static EFI_HII_DATABASE_PROTOCOL *HiiDatabase=NULL;
#else
EFI_HII_PROTOCOL *pHii = NULL;
#endif
UINT8 Setup[sizeof(SETUP_DATA)];

//<AMI_THDR_START>
//----------------------------------------------------------------------------
// Name:    SETUP_CALLBACK
//
// Fields: Type Name Description
//  EFI_FORM_CALLBACK_PROTOCOL Callback - Callback Protocol Instance for the 
//                                        Class and SubClass defined below
//  UINT16 Class - Value defined to identify a particular Hii form 
//  UINT16 SubClass - Secondary value used to uniquely define the an Hii form 
//
// Description:
//  These Data Structure define a structure used to match a specific 
//  Callback Protocol to an HII Form through the use of Class and SubClass 
//  values
//
// Notes:
//----------------------------------------------------------------------------
//<AMI_THDR_END>
typedef struct {
#if EFI_SPECIFICATION_VERSION>0x20000
    EFI_HII_CONFIG_ACCESS_PROTOCOL Callback;
#else
    EFI_FORM_CALLBACK_PROTOCOL Callback;
#endif
    UINT16 Class, SubClass;
} SETUP_CALLBACK;

#if EFI_SPECIFICATION_VERSION>0x20000
EFI_STATUS Callback(
    IN CONST EFI_HII_CONFIG_ACCESS_PROTOCOL *This,
    IN EFI_BROWSER_ACTION Action,
    IN EFI_QUESTION_ID KeyValue,
    IN UINT8 Type,
    IN EFI_IFR_TYPE_VALUE *Value,
    OUT EFI_BROWSER_ACTION_REQUEST *ActionRequest
);
#else
EFI_STATUS Callback(
    IN EFI_FORM_CALLBACK_PROTOCOL *This,
    IN UINT16 KeyValue,
    IN EFI_IFR_DATA_ARRAY *Data,
    OUT EFI_HII_CALLBACK_PACKET **Packet
);
#endif

EFI_STATUS InitAmiSetupProtocol(VOID);

//<AMI_GHDR_START>
//----------------------------------------------------------------------------
// Name:    Callback_Protocols
//
// Description:
//  These Variable definitions define the different formsets and what Callback 
//  protocol should be used for each one
//
//----------------------------------------------------------------------------
//<AMI_GHDR_END>
SETUP_CALLBACK MainCallbackProtocol = {{NULL,NULL,Callback},MAIN_FORM_SET_CLASS,0};
SETUP_CALLBACK AdvancedCallbackProtocol = {{NULL,NULL,Callback},ADVANCED_FORM_SET_CLASS,0};
SETUP_CALLBACK ChipsetCallbackProtocol = {{NULL,NULL,Callback},CHIPSET_FORM_SET_CLASS,0};
SETUP_CALLBACK BootCallbackProtocol = {{NULL,NULL,Callback},BOOT_FORM_SET_CLASS,0};
SETUP_CALLBACK SecurityCallbackProtocol = {{NULL,NULL,Callback},SECURITY_FORM_SET_CLASS,0};
SETUP_CALLBACK ExitCallbackProtocol = {{NULL,NULL,Callback},EXIT_FORM_SET_CLASS,0};

EFI_GUID MainFormSetGuid = MAIN_FORM_SET_GUID;
EFI_GUID AdvancedFormSetGuid = ADVANCED_FORM_SET_GUID;
EFI_GUID ChipsetFormSetGuid = CHIPSET_FORM_SET_GUID;
EFI_GUID BootFormSetGuid = BOOT_FORM_SET_GUID;
EFI_GUID SecurityFormSetGuid = SECURITY_FORM_SET_GUID;
EFI_GUID ExitFormSetGuid = EXIT_FORM_SET_GUID;


//<AMI_THDR_START>
//----------------------------------------------------------------------------
// Name:    SetupCallBack
//
// Fields: Type Name Description
//  EFI_GUID* pGuid - GUID used for future references
//  EFI_FORM_CALLBACK_PROTOCOL* pFormCallback - Structure that defines the Callback 
//                                              that occurs for this package
//  UINT16 Class - Formset Class of the Form Callback Protocol passed in
//  UINT16 SubClass - Formset Sub Class of the Form Callback Protocol passed in
//  EFI_HII_HANDLE HiiHandle - handle that identifies used Hii Package
//
// Description:
//  This array contains the different Hii packages that are used in the system
//
// Notes:
//  The HiiHandle is updated in the LoadResources function when the Hii Packages 
//  are loaded
//----------------------------------------------------------------------------
//<AMI_THDR_END>
CALLBACK_INFO SetupCallBack[] = {
    // Last field in every structure will be filled by the Setup
    { &MainFormSetGuid, &MainCallbackProtocol.Callback, MAIN_FORM_SET_CLASS, 0, 0},
    { &AdvancedFormSetGuid, &AdvancedCallbackProtocol.Callback, ADVANCED_FORM_SET_CLASS, 0, 0},
    { &ChipsetFormSetGuid, &ChipsetCallbackProtocol.Callback, CHIPSET_FORM_SET_CLASS, 0, 0},
    { &BootFormSetGuid, &BootCallbackProtocol.Callback, BOOT_FORM_SET_CLASS, 0, 0},
    { &SecurityFormSetGuid, &SecurityCallbackProtocol.Callback, SECURITY_FORM_SET_CLASS, 0, 0},
    { &ExitFormSetGuid, &ExitCallbackProtocol.Callback, EXIT_FORM_SET_CLASS, 0, 0}
};

//<AMI_GHDR_START>
//----------------------------------------------------------------------------
// Name:    FormsetVisible
//
// Description:
//  This array contains information that indicates to the system whether or not 
//  a formset is visible when Setup is loaded.
//
// Reference: 
//  SetupCallBack
//
// Notes:
//  Formset index in this array should match with the formset index in the 
//  SetupCallBack array
//
//----------------------------------------------------------------------------
//<AMI_GHDR_END>
BOOLEAN FormsetVisible[] = {
    TRUE, //Main formset is always displayed
    SHOW_ADVANCED_FORMSET, //Advanced formset
    SHOW_CHIPSET_FORMSET, //Chipset formset
    TRUE, //Boot formset is always displayed
    SHOW_SECURITY_FORMSET, //Security formset
    TRUE //Exit formset is always displayed
};

#define NUMBER_OF_FORMSETS (sizeof(SetupCallBack)/sizeof(CALLBACK_INFO))

//<AMI_THDR_START>
//----------------------------------------------------------------------------
// Name:    InitString
//
// Description:
//  This function updates a string defined by the StrRef Parameter in the HII 
//  database with the string and data passed in.
//
// Input:
//  EFI_HII_HANDLE HiiHandle - handle that identifies used Hii Package
//  STRING_REF StrRef - String Token defining string in the database to update
//  CHAR16 *sFormat - string with format descriptors in it
//  ... - extra paramaters that define data that correlate to the format 
//        descriptors in the String
//
// Output:
//  None
//
// Notes:
//----------------------------------------------------------------------------
//<AMI_THDR_END>
VOID InitString(EFI_HII_HANDLE HiiHandle, STRING_REF StrRef, CHAR16 *sFormat, ...)
{
    CHAR16 s[1024];
    va_list ArgList = va_start(ArgList,sFormat);
    Swprintf_s_va_list(s,sizeof(s),sFormat,ArgList);
    va_end(ArgList);
    HiiLibSetString(HiiHandle, StrRef, s);
}

//<AMI_THDR_START>
//----------------------------------------------------------------------------
// Name:    RevisionToString
//
// Description:
//  This function converts spec revision number to string
//
// Input:
//  OUT CHAR16 *String - pointer to string to store output
//  IN UINT32 Revision - spec revision number
//
// Output:
//  None
//
//----------------------------------------------------------------------------
//<AMI_THDR_END>
VOID RevisionToString(
    OUT CHAR16 *String,
    IN UINT32 Revision
)
{
    UINT16 Major;
    UINT16 MinorH;
    UINT16 MinorL;
    UINT16 *Walker;

    Walker = (UINT16 *)&Revision;
    Major = *(Walker + 1);
    MinorH = *Walker / 10;
    MinorL = *Walker % 10;

    if(MinorL != 0)
        Swprintf(String, L"%d.%d.%d", Major, MinorH, MinorL);
    else
        Swprintf(String, L"%d.%d", Major, MinorH);
}


//<AMI_THDR_START>
//----------------------------------------------------------------------------
// Name:    InitMain
//
// Description:
//  This function updates a few generic BIOS strings that are used on the 
//  setup pages.
//
// Input:
//  EFI_HII_HANDLE HiiHandle - handle that identifies used Hii Package
//
// Output:
//  None
//
// Notes:
//----------------------------------------------------------------------------
//<AMI_THDR_END>
VOID InitMain(EFI_HII_HANDLE HiiHandle)
{
    DXE_SERVICES *DxeTable;
    CHAR16 efi[10];
    CHAR16 pi[10];

    ///////////////// BIOS /////////////////////////////////////
    CHAR16 *FirmwareVendor  =   (pST->FirmwareVendor) 
                              ? pST->FirmwareVendor 
                              : CONVERT_TO_WSTRING(CORE_VENDOR);
    UINT32 FirmwareRevision =  (pST->FirmwareRevision) 
                              ? pST->FirmwareRevision 
                              : CORE_COMBINED_VERSION;

    InitString(
        HiiHandle,STRING_TOKEN(STR_BIOS_VENDOR_VALUE),
        L"%s", FirmwareVendor
    );
    InitString(
        HiiHandle,STRING_TOKEN(STR_BIOS_CORE_VERSION_VALUE),
        L"%d.%d.%d.%d",
        ((UINT16*)&pST->FirmwareRevision)[1],
        *(UINT16*)&pST->FirmwareRevision / 100,
        *(UINT16*)&pST->FirmwareRevision % 100 / 10,
        *(UINT16*)&pST->FirmwareRevision % 10
    );
    InitString(
        HiiHandle,STRING_TOKEN(STR_BIOS_VERSION_VALUE),
#if PROJECT_BUILD_NUMBER_IN_TITLE_SUPPORTED && defined (PROJECT_BUILD)
#ifdef EFIx64
        L"%s %d.%02d.%03d x64",
#else
        L"%s %d.%02d.%03d",
#endif
        STR(PROJECT_TAG), PROJECT_MAJOR_VERSION, PROJECT_MINOR_VERSION, PROJECT_BUILD
#else //#if PROJECT_BUILD_NUMBER_IN_TITLE_SUPPORTED && defined (PROJECT_BUILD)
#ifdef EFIx64
        L"%s %d.%02d x64",
#else
        L"%s %d.%02d",
#endif
        STR(PROJECT_TAG), PROJECT_MAJOR_VERSION, PROJECT_MINOR_VERSION
#endif//#if PROJECT_BUILD_NUMBER_IN_TITLE_SUPPORTED && defined (PROJECT_BUILD)
    );
    InitString(
        HiiHandle,STRING_TOKEN(STR_BIOS_DATE_VALUE),
        L"%s %s", L_TODAY, L_NOW
    );
    VERIFY_EFI_ERROR(LibGetDxeSvcTbl(&DxeTable));

    RevisionToString(efi, pST->Hdr.Revision);
    RevisionToString(pi, DxeTable->Hdr.Revision);

    InitString(
        HiiHandle,STRING_TOKEN(STR_BIOS_COMPLIANCY_VALUE),
        L"UEFI %s; PI %s", efi, pi
    );
}

VOID InitParts(EFI_HII_HANDLE HiiHandle, UINT16 Class);

//<AMI_THDR_START>
//----------------------------------------------------------------------------
// Name:    InitStrings
//
// Description:
//  This function is called for each Formset and initializes strings based on 
//  the porting provided and then updates the HII database
//
// Input:
//  EFI_HII_HANDLE HiiHandle - handle that that identifies used Hii Package
//  CALLBACK_INFO *pCallBackFound - pointer to an instance of CALLBACK_INFO 
//                                  that works with HiiHandle
//
// Output:
//  None
//
// Notes:
//----------------------------------------------------------------------------
//<AMI_THDR_END>
VOID InitStrings(
    EFI_HII_HANDLE HiiHandle,
    CALLBACK_INFO *pCallBackFound
)
{
    if (!pCallBackFound || !pCallBackFound->HiiHandle) return;
 
    InitParts(HiiHandle, pCallBackFound->Class);
    switch(pCallBackFound->Class)
    {
        case MAIN_FORM_SET_CLASS: 
            InitMain(HiiHandle); 
            break;
        case SECURITY_FORM_SET_CLASS:
        {
            InitString(
                HiiHandle,STRING_TOKEN(STR_MIN_PASSWORD_LENGTH__VALUE),
                L"%d", PASSWORD_MIN_SIZE
            );
            InitString(
                HiiHandle,STRING_TOKEN(STR_MAX_PASSWORD_LENGTH__VALUE),
                L"%d", PASSWORD_MAX_SIZE
            );
            break;
        }
    }
#if EFI_SPECIFICATION_VERSION>0x20000
// TODO: Defaults initialization
#else
{
    EFI_HII_VARIABLE_PACK_LIST *pVarPackList, *pVarPack;

    // Get default values from IFR initialized with default values
    if (EFI_ERROR(pHii->GetDefaultImage(
            pHii, HiiHandle, EFI_IFR_FLAG_DEFAULT, &pVarPackList
    ))) return;

    // Find Setup variable(default varstore) in the returned variable list
    for(pVarPack = pVarPackList; pVarPack->NextVariablePack != NULL; pVarPack = pVarPack->NextVariablePack)
    {
        EFI_HII_VARIABLE_PACK *pVar = pVarPack->VariablePack;
        UINTN i;
        UINT8 *p, *q;
        //default varstore has id set to 0
        if (pVar->VariableId != 0) continue;
        //if size does not match, don't update the setup data
        if (pVar->Header.Length - sizeof(*pVar) - pVar->VariableNameLength != sizeof(Setup))
        {
            TRACE((
                TRACE_DXE_CORE,
                "ERROR: Setup data size mismatch:\n\t"
                "Setup variable size: %d\n\t"
                "Default varstore size: %d\n",
                sizeof(Setup),
                pVar->Header.Length - sizeof(*pVar) - pVar->VariableNameLength
            ));
            break;
        }
        p = (UINT8*)&Setup;
        q = (UINT8*)(pVar + 1) + pVar->VariableNameLength;
        for(i = 0; i < sizeof(Setup); i++) p[i] |= q[i];
        break;
    }
    pBS->FreePool(pVarPackList);
}
#endif
}

//<AMI_PHDR_START>
//----------------------------------------------------------------------------
//
// Procedure:    InitLanguages
//
// Description:
//  Determine the current language that will be used based on language
//  related EFI Variables.
//
// Input:
//  EFI_HII_HANDLE HiiHandle - handle that that identifies used Hii Package
//
// Output:
//  None
//
// Notes:
//----------------------------------------------------------------------------
//<AMI_PHDR_END>
VOID InitLanguages(EFI_HII_HANDLE HiiHandle)
{
    UINTN Size = 0;
#if EFI_SPECIFICATION_VERSION>0x20000
    EFI_STATUS Status;
    CHAR8* LangCodes = NULL;

    if (HiiString == NULL) {
        return;
    }

    Status = HiiString->GetLanguages(HiiString, HiiHandle, LangCodes, &Size);
    if (Status==EFI_BUFFER_TOO_SMALL){
        LangCodes = Malloc(Size);
        Status = HiiString->GetLanguages(HiiString, HiiHandle, LangCodes, &Size);
        if (EFI_ERROR(Status)) pBS->FreePool(LangCodes);
    }
    if (EFI_ERROR(Status)){
        Size = sizeof(CONVERT_TO_STRING(DEFAULT_LANGUAGE_CODE));
        LangCodes = Malloc(Size);
        pBS->CopyMem(
            LangCodes, CONVERT_TO_STRING(DEFAULT_LANGUAGE_CODE), Size
        );
    }
#else
    EFI_STATUS PrimaryStatus;
    EFI_STATUS SecondaryStatus;
    UINTN i;
    UINTN Index = 0;
    CHAR8* LangCodes = NULL;
    CHAR16* PrimaryLanguages = NULL;
    EFI_STRING SecondaryLanguages = NULL;

    if (pHii == NULL) {
        return;
    }

    // Get list of available languages
    PrimaryStatus =  pHii->GetPrimaryLanguages( pHii,
                                          HiiHandle,
                                          &PrimaryLanguages );

    SecondaryStatus = pHii->GetSecondaryLanguages( pHii,
                                           HiiHandle,
                                           PrimaryLanguages,
                                           &SecondaryLanguages );

    if ( !EFI_ERROR(PrimaryStatus) ) {
        Size = Wcslen(PrimaryLanguages);
    }

    if ( !EFI_ERROR(SecondaryStatus) ) {
        Size += Wcslen(SecondaryLanguages);
    }

    if ( Size == 0 ) {
        // Primary and Secondary languages are not available
        Size = 3;
        LangCodes = Malloc(Size);
        pBS->CopyMem(
            LangCodes, CONVERT_TO_STRING(DEFAULT_LANGUAGE_CODE), 
            Size
        );
    } else {
        LangCodes = MallocZ(Size);
        if ( !EFI_ERROR(PrimaryStatus) ) {
            // Convert PrimaryLanguages from Unicode to EFI defined ASCII LangCodes
            for (i = 0; PrimaryLanguages[i] != 0; i++) {
                LangCodes[Index++] = (CHAR8)PrimaryLanguages[i];
            }
            pBS->FreePool(PrimaryLanguages);
        }

        if ( !EFI_ERROR(SecondaryStatus) ) {
            // Convert SecondaryLanguages from Unicode to EFI defined ASCII LangCodes
            for (i = 0; SecondaryLanguages[i] != 0; i++) {
                LangCodes[Index++] = (CHAR8)SecondaryLanguages[i];
            }

            pBS->FreePool(SecondaryLanguages);
        }
    }
#endif
    //LangCodes is a volatile variable and needs to be initialized during every boot
    //However, this routine is not invoked during every boot,
    //It is always invoked during the first boot.
    //During subsequent boots it is only invoked when user is trying to enter Setup
    //In order to initialize LanCodes when this routine is not invoked, let's create
    //a non-volatile variable LastLangCodes with the copy of LanCodes.
    //This copy is used to initialize LanCodes when this routine is not invoked.
    //(This code is part of SynchornizeLanguageVariables routine)
    pRS->SetVariable( LastLangCodes,
                      &guidSetup,
                      EFI_VARIABLE_BOOTSERVICE_ACCESS | EFI_VARIABLE_NON_VOLATILE,
                      Size,
                      LangCodes );

    pBS->FreePool(LangCodes);
}

//<AMI_PHDR_START>
//----------------------------------------------------------------------------
//
// Procedure:    SetupCallback
//
// Description:
//  This function publishes all HII resources and initializes the HII databases
//  There is a token ALWAYS_PUBLISH_HII_RESOURCES that would call this function
//  on every boot not just when the user tries to enter Setup
//
// Input:
//  IN EFI_EVENT Event - Event that was triggered
//  IN VOID *Context - data pointer to context information
//
// Output:
//  None
//
// Notes:
//----------------------------------------------------------------------------
//<AMI_PHDR_END>
VOID SetupCallback(IN EFI_EVENT Event, IN VOID *Context)
{
    static BOOLEAN ResourcesLoaded = FALSE;
    UINT32 i;

#if EFI_SPECIFICATION_VERSION>0x20000
    if (   !HiiString 
        && EFI_ERROR(pBS->LocateProtocol(
                        &gEfiHiiStringProtocolGuid, NULL, &HiiString
           ))
    ) return ;
    if (   !HiiDatabase 
        && EFI_ERROR(pBS->LocateProtocol(
                        &gEfiHiiDatabaseProtocolGuid, NULL, &HiiDatabase
           ))
    ) return ;
#else
    if (!pHii && EFI_ERROR(pBS->LocateProtocol(&gEfiHiiProtocolGuid, NULL, &pHii))) return ;
#endif
    if (Event) pBS->CloseEvent(Event);
    if (ResourcesLoaded) return;
    ResourcesLoaded = TRUE;
    LoadResources(ThisImageHandle, NUMBER_OF_FORMSETS, SetupCallBack, InitStrings);
    //Get list of available languages and initialize Lang and LangCodes variables
    //All setup packages share the same string pack
    //that's why it is enough to only process single pack in the SetupCallBack array.
    InitLanguages(SetupCallBack[0].HiiHandle);
    //Hide (remove) formsets if necessary
    for(i = 0; i < NUMBER_OF_FORMSETS; i++){
        if (!FormsetVisible[i]) 
#if EFI_SPECIFICATION_VERSION>0x20000
            HiiDatabase->RemovePackageList(
                HiiDatabase, SetupCallBack[i].HiiHandle
            );
#else
            pHii->RemovePack(pHii, SetupCallBack[i].HiiHandle);
#endif
    }
}

//<AMI_PHDR_START>
//----------------------------------------------------------------------------
// Procedure:    IsoToRfc
//
// Description:
//  This function takes a language string based on the ISO standard and 
//  returns a string that represents the same language in the RFC standard
//
// Input:
//  IN CHAR8 *IsoLang - ASCII string that represents language in the ISO format
//
// Output:
//  CHAR8 * - String that represents RFC version of the ISO language code passed
//
// Notes:
//----------------------------------------------------------------------------
//<AMI_PHDR_END>
CHAR8* IsoToRfc(IN CHAR8 *IsoLang, OUT UINTN *RfcLangSize){
    UINTN i;
    if (IsoLang == NULL) return NULL;
    for(i = 0; Iso6392LanguageList[i] != NULL; i++){
        if (MemCmp(Iso6392LanguageList[i], IsoLang, 3) == 0){
            if (RfcLangSize!=NULL) 
                *RfcLangSize = Strlen(Rfc4646LanguageList[i])+1;
            return Rfc4646LanguageList[i];
        }
    }
    return NULL;
}

//<AMI_PHDR_START>
//----------------------------------------------------------------------------
// Procedure:    RfcToIso
//
// Description:
//  This function takes a language string based on the RFC standard and 
//  returns a string that represents the same language in the ISO standard
//
// Input:
//  IN CHAR8 *RfcLang - ASCII string that represents a language in RFC standard
//
// Output:
//  CHAR8 * - String that represents ISO version of the RFC language code passed
//
// Notes:
//----------------------------------------------------------------------------
//<AMI_PHDR_END>
CHAR8* RfcToIso(IN CHAR8 *RfcLang, OUT UINTN *IsoLangSize){
    UINTN i;
    if (RfcLang == NULL) return NULL;
    for(i = 0; Rfc4646LanguageList[i] != NULL; i++){
        if (Strcmp(Rfc4646LanguageList[i],RfcLang) == 0){
            if (IsoLangSize!=NULL) *IsoLangSize = 3;
            return Iso6392LanguageList[i];
        }
    }
    return NULL;
}

//<AMI_PHDR_START>
//----------------------------------------------------------------------------
// Procedure:    IsoListToRfcList
//
// Description:
//  This function coverts list of ISO language tags to a list of RFC language tags
//
// Input:
//  IN CHAR8 *IsoList - string that represents list of one or more ISO language strings
//  IN UINTN IsoListSize - number of ISO entries in the list
//  OUT UINTN *RfcListSize - pointer to store size of output buffer
//
// Output:
//  VOID * - String that represents the RFC version of the ISO language codes passed
//
// Notes:
//  ISO tags are 3 characters in size
//  RFC tags are 42(max) characters plus a ';' that ends each tag
//----------------------------------------------------------------------------
//<AMI_PHDR_END>
CHAR8* IsoListToRfcList(IN CHAR8 *IsoList, IN UINTN IsoListSize, OUT UINTN *RfcListSize){
    CHAR8 *IsoPtr;
    CHAR8 *RfcList;
    CHAR8 *RfcPtr;

    if (IsoList==NULL || *IsoList==0 || IsoListSize<3) return NULL;
    //IsoListSize/3 = number of languages in the list
    //RFC4646 defines max lang tag size of 42, plus ';'
    RfcList = Malloc(IsoListSize / 3 * (42 + 1));
    if (RfcList == NULL) return NULL;
    for(IsoPtr = IsoList, RfcPtr = RfcList;
        IsoPtr < IsoList + IsoListSize;
        IsoPtr += 3
    ){
        UINTN Length;
        CHAR8 *TmpPtr = IsoToRfc(IsoPtr, &Length);

        if (TmpPtr == NULL) continue;
        Length--; // string length  = string size - 1
        MemCpy(RfcPtr, TmpPtr, Length);
        RfcPtr += Length;
        *RfcPtr++ = ';';
    }
    if (RfcPtr == RfcList){
        pBS->FreePool(RfcList);
        if (RfcListSize) *RfcListSize=0;
        return NULL;
    }
    *(RfcPtr - 1) = 0;
    if (RfcListSize) *RfcListSize=RfcPtr-RfcList;
    return RfcList;
}

//<AMI_PHDR_START>
//----------------------------------------------------------------------------
// Procedure:    RfcListToIsoList
//
// Description:
//  This function coverts list of RFC language tags to a list of ISO language tags
//
// Input:
//  IN CHAR8 *RfcList - string that represents list of one or more RFC language strings
//  IN UINTN RfcListSize - number of RFC entries in the list
//  OUT UINTN *IsoListSize - pointer to store size of output buffer
//
// Output:
//  CHAR8 * - A string that corresponds to the ISO version of the RFC language codes
//            passed
//
// Notes:
//  ISO tags are 3 characters in size
//  RFC tags are 42(max) characters plus a ';' that ends each tag
//----------------------------------------------------------------------------
//<AMI_PHDR_END>
CHAR8* RfcListToIsoList(IN CHAR8 *RfcList, IN UINTN RfcListSize, OUT UINTN *IsoListSize){
    UINTN Size;
    CHAR8 *RfcPtr, *RfcEndPtr;
    CHAR8 *IsoPtr;
    CHAR8 *IsoList;

    if (RfcList==NULL || *RfcList==0) return NULL;
    //calculate number of languages in the RfcList
    for(Size=3, RfcPtr=RfcList; *RfcPtr!=0; RfcPtr++){
        if (*RfcPtr==';') Size+=3;
    }
    IsoList = Malloc(Size);
    IsoPtr = IsoList;
    RfcEndPtr = RfcList;
    while(RfcEndPtr < RfcList+RfcListSize){
        CHAR8 *IsoLang;
        CHAR8 OriginalChar;
        RfcPtr = RfcEndPtr;
        while(*RfcEndPtr!=';'&&*RfcEndPtr!=0) RfcEndPtr++;
        OriginalChar = *RfcEndPtr;
        *RfcEndPtr = 0;
        IsoLang=RfcToIso(RfcPtr,NULL);
        if (IsoLang!=NULL){
            MemCpy(IsoPtr, IsoLang, 3);
            IsoPtr += 3;
        }
        *RfcEndPtr = OriginalChar;
        RfcEndPtr++;
    }
    if (IsoPtr==IsoList){
        pBS->FreePool(IsoList);
        if (IsoListSize) *IsoListSize=0;
        return NULL;
    }
    if (IsoListSize) *IsoListSize=IsoPtr-IsoList;
    return IsoList;
}

//<AMI_PHDR_START>
//----------------------------------------------------------------------------
// Procedure:    GetFirstIsoLang
//
// Description:
//  This function returns first language from passed ISO list
//
// Input:
//  IN CHAR8 *IsoList - string that represents list of one or more ISO languages
//  OUT UINTN *LangSize - pointer to store size of output buffer
//
// Output:
//  CHAR8 * - A string that contains first language
//
//----------------------------------------------------------------------------
//<AMI_PHDR_END>
CHAR8* GetFirstIsoLang(CHAR8* IsoList, UINTN *LangSize){
    if (LangSize) *LangSize=3;
    return IsoList;
}

//<AMI_PHDR_START>
//----------------------------------------------------------------------------
// Procedure:    GetFirstRfcLang
//
// Description:
//  This function returns first language from passed RFC list
//
// Input:
//  IN CHAR8 *RfcList - string that represents list of one or more RFC languages
//  OUT UINTN *LangSize - pointer to store size of output buffer
//
// Output:
//  CHAR8 * - A string that contains first language
//
//----------------------------------------------------------------------------
//<AMI_PHDR_END>
CHAR8* GetFirstRfcLang(CHAR8* RfcList, UINTN *LangSize){
    CHAR8 *RfcPtr;

    for(RfcPtr=RfcList; *RfcPtr!=0 && *RfcPtr!=';'; RfcPtr++);
    *RfcPtr=0;
    if (LangSize) *LangSize=RfcPtr-RfcList+1;    
    return RfcList;
}

//<AMI_PHDR_START>
//----------------------------------------------------------------------------
// Procedure:    GetLangVariable
//
// Description:
//  This function returns language variable stored in NVRAM
//
// Input:
//  IN CHAR16 *VariableName - Human-readable name of language variable
//  EFI_GUID *VariableGuid - pointer to variable GUID
//  UINTN *VariableSize - pointer to store output buffer size
//
// Output:
//  CHAR8 * - A string that contains list of languages supported by platform
//
//----------------------------------------------------------------------------
//<AMI_PHDR_END>
CHAR8* GetLangVariable(
    CHAR16 *VariableName, EFI_GUID *VariableGuid, UINTN *VariableSize
){
    UINTN Size = 0;
    CHAR8 *Buffer = NULL;
    EFI_STATUS Status;

    Status = GetEfiVariable(VariableName, VariableGuid, NULL, &Size, &Buffer);
    if (EFI_ERROR(Status)) Buffer=NULL;
    else if (VariableSize!=NULL) *VariableSize=Size;
    return Buffer;
}

//<AMI_PHDR_START>
//----------------------------------------------------------------------------
// Procedure:    SetLangCodes
//
// Description:
//  This function stores "PlatformLangCodes" variable
//
// Input:
//  IN CHAR16 *VariableName - Human-readable name of language variable
//  CHAR8* LangBuffer - pointer to list of language codes to store
//  UINTN LangBufferSize - size of the passed buffer
//
// Output:
//  None
//
//----------------------------------------------------------------------------
//<AMI_PHDR_END>
VOID SetLangCodes(CHAR16 *VariableName, CHAR8* LangBuffer, UINTN LangBufferSize){
    if (LangBuffer==NULL) return;
    pRS->SetVariable(
        VariableName, &guidEfiVar,
        EFI_VARIABLE_BOOTSERVICE_ACCESS |
        EFI_VARIABLE_RUNTIME_ACCESS,
        LangBufferSize, LangBuffer
    );
}

//<AMI_PHDR_START>
//----------------------------------------------------------------------------
// Procedure:    SetLang
//
// Description:
//  This function stores "PlatformLang" variable
//
// Input:
//  IN CHAR16 *VariableName - Human-readable name of language variable
//  CHAR8* LangBuffer - pointer to alanguage code to store
//  UINTN LangBufferSize - size of the passed buffer
//
// Output:
//  None
//
//----------------------------------------------------------------------------
//<AMI_PHDR_END>
VOID SetLang(CHAR16 *VariableName, CHAR8* LangBuffer, UINTN LangBufferSize){
    if (LangBuffer==NULL) return;
    pRS->SetVariable(
        VariableName, &guidEfiVar,
        EFI_VARIABLE_NON_VOLATILE |
        EFI_VARIABLE_BOOTSERVICE_ACCESS |
        EFI_VARIABLE_RUNTIME_ACCESS,
        LangBufferSize, LangBuffer
    );
}

//<AMI_PHDR_START>
//----------------------------------------------------------------------------
// Procedure:    SynchornizeLanguageVariables
//
// Description:
//  This function makes sure that all the Language variable are set to the 
//  same value.
//
// Input:
//  None
//
// Output:
//  None
//
// Notes:
//  Uses the following NVRAM variables
//  LangCodes, PlatformLangCodes, Lang, PlatformLang, LastLang
//----------------------------------------------------------------------------
//<AMI_PHDR_END>
VOID SynchornizeLanguageVariables(){
    CHAR8 *NativeLangBuffer;
    CHAR8 *CompatLangBuffer;
    CHAR8 *NativeLangCodesBuffer;
    CHAR8 *CompatLangCodesBuffer;
    UINTN NativeLangSize;
    UINTN CompatLangSize;
    UINTN NativeLangCodesSize;
    UINTN CompatLangCodesSize;
    BOOLEAN FreeNativeLangBuffer;

    //Set LanCodes variables
    NativeLangCodesBuffer = GetLangVariable(LastLangCodes, &guidSetup, &NativeLangCodesSize);
    SetLangCodes(NativeLangCodes, NativeLangCodesBuffer, NativeLangCodesSize);
    CompatLangCodesBuffer = LangNativeListToCompatList(
            NativeLangCodesBuffer, NativeLangCodesSize, &CompatLangCodesSize
    );
    SetLangCodes(CompatLangCodes, CompatLangCodesBuffer, CompatLangCodesSize);
    pBS->FreePool(CompatLangCodesBuffer);
    FreeNativeLangBuffer = FALSE;

    //Set Lang variables
    NativeLangBuffer = GetLangVariable(NativeLang, &guidEfiVar, &NativeLangSize); 
    CompatLangBuffer = GetLangVariable(CompatLang, &guidEfiVar, &CompatLangSize);
    if (!NativeLangBuffer && CompatLangBuffer){
        //Derive NativeLang value from the CompatLang
        NativeLangBuffer = LangToNative(CompatLangBuffer, &NativeLangSize);
        SetLang(NativeLang, NativeLangBuffer, NativeLangSize);
        pBS->FreePool(CompatLangBuffer);
    }else if (NativeLangBuffer && !CompatLangBuffer) {
        //Derive CompatLang value from the NativeLang
        CompatLangBuffer = LangToCompat(NativeLangBuffer,&CompatLangSize);
        SetLang(CompatLang,CompatLangBuffer,CompatLangSize); 
        FreeNativeLangBuffer = TRUE;
    }else if (!NativeLangBuffer && !CompatLangBuffer) {
        //Set NativeLang to the first language from the NativeLangCodes list
        NativeLangBuffer = GetFirstLang(NativeLangCodesBuffer, &NativeLangSize);
        SetLang(NativeLang, NativeLangBuffer, NativeLangSize);
        //Derive CompatLang value from the NativeLang
        CompatLangBuffer = LangToCompat(NativeLangBuffer,&CompatLangSize);
        SetLang(CompatLang,CompatLangBuffer,CompatLangSize); 
    }else{ //NativeLang && CompatLang
        CHAR8 *CompatLangInNativeFormat = LangToNative(CompatLangBuffer,NULL);
        if (!LanguageCodesEqual(CompatLangInNativeFormat,NativeLangBuffer)){
            CHAR8 *LastLangBuffer=GetLangVariable(LastLang, &guidSetup, NULL);
            if (LastLangBuffer && LanguageCodesEqual(LastLangBuffer,NativeLangBuffer)){
                pBS->FreePool(NativeLangBuffer);
                //Derive NativeLang value from the CompatLang
                NativeLangBuffer = LangToNative(CompatLangBuffer, &NativeLangSize);
                SetLang(NativeLang, NativeLangBuffer, NativeLangSize);
            }else{
                pBS->FreePool(CompatLangBuffer);
                //Derive CompatLang value from the NativeLang
                CompatLangBuffer = LangToCompat(NativeLangBuffer,&CompatLangSize);
                SetLang(CompatLang,CompatLangBuffer,CompatLangSize); 
                FreeNativeLangBuffer = TRUE;
            }
            pBS->FreePool(LastLangBuffer);
        }
    }
    pRS->SetVariable(
        LastLang, &guidSetup,
        EFI_VARIABLE_NON_VOLATILE |
        EFI_VARIABLE_BOOTSERVICE_ACCESS,
        NativeLangSize, NativeLangBuffer
    );
    if (FreeNativeLangBuffer) pBS->FreePool(NativeLangBuffer);
    pBS->FreePool(NativeLangCodesBuffer);
}

//<AMI_PHDR_START>
//----------------------------------------------------------------------------
// Procedure:    IsVarisbleExist
//
// Description:
//  Helper routine that checks if a given variable exists
//
// Input:
//  IN CHAR16 *VariableName - Name of the variable to check on
//  IN EFI_GUID *VendorGuid - GUID of the variable to check on
//
// Output:
//  TRUE - if variable exsits
//  FALSE - if variable does not exist
//
//----------------------------------------------------------------------------
//<AMI_PHDR_END>
BOOLEAN IsVariableExist(IN CHAR16 *VariableName, IN EFI_GUID *VendorGuid){
    UINTN Size=0;
    return 
           pRS->GetVariable(VariableName, VendorGuid, NULL, &Size, NULL)
        == EFI_BUFFER_TOO_SMALL;
}

//<AMI_PHDR_START>
//----------------------------------------------------------------------------
// Procedure:    SetupEntry
//
// Description:
//  This function is the entry point for the Setup driver. It registers the 
//  the Setup callback functions and then it checks if the
//  "Setup" and "Lang" variables are defined. If not it is a first boot
//  (first flash or first boot after BIOS upgrade) and these variables will 
//  need to be defined.
//  If "Setup" and "Lang" variables are defined, then make sure the language 
//  variables all agree and then return
//
// Input:
//  IN EFI_HANDLE ImageHandle - Image handle
//  IN EFI_SYSTEM_TABLE *SystemTable - pointer to the UEFI System Table
//
// Output:
//  EFI_SUCCESS
//
// Notes:
//
//----------------------------------------------------------------------------
//<AMI_PHDR_END>
EFI_STATUS SetupEntry(
    IN EFI_HANDLE ImageHandle, IN EFI_SYSTEM_TABLE   *SystemTable
)
{
    static EFI_EVENT SetupEnterEvent;
    static EFI_GUID guidSetupEnter = AMITSE_SETUP_ENTER_GUID;
#if FORCE_USER_TO_SETUP_ON_FIRST_BOOT
    static UINT32 BootFlow = BOOT_FLOW_CONDITION_FIRST_BOOT;
    static EFI_GUID guidBootFlow = BOOT_FLOW_VARIABLE_GUID;
#endif

    EFI_HANDLE Handle=NULL;

    ThisImageHandle = ImageHandle;
    InitAmiLib(ImageHandle,SystemTable);
    InitAmiSetupProtocol();
    pBS->SetMem(Setup, sizeof(Setup), 0);

    if (!IsVariableExist(LastLangCodes, &guidSetup))
    {   //If LastLangCodes Variable is not found,
        //this is first boot after FW upgrade.
        //We have to submit resources to HII to get Setup defaults
        //and list of supported languages.
        //After that we have to:
        //  1. If Setup variable is missing,
        //     initialize it with Defaults
        //  2. If Lang is missing, initialize
        //     Lang variable.
        //  3. Force user to go to Setup
        //    ( if FORCE_USER_TO_SETUP_ON_FIRST_BOOT SDL token is on).
        SetupCallback(NULL, NULL); //submit resources to HII and get defaults
        //Setup global variable is initialized during SetupCallback
#if EFI_SPECIFICATION_VERSION>0x20000
// TODO: Defaults initialization
#else
        if (!IsVariableExist(L"Setup", &guidSetup))
            pRS->SetVariable(
                L"Setup", &guidSetup,
                  EFI_VARIABLE_NON_VOLATILE
                | EFI_VARIABLE_BOOTSERVICE_ACCESS
                | EFI_VARIABLE_RUNTIME_ACCESS,
                sizeof(Setup), &Setup
            );
#endif
#if FORCE_USER_TO_SETUP_ON_FIRST_BOOT
        if (!IsVariableExist(L"BootFlow", &guidBootFlow)){
            return pRS->SetVariable(
                L"BootFlow", &guidBootFlow,
                EFI_VARIABLE_BOOTSERVICE_ACCESS,
                sizeof(BootFlow), &BootFlow);
        }
#endif
    }
    else
    {   //otherwise
        //  Register setup callbacks to submit resources to HII
        //     only if/when setup is launched
#if ALWAYS_PUBLISH_HII_RESOURCES
        SetupCallback(NULL, NULL);
#else
        VOID *pSetupRegistration;
        RegisterProtocolCallback(
            &guidSetupEnter, SetupCallback,
            NULL,&SetupEnterEvent, &pSetupRegistration
        );
#endif
    }
    SynchornizeLanguageVariables();
    return EFI_SUCCESS;
}

//<AMI_THDR_START>
//----------------------------------------------------------------------------
// Name:    SETUP_ITEM_CALLBACK
//
// Fields: Type Name Description
//  UINT16 Class - Primary identification value of an Hii Formset
//  UINT16 SubClass - Secondary identification value of an Hii Formset 
//  UINT16 Key - A unique value that identifies a specific item on a setup form
//  SETUP_ITEM_CALLBACK_HANDLER *UpdateItem - function used to update an item 
//                          defined by the Class, SubClass and Key parameters
//
// Description:
//  This Data Structure is used by the setup infrastructure to define 
//  callback functions that should be used for interacting with setup forms
//  or individual questions.
//
// Notes:
//   
//----------------------------------------------------------------------------
//<AMI_THDR_END>


// Brings the definitions of the SDL token defined list of callbacks into this
//  file as a list of functions that can be called
#define ITEM_CALLBACK(Class,Subclass,Key,Callback) Callback
extern SETUP_ITEM_CALLBACK_HANDLER SETUP_ITEM_CALLBACK_LIST EndOfList;
#undef ITEM_CALLBACK

// This creates an array of callbacks to be used 
#define ITEM_CALLBACK(Class,Subclass,Key,Callback) {Class,Subclass,Key,&Callback}
SETUP_ITEM_CALLBACK SetupItemCallback[] = { SETUP_ITEM_CALLBACK_LIST {0,0,0,NULL} };

CALLBACK_PARAMETERS *CallbackParametersPtr = NULL;
CALLBACK_PARAMETERS* GetCallbackParameters(){
    return CallbackParametersPtr;
}

static AMI_SETUP_PROTOCOL *AmiSetupProtocol = NULL;

//<AMI_PHDR_START>
//----------------------------------------------------------------------------
// Procedure:    Callback
//
// Description:
//  This function is used to identify the function to call when an interactive 
//  item has been triggered in the setup browser based on the information in
//  the Callback protocol and the SetupCallBack Array
//
// Input:
//  IN EFI_FORM_CALLBACK_PROTOCOL *This - Pointer to the instance of the callback 
//                                        protocol
//  IN UINT16 KeyValue - Unique value that defines the type of data to expect in 
//                       the Data parameter
//  IN EFI_IFR_DATA_ARRAY *Data - Data defined by KeyValue Parameter
//  OUT EFI_HII_CALLBACK_PACKET **Packet - Data passed from the Callback back to 
//                                         the setup Browser
//
// Output:
//  EFI_SUCCESS
//
//----------------------------------------------------------------------------
//<AMI_PHDR_END>
#if EFI_SPECIFICATION_VERSION>0x20000
EFI_STATUS Callback(
    IN CONST EFI_HII_CONFIG_ACCESS_PROTOCOL *This,
    IN EFI_BROWSER_ACTION Action,
    IN EFI_QUESTION_ID KeyValue,
    IN UINT8 Type,
    IN EFI_IFR_TYPE_VALUE *Value,
    OUT EFI_BROWSER_ACTION_REQUEST *ActionRequest
)
#else
EFI_STATUS Callback(
    IN EFI_FORM_CALLBACK_PROTOCOL *This,
    IN UINT16 KeyValue,
    IN EFI_IFR_DATA_ARRAY *Data,
    OUT EFI_HII_CALLBACK_PACKET **Packet
)
#endif
{
    UINTN i;
    SETUP_CALLBACK *pCallback = (SETUP_CALLBACK*)This;
    CALLBACK_PARAMETERS CallbackParameters;
    EFI_STATUS Status;
    SETUP_ITEM_CALLBACK *SetupItemCallbacks = NULL;
    UINTN FixedSize = sizeof(SetupItemCallback);
    UINTN VarSize = 0;
    UINT8 *CopyPointer;
    BOOLEAN AllocatedBuffer = FALSE;

#if EFI_SPECIFICATION_VERSION>0x20000
    CallbackParameters.This = (VOID*)This;
    CallbackParameters.Action = Action;
    CallbackParameters.KeyValue = KeyValue;
    CallbackParameters.Type = Type;
    CallbackParameters.Value = Value;
    CallbackParameters.ActionRequest = ActionRequest;
    if (ActionRequest) *ActionRequest=EFI_BROWSER_ACTION_REQUEST_NONE;
    Status = EFI_UNSUPPORTED;
#else
    CallbackParameters.This = This;
    CallbackParameters.KeyValue = KeyValue;
    CallbackParameters.Data = Data;
    CallbackParameters.Packet = Packet;
    Status = EFI_SUCCESS;
#endif

    CallbackParametersPtr = &CallbackParameters;

    if(AmiSetupProtocol == NULL) {
        Status = pBS->LocateProtocol(&AmiSetupProtocolGuid, NULL, &AmiSetupProtocol);
    }

//first get callbacks, registered at runtime
    Status = AmiSetupProtocol->GetCallbacks(&VarSize, SetupItemCallbacks);
    if(Status == EFI_NOT_FOUND) {   //no runtime callbacks registered
        SetupItemCallbacks = SetupItemCallback;
    } else if(Status == EFI_BUFFER_TOO_SMALL) {
        Status = pBS->AllocatePool(EfiBootServicesData, VarSize + FixedSize, &SetupItemCallbacks);
        if(EFI_ERROR(Status))
            return Status;
        AllocatedBuffer = TRUE;
        Status = AmiSetupProtocol->GetCallbacks(&VarSize, SetupItemCallbacks);
        //now add callbacks registered at build time via eLink
        CopyPointer = (UINT8 *)SetupItemCallbacks;
        CopyPointer += VarSize;
        MemCpy(CopyPointer, SetupItemCallback, FixedSize);
    }

    for(i=0; i<NUMBER_OF_FORMSETS; i++)
        if (SetupCallBack[i].Class == pCallback->Class && SetupCallBack[i].SubClass == pCallback->SubClass)
        {
            SETUP_ITEM_CALLBACK *pItemCallback = SetupItemCallbacks;
            while(pItemCallback->UpdateItem)
            {
                if (    pItemCallback->Class == pCallback->Class
                    &&  pItemCallback->SubClass == pCallback->SubClass
                    &&  pItemCallback->Key == KeyValue
                ){
                    Status = pItemCallback->UpdateItem(
                        SetupCallBack[i].HiiHandle,
                        pItemCallback->Class, pItemCallback->SubClass,
                        KeyValue
                    );
#if EFI_SPECIFICATION_VERSION>0x20000
                    if (Status != EFI_UNSUPPORTED) break;
#endif
                }
                pItemCallback++;
            }
        }
    CallbackParametersPtr = NULL;
    if(AllocatedBuffer)
        pBS->FreePool(SetupItemCallbacks);
    return Status;
}
//**********************************************************************
//**********************************************************************
//**                                                                  **
//**        (C)Copyright 1985-2010, American Megatrends, Inc.         **
//**                                                                  **
//**                       All Rights Reserved.                       **
//**                                                                  **
//**      5555 Oakbrook Parkway, Suite 200, Norcross, GA 30093        **
//**                                                                  **
//**                       Phone: (770)-246-8600                      **
//**                                                                  **
//**********************************************************************
//**********************************************************************
