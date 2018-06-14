//**********************************************************************
//**********************************************************************
//**                                                                  **
//**        (C)Copyright 1985-2010, American Megatrends, Inc.         **
//**                                                                  **
//**                       All Rights Reserved.                       **
//**                                                                  **
//**        5555 Oakbrook Pkwy, Suite 200, Norcross, GA 30093         **
//**                                                                  **
//**                       Phone: (770)-246-8600                      **
//**                                                                  **
//**********************************************************************
//*************************************************************************
// $Header: /Alaska/SOURCE/Modules/TCG2/Common/AmiTcgPlatform/AmiTcgPlatformDxe/AmiTcgPlatformDxe.h 1     4/21/14 2:17p Fredericko $
//
// $Revision: 1 $
//
// $Date: 4/21/14 2:17p $
//*************************************************************************
// Revision History
// ----------------
// $Log: /Alaska/SOURCE/Modules/TCG2/Common/AmiTcgPlatform/AmiTcgPlatformDxe/AmiTcgPlatformDxe.h $
// 
// 1     4/21/14 2:17p Fredericko
// 
// 1     10/08/13 12:04p Fredericko
// Initial Check-In for Tpm-Next module
// 
// 2     10/03/13 2:19p Fredericko
// 
// 1     7/10/13 5:55p Fredericko
// [TAG]  		EIP120969
// [Category]  	New Feature
// [Description]  	TCG (TPM20)
// 
// 11    1/20/12 9:20p Fredericko
// 
// 10    12/30/11 5:06p Fredericko
// [TAG]  		EIP78141
// [Category]  	New Feature
// [Description]  	Added hooks to override generic TPM platform hash
// functions.
// [Files]  		1. AmiTcgPlatform.sdl
// 2. AmiTcgPlatformPei.h
// 3. AmiTcgPlatformPeiLib.c
// 4. AmiTcgPlatformPeiAfterMem.c
// 5. AmiTcgPlatformDxe.c
// 6. AmiTcgPlatformDxe.h
// 
// 9     11/28/11 7:31p Fredericko
// [TAG]  		EIP63922
// [Category]  	Improvement
// [Description]  	Support for Smbios label 30 and up. Callback on
// publishing of Smbios tables
// [Files]		AmiTcgPlatformDxe.c
// 
// 8     10/10/11 11:36a Fredericko
// [TAG]  		EIP70220
// [Category]  	Improvement
// [Description]  	Remove dependency on CSM
// [Files]  		TcgLegacy.sdl
// AmiTcgPlatformDxe.c
// AmiTcgPlatformDxe.h
// xTcgDxe.c
// 
// 7     10/10/11 12:12a Fredericko
// [TAG]  		EIP70220
// [Category]  	Improvement
// [Description]  	Remove dependency on CSM
// [Files]  		TcgLegacy.sdl
// AmiTcgPlatformDxe.c
// AmiTcgPlatformDxe.h
// xTcgDxe.c
// 
// 6     7/25/11 3:43a Fredericko
// [TAG]  		EIP65177
// [Category]  	Spec Update
// [Severity]  	Minor
// [Description]  	Tcg Ppi Spec ver 1.2 update
// 
// 5     4/28/11 6:34p Fredericko
// Removed VFR compile
// 
// 4     4/26/11 1:54p Fredericko
// Added support for function level override of specific functions. GUID
// definitions added
// 
// 3     4/06/11 10:40a Fredericko
// Core 4.6.5.0 build error changes
// 
// 2     3/29/11 2:27p Fredericko
// [TAG]        EIP 54642
// [Category] Improvement
// [Description] 1. Checkin Files related to TCG function override 
// 2. Include TCM and TPM auto detection
// [Files] Affects all TCG files
//
// 
//*************************************************************************
//<AMI_FHDR_START>
//
// Name:	AmiTcgPlatformDxe.h
//
// Description:	Header file for AmiTcgPlatformDxe
//
//<AMI_FHDR_END>
//*************************************************************************
#include <EFI.h>
#include "TcgPc.h"
#include <AmiLib.h>
#include <AmiDxeLib.h>
#include <TcgCommon.h>
#include <token.h>
#if SMBIOS_SUPPORT == 1
  #include <SmBios.h>
#endif
#include <TcgMisc.h>
#include <protocol\TcgService\TcgTcmService.h>
#include <protocol\TcgService\TcgService.h>
#include <Protocol\TpmDevice\TpmDevice.h>
#include <Include/Setup.h>
#include "Protocol/CpuIo.h"
#include "Protocol/FirmwareVolume.h"
#include "Protocol/DevicePath.h"

#if ( defined(CSM_SUPPORT) && (CSM_SUPPORT != 0) )
#include "Protocol/LegacyBios.h"
#endif

#include "Protocol/PciIo.h"
#include "Protocol/Variable.h"
#include "Protocol/Reset.h"
#include "Protocol/SimpleTextOut.h"
#include "Protocol/SimpleTextIn.h"
#include "Protocol/UgaDraw.h"
#include "AMIPostMgr.h"
#if EFI_SPECIFICATION_VERSION>0x20000 
    #include "Include\UefiHii.h"
    #include "Protocol/HiiDatabase.h"
    #include "Protocol/HiiString.h"
#else
  #include "Protocol/HII.h"
#endif
#include <Protocol\SmmBase.h>
#include <Protocol\SmmSwDispatch.h>
#include <Include\Acpi.h>
#include <Include\Acpi11.h>
#include "AmiTcgPlatformDxeLib.h"
#include <AcpiRes.h>




//--------------------------------------------------------------------------
//GUID Definitions
//--------------------------------------------------------------------------
#define EFI_SMBIOS_TABLE_GUID \
    {0xeb9d2d31, 0x2d88, 0x11d3, 0x9a, 0x16, 0x0, 0x90, 0x27, 0x3f, 0xc1, 0x4d}

#define AMI_TCG_PLATFORM_PROTOCOL_GUID\
    {0x8c939604, 0x700, 0x4415, 0x9d, 0x62, 0x11, 0x61, 0xdb, 0x81, 0x64, 0xa6}

#define  AMI_PROCESS_TCG_PPI_REQUEST_GUID\
    { 0x30ad2b83, 0xadd0, 0x414b, 0xb1, 0x1c, 0xf9, 0x3c, 0xc1, 0xd0, 0xb7,\
      0x9b}

#define  AMI_PROCESS_TCG_SETUP_GUID\
    { 0xc77dd102, 0x1db4, 0x4997, 0xae, 0x37, 0x4e, 0x8c, 0x52, 0x1e, 0xf5,\
      0x67}

#define  AMI_MEASURE_CPU_MICROCODE_GUID\
    { 0x5cf308b5, 0xfa23, 0x4100, 0x8a, 0x76, 0xf3, 0x26, 0xc2, 0x81, 0x48,\
      0x80}

#define  AMI_MEASURE_PCIOPROM_GUID\
    { 0x76f3992d, 0x529e, 0x4efe, 0x8b, 0xbe, 0x8e, 0x1e, 0xd4, 0x32, 0xc2,\
      0x23}

#define  AMI_SET_TCG_READYTOBOOT_GUID\
    { 0xa4524a9c, 0xb5e, 0x492d, 0xae, 0xc9, 0x30, 0x86, 0x31, 0xb1, 0x89,\
      0xb4}

#define TCG_SMBIOS_EFI_TABLE_GROUP \
    { 0xb3dae700, 0x2a77, 0x4ea4, 0xaf, 0x79, 0x32, 0x97, 0xb4, 0x84, 0xbe, 0x61 } 


EFI_GUID gEfiSmbiosTableGuid = EFI_SMBIOS_TABLE_GUID;

#define    MINI_SETUP_GUID { 0xB1DA0ADF, 0x4F77, 0x4070,\
      { 0xA8, 0x8E, 0xBF, 0xFE, 0x1C, 0x60, 0x52, 0x9A } }

#define   GUID_VARIABLE_DECLARATION( Variable, Guid ) extern EFI_GUID Variable

EFI_GUID  gMicrocodeGuid = {
    0x17088572, 0x377F, 0x44ef, 0x8F, 0x4E, 0xB0, 0x9F, 0xFF, 0x46, 0xA0, 0x70
};

#if TPM_PASSWORD_AUTHENTICATION

EFI_GUID  gAmitseAdminPasswordValidGuid = AMITSE_ADMIN_PASSWORD_VALID_GUID;


#define AMITSE_PASSWORD_PROMPT_EXIT_GUID { 0xb9b038b0, 0xe2b6, 0x4aab, \
    0x94, 0x35, 0x41, 0x65, 0xec, 0xfe, 0xd0, 0x32 }


EFI_GUID  gAmitsePasswordPromptExitGuid = AMITSE_PASSWORD_PROMPT_EXIT_GUID;

#define AMITSE_PASSWORD_PROMPT_ENTER_GUID \
{ 0x73e7e01, 0x2611, 0x4e85, 0xb8, 0x96, 0xa3, 0xb6, 0x76, 0x7c, 0xba, 0x0 }
  
EFI_GUID  gAmitsePasswordPromptEnterGuid = AMITSE_PASSWORD_PROMPT_ENTER_GUID;
#endif

EFI_GUID  gEfiTcgProtocolGuid = EFI_TCG_PROTOCOL_GUID;
EFI_GUID  gDsdtGuidDxe        = DSDT_GUID;
EFI_GUID  TcgEfiGlobalVariableGuid = TCG_EFI_GLOBAL_VARIABLE_GUID;


#define TCG_DEACTIVED_ERROR  0x06

//---------------------------------------------------------------------------
//      Structure Definitions
//---------------------------------------------------------------------------
#if defined CORE_REVISION && CORE_REVISION < 5
typedef struct _EFI_LIST_ENTRY
{
    struct _EFI_LIST_ENTRY *ForwardLink;
    struct _EFI_LIST_ENTRY *BackLink;
} EFI_LIST_ENTRY;
#endif

typedef struct
{
    UINTN          Signature;
    EFI_LIST_ENTRY AllEntries;            // All entries
    EFI_GUID       ProtocolID;            // ID of the protocol
    EFI_LIST_ENTRY Protocols;             // All protocol interfaces
    EFI_LIST_ENTRY Notify;                // Registerd notification handlers
} TCG_PROTOCOL_ENTRY;

typedef struct
{
    UINTN              Signature;
    TCG_PROTOCOL_ENTRY *Protocol;
    EFI_LIST_ENTRY     Link;                  // All notifications for this protocol
    EFI_EVENT          Event;                 // Event to notify
    EFI_LIST_ENTRY     *Position;              // Last position notified
} TCG_PROTOCOL_NOTIFY;

typedef struct
{
    UINT8 MajorVersion;
    UINT8 MinorVersion;
    UINT8 Reserve;
    UINT8 Flag;
} AMI_TCG_PROTOCOL_VERSION;




//**********************************************************************
//              Function Declarations
//**********************************************************************
EFI_STATUS 
OnAcpiInstalled(IN EFI_EVENT ev,
  IN VOID  *ctx );



EFI_STATUS measureCpuMicroCode();


EFI_FORWARD_DECLARATION( AMI_TCG_PLATFORM_PROTOCOL );


typedef
EFI_STATUS
(EFIAPI * MEASURE_CPU_MICROCODE)(

);


typedef
EFI_STATUS
(EFIAPI * MEASURE_HANDOFF_TABLES)(

);


typedef
EFI_STATUS
(EFIAPI * MEASURE_PCI_OPROMS)(

);


typedef
EFI_STATUS
(EFIAPI * PROCESS_TCG_SETUP)(

);



typedef
EFI_STATUS
(EFIAPI * PROCESS_TCG_PPI_REQUEST)(

);



typedef
EFI_STATUS
(EFIAPI * MEASURE_VARIABLES)(

);


typedef
EFI_STATUS
(EFIAPI * TCG_READY_TO_BOOT)(

);

typedef
EFI_STATUS
(EFIAPI * GET_PROTOCOL_VERSION)(
    AMI_TCG_PROTOCOL_VERSION *
);

typedef
EFI_STATUS
(EFIAPI * GET_)(
    AMI_TCG_PROTOCOL_VERSION *
);


typedef
VOID
(EFIAPI * RESETOSTCGVAR)(
); 


typedef
EFI_STATUS
(EFIAPI * AMI_TCG_DXE_FUNCTION_OVERRIDE)(
);



typedef struct _AMI_TCG_DXE_FUNCTION_OVERRIDE_PROTOCOL
{
    AMI_TCG_DXE_FUNCTION_OVERRIDE   Function;
} AMI_TCG_DXE_FUNCTION_OVERRIDE_PROTOCOL;



typedef EFI_STATUS (MEASURE_PCI_OPTION_ROM_FUNC_PTR)(
);

typedef EFI_STATUS (MEASURE_HANDOFF_TABLES_FUNC_PTR)(
);


typedef EFI_STATUS (MEASURE_CPU_MICROCODE_FUNC_PTR)(
);


typedef EFI_STATUS (MEASURE_BOOT_VAR_FUNC_PTR)(
);

#if (defined(TCGMeasureSecureBootVariables) && (TCGMeasureSecureBootVariables!= 0))
typedef EFI_STATUS (MEASURE_SECURE_BOOT_FUNC_PTR)(
);
#endif


typedef EFI_STATUS (MEASURES_TCG_BOOT_SEPARATORS_DXE_FUNC_PTR)(
   
);


typedef EFI_STATUS (MEASURE_WAKE_EVENT_DXE_FUNC_PTR)(
);

typedef UINT8 (SKIP_PHYSICAL_PRESENCE_LOCK_PTR)(
);

extern MEASURE_PCI_OPTION_ROM_FUNC_PTR  *MeasurePCIOpromsFuncPtr;
extern MEASURE_HANDOFF_TABLES_FUNC_PTR  *MeasureHandoffTablesFuncPtr;
extern MEASURE_CPU_MICROCODE_FUNC_PTR   *MeasureCpuMicroCodeFuncPtr;
extern MEASURE_BOOT_VAR_FUNC_PTR        *MeasureAllBootVariablesFuncPtr;
#if (defined(TCGMeasureSecureBootVariables) && (TCGMeasureSecureBootVariables != 0))
extern MEASURE_SECURE_BOOT_FUNC_PTR     *MeasureSecurebootVariablesFuncPtr;
#endif
extern MEASURES_TCG_BOOT_SEPARATORS_DXE_FUNC_PTR      *MeasureSeparatorsFuncPtr;
extern MEASURE_WAKE_EVENT_DXE_FUNC_PTR                *MeasureWakeEventFuncPtr;

typedef struct _AMI_TCG_PLATFORM_PROTOCOL
{
    MEASURE_CPU_MICROCODE       MeasureCpuMicroCode;
    MEASURE_PCI_OPROMS          MeasurePCIOproms;
    PROCESS_TCG_SETUP           ProcessTcgSetup;
    PROCESS_TCG_PPI_REQUEST     ProcessTcgPpiRequest;
    TCG_READY_TO_BOOT           SetTcgReadyToBoot;
    GET_PROTOCOL_VERSION        GetProtocolVersion;
    RESETOSTCGVAR               ResetOSTcgVar;
} AMI_TCG_PLATFORM_PROTOCOL;

extern EFI_GUID gEfiTcgProtocolGuid;
//**********************************************************************
//**********************************************************************
//**                                                                  **
//**        (C)Copyright 1985-2010, American Megatrends, Inc.         **
//**                                                                  **
//**                       All Rights Reserved.                       **
//**                                                                  **
//**     5555 Oakbrook Pkwy, Suite 200, Norcross, GA 30093            **
//**                                                                  **
//**                       Phone: (770)-246-8600                      **
//**                                                                  **
//**********************************************************************
//**********************************************************************
