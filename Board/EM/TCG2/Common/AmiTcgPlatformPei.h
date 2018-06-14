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
// $Header: /Alaska/SOURCE/Modules/TCG2/Common/AmiTcgPlatform/AmiTcgPlatformPei/AmiTcgPlatformPei.h 1     4/21/14 2:17p Fredericko $
//
// $Revision: 1 $
//
// $Date: 4/21/14 2:17p $
//*************************************************************************
// Revision History
// ----------------
// $Log: /Alaska/SOURCE/Modules/TCG2/Common/AmiTcgPlatform/AmiTcgPlatformPei/AmiTcgPlatformPei.h $
// 
// 1     4/21/14 2:17p Fredericko
// 
// 1     10/08/13 12:03p Fredericko
// Initial Check-In for Tpm-Next module
// 
// 1     7/10/13 5:54p Fredericko
// [TAG]  		EIP120969
// [Category]  	New Feature
// [Description]  	TCG (TPM20)
// 
// 6     12/30/11 4:40p Fredericko
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
// 5     9/01/11 2:25p Fredericko
// [TAG]  		EIP66113
// [Category]  	Improvement
// [Description]  	Support LTsx on server platforms where startup commands
// are sent by the ACM binaries.
// [Files]  		AmiTcgPlatformPeiBoardBeforeMem.c
// AmiTcgPlatformPeiLib.c
// AmiTcgPlatformPei.h
// 
// 4     4/28/11 6:30p Fredericko
// Removed VFR compile
// 
// 3     4/26/11 1:51p Fredericko
// Added support for function level override of specific functions. GUID
// definitions added and generic function override definition also added.
// 
// 2     3/29/11 2:18p Fredericko
// [TAG]        EIP 54642
// [Category] Improvement
// [Description] 1. Checkin Files related to TCG function override 
// 2. Include TCM and TPM auto detection
// [Files] Affects all TCG files
//
//
// 
//*************************************************************************
//<AMI_FHDR_START>
//
// Name:	AmiTcgPlatformPei.h
//
// Description:	Header file for AmiTcgPlatformPei
//
//<AMI_FHDR_END>
//*************************************************************************
#include <Include/Setup.h>

#define AMI_TCG_PLATFORM_PPI_BEFORE_MEM_GUID\
    {0xc1e6791d, 0xf35b, 0x43ef, 0x92, 0xa, 0xbe, 0x6, 0xba, 0x7f, 0x86, 0xa1}

#define AMI_TCG_PLATFORM_PPI_AFTER_MEM_GUID\
    {0x890c2cef, 0x43c8, 0x4209, 0xa7, 0x8d, 0xae, 0x14, 0xaa, 0x17, 0x98, 0xb4}

#define EFI_PEI_PERMANENT_MEMORY_INSTALLED_PPI \
  {0xf894643d, 0xc449, 0x42d1, 0x8e, 0xa8, 0x85, 0xbd, 0xd8, 0xc6, 0x5b, 0xde}

#define TCG_LOCK_DOWN_VAR_GUID\
  {0x6e605536, 0xa30a, 0x4d56, 0x93, 0x9e, 0x1c, 0x37, 0x3f, 0x79, 0x8d, 0x7b}

#define  AMI_MEMORY_ABSENT_OVERRIDE_GUID\
    { 0x9c109e5e, 0xbf38, 0x4a78, 0x9c, 0xac, 0x43, 0xde, 0x7e, 0x72, 0x6f,\
      0x9e}

#define  AMI_VERIFY_TCG_VARIABLES_GUID\
    { 0x4f44fa64, 0xa8d6, 0x4c19, 0xb6, 0x1d, 0x63, 0x10, 0x9d, 0x77, 0xd3,\
      0xd2}

#define  AMI_MEMORY_PRESENT_FUNCTION_OVERRIDE_GUID\
    { 0x4d7161bc, 0xbe35, 0x43af, 0x87, 0x9b, 0x95, 0x6e, 0xb3, 0x79, 0x83,\
      0xd6}

#define  AMI_SET_PHYSICAL_PRESENCE_GUID\
    { 0x126f424e, 0xf45b, 0x4406, 0x80, 0x1e, 0x2a, 0xac, 0xf4, 0x4, 0x16,\
      0x7f}

#define AMI_SKIP_TPM_STARTUP_GUID \
    { 0x6ee1b483, 0xa9b8, 0x4eaf, 0x9a, 0xe1, 0x3b, 0x28, 0xc5, 0xcf, 0xf3,\
      0x6b}


#define EFI_MAX_BIT       0x80000000

#define TCG_LOG_MAX_TABLE_SIZE      0x100
#define _CR( Record, TYPE,\
       Field )((TYPE*) ((CHAR8*) (Record) - (CHAR8*) &(((TYPE*) 0)->Field)))


static EFI_GUID gSetupGuid = SETUP_GUID;

#pragma pack (1)
typedef struct
{
    EFI_PHYSICAL_ADDRESS PostCodeAddress;
    #if x64_BUILD
    UINT64 PostCodeLength;
    #else
    UINTN PostCodeLength;
    #endif
} EFI_TCG_EV_POST_CODE;

typedef struct
{
    EFI_TCG_PCR_EVENT_HEADER Header;
    EFI_TCG_EV_POST_CODE     Event;
} PEI_EFI_POST_CODE;

typedef struct
{
    EFI_TCM_PCR_EVENT_HEADER Header;
    EFI_TCG_EV_POST_CODE     Event;
} TCM_PEI_EFI_POST_CODE;
#pragma pack ()

typedef struct _TCG_PEI_MEMORY_CALLBACK
{
    EFI_PEI_NOTIFY_DESCRIPTOR NotifyDesc;
    EFI_FFS_FILE_HEADER       *FfsHeader;
} TCG_PEI_MEMORY_CALLBACK;


EFI_FORWARD_DECLARATION( AMI_TCG_PLATFORM_PPI );


typedef
EFI_STATUS
(EFIAPI * SET_TPM_PHYSICAL_PRESENCE)(
    IN EFI_PEI_SERVICES **PeiServices 
);


typedef
EFI_STATUS
(EFIAPI * MEMORY_PRESENT_ENTRY)(
    IN EFI_PEI_SERVICES **PeiServices 
);


typedef
EFI_STATUS
(EFIAPI * MEMORY_ABSENT_ENTRY)(
    IN EFI_PEI_SERVICES    **PeiServices 
);


typedef
EFI_STATUS
(EFIAPI * READ_RESET_MOR)(
    IN EFI_PEI_SERVICES    **PeiServices 
);

typedef
EFI_STATUS 
(EFIAPI * VERIFYTCGVARIABLES)(
    IN EFI_PEI_SERVICES    **PeiServices 
);



TPM_Capabilities_PermanentFlag TCGPEI_GETCAP(
    IN EFI_PEI_SERVICES **PeiServices );

void
EFIAPI xTcgPeiEntry(
    IN PEI_TCG_PPI         *tcg,
    IN EFI_FFS_FILE_HEADER *FfsHeader,
    IN EFI_PEI_SERVICES    **ps );


//-----------------------------------------------------------
//HELPER FUNCTIONS
//-----------------------------------------------------------
VOID OverwriteSystemMemory(
IN EFI_PEI_SERVICES    **PeiServices
);


EFI_STATUS MeasureCRTMVersion(
    IN EFI_PEI_SERVICES    **PeiServices 
);


EFI_STATUS
 MeasureTcmCRTMVersion(
    IN EFI_PEI_SERVICES **PeiServices 
);

EFI_STATUS TcgPeiTpmStartup(
    IN EFI_PEI_SERVICES **PeiServices,
    IN EFI_BOOT_MODE    BootMode 
);

EFI_STATUS SendStartupandSelftest(
    IN EFI_PEI_SERVICES **PeiServices,
    IN EFI_BOOT_MODE    BootMode
);

TCM_Capabilities_PermanentFlag TCMPEI_GETCAP(
IN EFI_PEI_SERVICES **PeiServices );


EFI_STATUS MeasureDxeCoreFwVol(
    IN PEI_TCG_PPI                * tcg,
    IN EFI_PEI_SERVICES           **ps,
    IN EFI_FIRMWARE_VOLUME_HEADER *fwv 
);

BOOLEAN Lock_TPMPhysicalPresence(
    IN EFI_PEI_SERVICES **PeiServices 
);


EFI_STATUS ContinueTPMSelfTest(
     IN EFI_PEI_SERVICES **ps 
);

EFI_STATUS MeasureTCGPcClientSpecID(
    IN EFI_PEI_SERVICES **ps, 
    IN PEI_TCG_PPI      *tcg
);

EFI_STATUS LocateTcgPpi(
    IN EFI_PEI_SERVICES **PeiServices,
    IN PEI_TPM_PPI      **gTpmDevicePpi,
    IN PEI_TCG_PPI      **gTcgPpi
);

EFI_STATUS LocateTcmPpi(
    IN EFI_PEI_SERVICES **PeiServices,
    IN PEI_TPM_PPI      **gTpmDevicePpi,
    IN PEI_TCM_PPI      **gTcmPpi
);


EFI_STATUS TcgPeiBuildHobGuid(
    IN EFI_PEI_SERVICES **PeiServices,
    IN EFI_GUID         *Guid,
    IN UINTN            DataLength,
    OUT VOID            **Hob );


typedef
EFI_STATUS
(EFIAPI * AMI_TCG_PEI_FUNCTION_OVERRIDE)(
    IN EFI_PEI_SERVICES **PeiServices 
);



EFI_STATUS FindDxeCoreFile(
    IN EFI_PEI_SERVICES            **ps,
    OUT EFI_FIRMWARE_VOLUME_HEADER **fwMain );

typedef struct _AMI_TCG_PLATFORM_PPI_AFTER_MEM
{
    SET_TPM_PHYSICAL_PRESENCE   SetPhysicalPresence;
    MEMORY_PRESENT_ENTRY        MemoryPresentFunctioOverride;
    VERIFYTCGVARIABLES          VerifyTcgVariables;
} AMI_TCG_PLATFORM_PPI_AFTER_MEM;


typedef struct _AMI_TCG_PLATFORM_PPI_BEFORE_MEM
{
    MEMORY_ABSENT_ENTRY         MemoryAbsentFunctionOverride;
} AMI_TCG_PLATFORM_PPI_BEFORE_MEM;


typedef struct _AMI_TCG_PEI_FUNCTION_OVERRIDE_PPI
{
    AMI_TCG_PEI_FUNCTION_OVERRIDE   Function;
} AMI_TCG_PEI_FUNCTION_OVERRIDE_PPI;

typedef EFI_STATUS (MEASURE_CRTM_VERSION_PEI_FUNC_PTR)(
    IN EFI_PEI_SERVICES **PeiServices
);

typedef EFI_STATUS (MEASURE_TCG_PCCLIENT_ID_PEI_FUNC_PTR)(
    IN EFI_PEI_SERVICES **ps, 
    IN PEI_TCG_PPI      *tcg
);

typedef EFI_STATUS (MEASURE_CORE_DXE_FW_VOL_PEI_FUNC_PTR)(
    IN PEI_TCG_PPI                * tcg,
    IN EFI_PEI_SERVICES           **ps,
    IN EFI_FIRMWARE_VOLUME_HEADER *fwv
);

extern MEASURE_CRTM_VERSION_PEI_FUNC_PTR        *MeasureCRTMVersionFuncPtr;
extern MEASURE_TCG_PCCLIENT_ID_PEI_FUNC_PTR     *MeasureTCGPcClientSpecIDFuncPtr;
extern MEASURE_CORE_DXE_FW_VOL_PEI_FUNC_PTR     *MeasureDxeCoreFwVolFuncPtr;


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
