//**********************************************************************
//**********************************************************************
//**                                                                  **
//**        (C)Copyright 1985-2010, American Megatrends, Inc.         **
//**                                                                  **
//**                       All Rights Reserved.                       **
//**                                                                  **
//**             5555 Oakbrook Parkway, Suite 200, Norcross, GA 30093 **
//**                                                                  **
//**                       Phone: (770)-246-8600                      **
//**                                                                  **
//**********************************************************************
//**********************************************************************
//**********************************************************************
// $Header: /Alaska/SOURCE/Modules/TCG2/Common/TcgDxe/xTcgDxe.c 2     6/14/14 12:28a Fredericko $
//
// $Revision: 2 $
//
// $Date: 6/14/14 12:28a $
//**********************************************************************
// Revision History
// ----------------\
// $Log: /Alaska/SOURCE/Modules/TCG2/Common/TcgDxe/xTcgDxe.c $
// 
// 2     6/14/14 12:28a Fredericko
// 
// 1     4/21/14 2:16p Fredericko
// 
// 2     10/31/13 11:20a Fredericko
// 
// 1     10/08/13 12:03p Fredericko
// Initial Check-In for Tpm-Next module
// 
// 2     10/03/13 2:01p Fredericko
// 
// 1     7/10/13 5:51p Fredericko
// [TAG]  		EIP120969
// [Category]  	New Feature
// [Description]  	TCG (TPM20)
// 
// 105   12/10/12 6:24p Fredericko
// 
// 104   12/03/12 11:01p Fredericko
// [TAG]  		EIP104961
// [Category]  	Bug Fix
// [Severity]  	Minor
// [Symptom]  	UEFI 2.3.1 SCT test failed in Generic\EfiCompliant case.
// The VariableAttribute of SecureBoot is not correct.
// [RootCause]  	Changes to Secureboot module
// [Solution]  	Remove secureboot variable check in Tcg
// [Files]  		AmiTcgPlatformDxe.c
// xTcgdxe.c
// 
// 103   10/30/12 11:31a Fredericko
// 
// 102   9/13/12 5:09p Fredericko
// [TAG]  		EIP96217
// [Category]  	Bug Fix
// [Severity]  	Normal
// [Symptom]  	AMIUEFI: Only one EV_EFI_VARIABLE_AUTHORITY event instead
// of two when an EFI application or driver is not executed because of a
// Secure Boot violation and then booted into Windows ( Winqual Bug ID :
// 958465 )
// [RootCause]  	Not measuring Subsequent Certificate Authority that can
// be loaded after boot before ExitBootServices is called
// [Solution]  	Measuring all Subsequent Certificate Authority that can be
// loaded after boot before ExitBootServices is called
// Also EIP [96218]: Measure Zero Events for when SecureBootSupport is
// enabled but Keys are not installed
// [Files]  		xTcgDxe.c
// AmiTcgPlatformDxe.c
// 
// 101   5/09/12 3:52p Fredericko
// Changes for the measurement for Certificate Authority for secureboot.
// 
// 100   4/28/12 3:28p Fredericko
// Changed When gpt is measured as well as put Perf macro for DP
// information.
// 
// 99    4/19/12 5:57p Fredericko
// EIP: 85771. Fixes for measurement of gpt partitions on EFI platform.
// First boot scenario after flashing was failing sometimes.
// 
// 97    3/19/12 6:32p Fredericko
// [TAG]  		EIP82769
// [Category]  	Improvement
// [Description]  	Firmware updates disable the TPM when Firmware update
// is done
// [Files]  		xTcgPei.c, xTcgDxe.c, TcgDxe.c
// 
// 96    12/15/11 3:25p Fredericko
// 
// 95    12/12/11 3:37p Fredericko
// [TAG]  		EIP76865
// [Category]  	Improvement
// [Description]  	Dual Support for TCM and TPM. System could hang in TXT
// if txt is enabled in setup
// [Files]  		AmiTcgPlatfompeilib.c, AmiTcgPlatformPpi.cif,
// AmiTcgPlatformPpi.h, AmiTcgPlatformProtocol.cif,
// AmiTcgPlatformProtocol.h,
// EMpTcmPei.c, TcgDxe.cif, TcgPei.cif, TcgPeiAfterMem.cif,
// TcgPeiAfterMem.mak, TcgTcmPeiAfterMem.c, xTcgDxe.c, xTcgPei.c, 
// xTcgPeiAfterMem.c
// 
// 94    11/17/11 2:31p Fredericko
// Changes for AmiTcgSetup for cases when TPM is plug into board after
// first boot.
// 
// 93    10/26/11 3:15p Fredericko
// Changes for First boot scenerio and when Tcg Support is enabled and
// Disabled
// 
// 92    10/10/11 12:06a Fredericko
// [TAG]  		EIP70220
// [Category]  	Improvement
// [Description]  	Remove dependency on CSM
// [Files]  		TcgLegacy.sdl
// AmiTcgPlatformDxe.c
// AmiTcgPlatformDxe.h
// xTcgDxe.c
// 
// 91    9/27/11 10:26p Fredericko
// [TAG]  		EIP67286
// [Category]  	Improvement
// [Description]  	changes for Tcg Setup policy
// [Files]  		Tcg.sdl
// TcgPei.cif
// TcgPei.mak
// xtcgPei.c
// xTcgPeiAfterMem.c
// TcgPeiAfterMem.mak
// TcgDxe.cif
// TcgDxe.mak
// xTcgDxe.c
// AmiTcgPlatformPeilib.c
// AmiTcgPlatformDxelib.c
// 
// 90    9/03/11 8:05p Fredericko
// 
// 89    8/29/11 6:50p Fredericko
// [TAG]  		EIP0000
// [Category]  	Improvement
// [Description]  	Tcg Setup improvement. Logic for when Tcgsupport is
// enabled.
// [Files]  		xtcgdxe.c
// 
// 88    4/18/11 5:00p Fredericko
// 
// 87    3/29/11 9:17p Fredericko
// Don't install platform protocol if there is a TPM device error from
// startup command or selftest
// 
// 86    3/29/11 1:13p Fredericko
// 
// 85    3/28/11 2:20p Fredericko
// [TAG]        EIP 54642
// [Category] Improvement
// [Description] 1. Checkin Files related to TCG function override
// 2. Include TCM and TPM auto detection
// [Files] Affects all TCG files
// 
// 82    10/07/10 10:37a Fredericko
// [TAG]             EIP45667
// [Category]      BUG FIX
// [Severity]	      Normal
// [Symptom]      Fail to get AMITSEVar
// [RootCause]   Uninitialized variable
// [Solution]        Initialize Size variable in prompt_operation function
// [Files]              xtcgdxe.c
// 
// 81    9/23/10 6:12p Fredericko
// [TAG]    	 EIP42580 
// [Category] BUG FIX
// [Severity]   Normal
// [Symptom] TPM prompt message override on LOGO mode 
// [RootCause]  Proper SDL token comparism
// [Solution]	Use proper SDL token comparism
// [Files]	 xtcgdxe.c
// 
// 80    8/31/10 2:18p Fredericko
// Workaround TSE problem with using AMIpost Manager for string display.
// 
// 79    8/19/10 5:28p Fredericko
// Edit display string positions on screen.
// 
// 78    8/13/10 11:06a Fredericko
// [TAG]   N\A
// [Category] IMPROVEMENT
// [Description] Support for core 4.6.4.x and UEFI 2.1 Specifications
// [FILES] xTcgDxe.c, TPMPwd.c
// 
// 77    8/10/10 6:11p Fredericko
// String display operations changes. 
// 
// 76    8/09/10 3:49p Fredericko
// UEFI 2.1 changes
// 
// 75    8/09/10 2:23p Fredericko
// UEFI 2.1 changes
// 
// 74    8/04/10 5:18p Fredericko
// Reset system after executing owner commands. Special case.
// 
// 73    7/13/10 5:37p Fredericko
// 
// 72    7/09/10 3:39p Fredericko
// modified platform protocol
// 
// 71    6/02/10 5:06p Fredericko
// Do nothing on some TPM error scenerios. We were shutting down the
// system before.
// 
// 70    5/21/10 4:03p Fredericko
// Hii String package changes
// 
// 68    5/21/10 11:37a Rizwank
// Changes to include proper strings token header when AMI_TCG_MESSAGE is
// enabled
// Use correct imagehandle name
// 
// 67    5/20/10 5:37p Fredericko
//       
// 
// 65    5/20/10 9:02a Fredericko
// Included File Header
// Code Beautification
// EIP 37653
//
// 64    4/30/10 5:01p Fredericko
// EIP 36943: Was not writing TPM results and clearing TPM request on a
// special case.
//
// 63    4/21/10 11:50a Fredericko
// Removal of functions that are no needed anymore for multi language
// support.
//
// 62    3/23/10 8:42p Fredericko
// TcgLegacy event moved to subcomponent
//
// 61    3/19/10 4:20p Fredericko
// modified for legacy IO interface support
//
// 60    1/14/10 11:57a Fredericko
// Physical presence lifetime lock support added.
//
// 59    12/31/09 2:52p Fredericko
// modified to allow the setting of lifetime lock on physical presence
//
// 58    11/17/09 5:53p Fredericko
// Check-in changes for PPI request that was lost in label 32...
//
// 57    10/10/09 5:11p Fredericko
//
// 56    9/15/09 6:22p Fredericko
// Changed to not use CMOS for the case when a deactivated for Enable,
// Activate and allow owner command.
//
// 55    8/19/09 1:58p Fredericko
//
// 54    8/19/09 10:54a Fredericko
// Support to measure CPU microcode in Nested firmware volume.
//
// 53    8/14/09 4:22p Fredericko
// Changed flow with Authentication and Setup Confirmation to rid of extra
// reset in the flow.
//
// 52    7/29/09 11:17a Fredericko
// 1. Create ACPI table for all ACPI NVS. including ACPI3.0
// 2. If Setup request fails full reset the platform and re-execute the
// command on next boot.
// 3. Minor Compiler problem with error checking fixed.
//
// 1     6/10/09 4:56p Fasihm
// Added fix for TCG support. Remove after TCG label is updated with
// changes generically incorporated.
//
// 51    6/02/09 4:49p Fredericko
//
// 50    6/02/09 1:12p Fredericko
//
// 49    6/01/09 4:18p Fredericko
// Changes added for TCM_SUPPORT
//
// 48    4/30/09 6:18p Fredericko
// Updated Header Date
//
// 47    4/30/09 5:36p Fredericko
// AMI company Header Address changes, Fixes when AMI_TCG_MESSAGE is
// enabled. Build and display Fixes.
//
// 46    4/13/09 4:39p Fredericko
//
// 45    4/03/09 6:14p Fredericko
// #define changes and coding standard changes
//
// 43    3/05/09 3:15p Fredericko
// Changes for CoreSources dependency
//
// 42    2/05/09 5:37p Fredericko
// Lots of changes done in relation to removing dependencies on EDK
//
// 41    1/02/09 5:36p Fredericko
// Moving Measurement of event Separators to EFI phase from legacy phase.
//
// 39    6/02/08 8:34p Fredericko
// update Setup with no hardware if TPM does not respond properly to
// commands.
//
// 38    4/10/08 6:02p Fredericko
// Mor implemenation changes. Currently supports upto 4GB.
//
// 37    4/10/08 5:31p Fredericko
// Generic Measurement changes and bug fixes
//
// 36    2/27/08 8:50p Fredericko
//
// 35    2/27/08 5:57p Fredericko
// TCG specification changes and code clean up
//
// 34    2/06/08 9:01p Fredericko
// Changes for DTM WLK 1.1 and Physical Presence Lock before booting.
//
// 33    1/18/08 8:23p Fredericko
// Generic changes for Tcg EFI measurements specification requirements
//
// 32    11/09/07 6:44p Fasihm
// Removed CONFIRM_SETUP_CHANGE around update_cmos() as it is not needed
// now.
//
// 31    10/23/07 12:36p Fredericko
// Setup PPI bug fixes
//
// 30    10/08/07 9:16a Fredericko
//
// 29    9/26/07 2:46p Fredericko
// Build in TRACE "TRACE" bugs
//
// 28    9/04/07 6:09p Fredericko
// Changes made for new compiler swtich "\W4" to work
//
// 27    9/04/07 10:22a Fredericko
// Measuring Embedded PciROM fix
//
// 26    8/09/07 2:20p Pats
// Removed unnecessary extern reference.
//
// 25    8/09/07 11:34a Pats
// Modified to support password authentication and state change
// confirmation.
//
// 24    7/13/07 2:54p Rameshraju
// Added the TPM post message and SDL tokens for the TPM key's
//
// 23    6/13/07 5:26p Fredericko
// Measuring PCI option ROM fixes
//
// 22    6/08/07 6:36p Fredericko
// New TPM feature to allow disabling and enabling TPM support.
//
// 21    5/22/07 7:24p Fredericko
//
// 20    5/22/07 3:51p Fredericko
// Added TPM feature to report TPM status and ownership in setup
//
// 19    3/23/07 3:34p Fredericko
// Display Correction for PPI request
//
// 18    3/19/07 9:07a Fredericko
// Build issue fix
//
// 17    3/14/07 5:14p Fredericko
// PPI print change and PPI bug fixes
//
// 16    3/12/07 11:45a Fredericko
// Allow execution of TCG command if Tcg_Setup_enable and
// TCG_setup_operation is requested
//
// 15    3/07/07 3:10p Fredericko
// TCG_PPI bug fixes
//
// 14    3/06/07 1:02p Fasihm
// Added the support for the TCG PPI support to the TCG module.
//
// 13    3/01/07 8:00p Fasihm
// Changes made for the new Edk in both structures and APIs.
//
// 12    12/11/06 1:56p Fasihm
// Added code for controlling with the Setup question TCG_SETUP.
//
// 11    11/15/06 11:16a Radhikav
//
// 10    11/13/06 3:47p Radhikav
//
// 9     11/03/06 6:34p Andriyn
//
// 8     11/02/06 9:59a Andriyn
// Change: new features (PPI and Setup questions) are conditional under
// SDL flag
//
// 7     10/06/06 5:16p Andriyn
//
// 6     8/22/06 1:30p Andriyn
// MOR related changes
//
// 5     8/18/06 9:02a Andriyn
// Refactor code
//
// 4     8/15/06 9:28a Andriyn
//
// 3     6/22/06 3:03p Andriyn
//
// 2     6/20/06 7:13p Andriyn
// Changes due to protocols moved to MiscFramework
//--------------------------------------------------------------------------
//*************************************************************************
//<AMI_FHDR_START>
//
// Name:  xTcgDxe.c
//
// Description: 
//  Most Tcg DXE initialization and measurements are done here
//
//<AMI_FHDR_END>
//*************************************************************************
#include <EFI.h>
#include <TcgCommon.h>
#include <AmiLib.h>
#include <token.h>

#if SMBIOS_SUPPORT == 1
  #include <SmBios.h>
#endif

#include <TcgMisc.h>
#include "TcgPrivate.h"
#include <AmiDxeLib.h>
#include <TcgPrivate.h>
#include <DiskIo.h>
#include <BlockIo.h>
#include "protocol\TcgService\TcgService.h"
#include "protocol\TpmDevice\TpmDevice.h"
#include "Protocol/CpuIo.h"
#include "Protocol/FirmwareVolume.h"
#include "Protocol/DevicePath.h"
#include "Protocol/PciIo.h"
#include "TcgPlatformSetupPolicy.h"
#include <AmiTcgPlatformProtocol.h>
#if (defined(TCGMeasureSecureBootVariables) && (TCGMeasureSecureBootVariables != 0))
#include <ImageAuthentication.h>
#endif


//------------------------------------------------------------------------
//Internal Structures
//------------------------------------------------------------------------
typedef struct _TCG_DXE_PRIVATE_DATA
{
    EFI_TCG_PROTOCOL        TcgServiceProtocol;
    EFI_TPM_DEVICE_PROTOCOL *TpmDevice;
} TCG_DXE_PRIVATE_DATA;

EFI_STATUS
__stdcall TcgDxeCommonExtend(
    IN VOID         *CallbackContext,
    IN TPM_PCRINDEX PCRIndex,
    IN TCG_DIGEST   *Digest,
    OUT TCG_DIGEST  *NewPCRValue );


#define TCG_DXE_PRIVATE_DATA_FROM_THIS( This )  \
    _CR( This, TCG_DXE_PRIVATE_DATA, TcgServiceProtocol )
//--------------------------------------------------------------------------
//--------------------------------------------------------------------------

#define   GUID_VARIABLE_DECLARATION( Variable, Guid ) extern EFI_GUID Variable

EFI_GUID                  gEfiTcgProtocolGuid = EFI_TCG_PROTOCOL_GUID;
EFI_GUID                  gDsdtGuidDxe        = DSDT_GUID;
EFI_GUID                  TcgEfiGlobalVariableGuid = TCG_EFI_GLOBAL_VARIABLE_GUID;
EFI_GUID                  AmiTcgPlatformProtocolGuid = AMI_TCG_PLATFORM_PROTOCOL_GUID;
EFI_GUID                  gEfiTcgPrivateInterfaceGuid = EFI_TCG_PRIVATE_INTERFACE_GUID;
static BOOLEAN            BootLaunchDone = FALSE;

//---------------------------------------------------------------------------
//---------------------------------------------------------------------------

#include <AcpiSupport.h>

//---------------------------------------------------------------------------
//---------------------------------------------------------------------------
EFI_STATUS EFIAPI TcgDxeHashLogExtendEvent (
    IN EFI_TCG_PROTOCOL     *This,
    IN EFI_PHYSICAL_ADDRESS HashData,
    IN UINT64               HashDataLen,
    IN TCG_ALGORITHM_ID     AlgorithmId,
    IN OUT TCG_PCR_EVENT    *TCGLogData,
    IN OUT UINT32           *evNum );

EFI_STATUS
EFIAPI
TcgMeasureGptTable (
  IN      EFI_DEVICE_PATH_PROTOCOL  *DevicePath
  );


/////////////////////////////////////////////////
#define AMI_VALID_BOOT_IMAGE_CERT_TBL_GUID \
    { 0x6683D10C, 0xCF6E, 0x4914, 0xB5, 0xB4, 0xAB, 0x8E, 0xD7, 0x37, 0x0E, 0xD7 }
//
//
// Data Table definition
//
typedef struct _AMI_VALID_CERT_IN_SIG_DB {
  UINT32          SigOffset;
  UINT32          SigLength;
} AMI_VALID_CERT_IN_SIG_DB;



//**********************************************************************
//<AMI_PHDR_START>
//
// Procedure:    AppendDevicePath
//
// Description:  Appends Two given Device Path
//
// Input:        IN     EFI_DEVICE_PATH_PROTOCOL        *Path1
//               IN     EFI_DEVICE_PATH_PROTOCOL        *Path2
//
// Output:       None
//
// Modified:
//
// Referrals:
//
// Notes:
//<AMI_PHDR_END>
//**********************************************************************
static
EFI_DEVICE_PATH_PROTOCOL* TcgAppendDevicePath(
    IN EFI_DEVICE_PATH_PROTOCOL *Path1,
    IN EFI_DEVICE_PATH_PROTOCOL *Path2 )
{
    EFI_DEVICE_PATH_PROTOCOL *NewPath;
    UINTN                    PathSize1, PathSize2;

    if ( !Path1 && !Path2 )
    {
        return NULL;
    }

    PathSize1 = DPLength( Path1 );
    PathSize2 = DPLength( Path2 );

    if ( PathSize1 && PathSize2 )
    {
        PathSize1 -= sizeof (EFI_DEVICE_PATH_PROTOCOL);
    }

    pBS->AllocatePool( EfiBootServicesData,
                       PathSize1 + PathSize2,
                       (void**)&NewPath );

    pBS->CopyMem( NewPath,                     Path1, PathSize1 );
    pBS->CopyMem( (UINT8*)NewPath + PathSize1, Path2, PathSize2 );

    return NewPath;
}



//<AMI_PHDR_START>
//----------------------------------------------------------------------------
//
// Procedure:   EfiLibAllocatePool
//
// Description: Allocate BootServicesData pool.
//
// Input:       AllocationSize  - The size to allocate
//
// Output:      Pointer of the buffer allocated.
//
//----------------------------------------------------------------------------
//<AMI_PHDR_END>

VOID *
EfiLibAllocatePool (
  IN  UINTN   AllocationSize
)
{
  VOID  *Memory;

  Memory = NULL;
  pBS->AllocatePool (EfiBootServicesData, AllocationSize, &Memory);
  return Memory;
}



//<AMI_PHDR_START>
//----------------------------------------------------------------------------
//
// Procedure:   TcgEfiLibAllocateZeroPool
//
// Description: Allocate BootServicesData pool and zero the pool.
//
// Input:       AllocationSize  - The size to allocate
//
// Output:      Pointer of the buffer allocated.
//
//----------------------------------------------------------------------------
//<AMI_PHDR_END>
VOID *
TcgEfiLibAllocateZeroPool (
  IN  UINTN   AllocationSize
  )
{
  VOID  *Memory;

  Memory = EfiLibAllocatePool (AllocationSize);
  if (Memory != NULL) {
    pBS->SetMem (Memory, AllocationSize, 0);
  }

  return Memory;
}


#if (defined(TCGMeasureSecureBootVariables) && (TCGMeasureSecureBootVariables != 0))
EFI_STATUS
MeasureCertificate(UINTN sizeOfCertificate, 
                   UINT8 *pterCertificate)
{
    EFI_STATUS   Status;
    TCG_PCR_EVENT             *TcgEvent = NULL;
    EFI_GUID                  gEfiTcgProtocolGuid = EFI_TCG_PROTOCOL_GUID;
    EFI_TCG_PROTOCOL          *tcgSvc;
    TCG_EFI_VARIABLE_DATA     *VarLog;
    EFI_PHYSICAL_ADDRESS      Last;
    UINT32                    evNum;
    BOOLEAN                   AlreadyMeasuredCert = FALSE;
    UINTN                     i=0;
    UINTN                     VarNameLength;
    static BOOLEAN            initialized = 0;
    static TPM_DIGEST         digestTrackingArray[10];
    static TPM_DIGEST         zeroDigest;
    UINT8                     *tempDigest = NULL;
    UINT64                    HashedDataLen = 20; 

    if(!initialized)
    {
        for(i=0;i<5; i++)
        {
            MemSet(digestTrackingArray[i].digest,20,0);
        }
        MemSet(zeroDigest.digest,20,0);
        initialized = TRUE;
    }

    Status = pBS->LocateProtocol(&gEfiTcgProtocolGuid,
                                     NULL, &tcgSvc );

    if(EFI_ERROR(Status))return Status;

    VarNameLength = Wcslen(L"db");
    Status = pBS->AllocatePool( EfiBootServicesData,
               _TPM_STRUCT_PARTIAL_SIZE( TCG_PCR_EVENT,Event ) 
                + (UINT32)(sizeof(TCG_EFI_VARIABLE_DATA) + (VarNameLength 
                * sizeof(CHAR16)) + sizeOfCertificate - 3),
                &TcgEvent);
    
    if(EFI_ERROR(Status))return Status;
        
    TcgEvent->PCRIndex  = 7;
    TcgEvent->EventType = 0x800000E0;

    TcgEvent->EventSize = (UINT32)( sizeof (*VarLog) + VarNameLength 
                              * sizeof (CHAR16) + sizeOfCertificate) - 3;

    pBS->AllocatePool( EfiBootServicesData, TcgEvent->EventSize, &VarLog );

    if ( VarLog == NULL ){
        return EFI_OUT_OF_RESOURCES;
    }
        
    VarLog->VariableName       = gEfiImageSecurityDatabaseGuid;
    VarLog->UnicodeNameLength  = VarNameLength;
    VarLog->VariableDataLength = sizeOfCertificate;

    pBS->CopyMem((CHAR16*)(VarLog->UnicodeName),
                L"db",
                VarNameLength * sizeof (CHAR16));
   
    pBS->CopyMem((CHAR16*)(VarLog->UnicodeName) + VarNameLength,
                     pterCertificate,
                     sizeOfCertificate);

    pBS->CopyMem( TcgEvent->Event,
                  VarLog,
                  TcgEvent->EventSize );

    //before extending verify if we have already measured it.
    tcgSvc->HashAll(tcgSvc,
        (UINT8 *)VarLog,
        TcgEvent->EventSize,
        4,
        &HashedDataLen,
        &tempDigest);

    for(i=0; i<10; i++)
    {
        //tempDigest
        if(!MemCmp(digestTrackingArray[i].digest, tempDigest, 20))
        return EFI_SUCCESS; //already measured

        if(!MemCmp(digestTrackingArray[i].digest, zeroDigest.digest, 20))
        break; //we need to measure
    }

    pBS->CopyMem(digestTrackingArray[i].digest, tempDigest, 20);

    Status = tcgSvc->HashLogExtendEvent(tcgSvc,
                            (EFI_PHYSICAL_ADDRESS)VarLog,
                            TcgEvent->EventSize,
                            4,
                            TcgEvent,
                            &evNum,
                            &Last );

    pBS->FreePool(TcgEvent);

    return Status;
}


EFI_STATUS FindandMeasureSecureBootCertificate(BOOLEAN  BootPolicy)
{
    EFI_STATUS      Status;
    UINTN           VarSize  = 0;
    UINTN           i=0;
    UINT8           *SecureDBBuffer = NULL;
    UINT8           *CertificateBuffer = NULL;
    UINTN           SizeofCertificate = 0;
    EFI_GUID        Certificateguid = AMI_VALID_BOOT_IMAGE_CERT_TBL_GUID;
    AMI_VALID_CERT_IN_SIG_DB    *CertInfo;
    UINT8           *CertOffsetPtr = NULL;
    static BOOLEAN  NullKeysMeasured = FALSE;

    
    if(BootPolicy == FALSE && BootLaunchDone == FALSE) return EFI_SUCCESS;
    if(NullKeysMeasured == TRUE)return EFI_SUCCESS;
  
    if(BootPolicy == TRUE && BootLaunchDone == FALSE)
    {
        Status   = pRS->GetVariable(L"db",
                        &gEfiImageSecurityDatabaseGuid,
                        NULL,
                        &VarSize,
                        NULL);

        if ( Status == EFI_BUFFER_TOO_SMALL )
        {
            pBS->AllocatePool( EfiBootServicesData, VarSize, &SecureDBBuffer );
            
            if ( SecureDBBuffer != NULL )
            {
                Status = pRS->GetVariable(L"db",
                                &gEfiImageSecurityDatabaseGuid,
                                NULL,
                                &VarSize,
                                SecureDBBuffer);

                if ( EFI_ERROR( Status ))
                {
                    pBS->FreePool( SecureDBBuffer  );
                    SecureDBBuffer = NULL;
#if (defined(UnconfiguredSecureBootVariables) && (UnconfiguredSecureBootVariables == 0))
                    return EFI_NOT_FOUND;
#endif
                }
            }

        }else{
#if (defined(UnconfiguredSecureBootVariables) && (UnconfiguredSecureBootVariables == 0))
          return EFI_NOT_FOUND;
#else
          SecureDBBuffer = NULL;
#endif
        }
    }

    //we need to find the pointer in the EFI system table and work from 
    //there
    CertInfo = NULL;
    CertInfo = GetEfiConfigurationTable(pST, &Certificateguid);
    if(CertInfo == NULL){
     TRACE(( TRACE_ALWAYS,"db variable found SecCertificate Information not found in EFI System Table \n"));
    }
    if(CertInfo->SigLength == 0){
     TRACE(( TRACE_ALWAYS,"SecCertificate Information found in EST but Information might be invalid \n"));
    }

    CertOffsetPtr = NULL;

    if(CertInfo!=0)
    {
        CertOffsetPtr = (SecureDBBuffer + CertInfo->SigOffset);
        SizeofCertificate = (UINTN)CertInfo->SigLength;
    }else{
        SizeofCertificate = 0;
    }

    if(SizeofCertificate == 0){
        NullKeysMeasured = TRUE;
    }

    MeasureCertificate(SizeofCertificate,CertOffsetPtr);
    
    if(SecureDBBuffer!=NULL){
        pBS->FreePool( SecureDBBuffer  );
    }
    
    return Status;
}
#endif




//--------------------------------------------------------------------------------------------
//Description:  Measure a PE/COFF image into PCR 2 or 4 depending on Boot policy of 0 or 1
//Arguments:
// 	BootPolicy  - Boolean value of 0 or 1 for PCR index 2 or 4.
//  ImageContext - Contains details about the image.
//  LinkTimeBase - Linking time Image Address
//  ImageType    - EFI_IMAGE_SUBSYSTEM_EFI_APPLICATION, BOOT_SERVICE_DRIVER, EFI_RUNTIME_DRIVER
//  DeviceHandle - Device identification handle
//  FilePath     - Device File path
//Output:  EFI_SUCCESS - Image Measured successfully.
//---------------------------------------------------------------------------------------------

EFI_STATUS
EFIAPI
TcgMeasurePeImage (
  IN      BOOLEAN                   BootPolicy,
  IN      EFI_PHYSICAL_ADDRESS      ImageAddress,
  IN      UINTN                     ImageSize,
  IN      UINTN                     LinkTimeBase,
  IN      UINT16                    ImageType,
  IN      EFI_HANDLE                DeviceHandle,
  IN      EFI_DEVICE_PATH_PROTOCOL  *FilePath
  )
{

  EFI_STATUS                        Status;
  TCG_PCR_EVENT_HDR                 TcgEvent;
  TCG_PCR_EVENT                     *TcgEventlog = NULL;
  EFI_IMAGE_LOAD_EVENT              *ImageLoad;
  EFI_DEVICE_PATH_PROTOCOL          *DevicePath;
  EFI_DEVICE_PATH_PROTOCOL          *FullPath;
  UINT32                            FullPathSize;
  SHA1_CTX                          Sha1Ctx;
  TCG_EFI_IMAGE_DOS_HEADER              *DosHdr;
  UINT32                            PeCoffHeaderOffset;
  TCG_EFI_IMAGE_NT_HEADERS          *Hdr;
  TCG_EFI_IMAGE_SECTION_HEADER      *Section;
  UINT8                             *HashBase;
  UINTN                             HashSize;
  UINTN                             SumOfBytesHashed;
  TCG_EFI_IMAGE_SECTION_HEADER      *SectionHeader;
  UINTN                             Index, iPos;
  EFI_TCG_PROTOCOL			        *TcgProtocol;
  EFI_TPM_DEVICE_PROTOCOL			*TpmProtocol;
  UINT32							EventNumber;
  TCG_DIGEST                        *Sha1Digest = NULL;
      
  ImageLoad     = NULL;
  FullPath      = NULL;
  SectionHeader = NULL;
  FullPathSize  = 0;

  if(AutoSupportType()){
    return EFI_SUCCESS;  
  }
    
  Status = pBS->LocateProtocol (&gEfiTcgProtocolGuid,  NULL, &TcgProtocol);
  if (EFI_ERROR (Status)) {
      return Status;
   }

  Status = pBS->LocateProtocol (&gEfiTpmDeviceProtocolGuid,  NULL, &TpmProtocol );
  if (EFI_ERROR (Status)) {
      return Status;
   }



  if (DeviceHandle != NULL) {
    //
    // Skip images loaded from FVs
    //
    Status = pBS->OpenProtocol (
                    DeviceHandle,
                    &gEfiFirmwareVolumeProtocolGuid,
                    NULL,
                    NULL,
                    NULL,
                    EFI_OPEN_PROTOCOL_TEST_PROTOCOL
                    );
    if (!EFI_ERROR (Status)) {
      goto Done;
    }
    ASSERT (Status == EFI_UNSUPPORTED);

    //
    // Get device path for the device handle
    //
    Status = pBS->HandleProtocol (
                    DeviceHandle,
                    &gEfiDevicePathProtocolGuid,
                    &DevicePath
                    );
    if (EFI_ERROR (Status)) {
      goto Done;
    }
                   
    FullPath     = TcgAppendDevicePath (DevicePath, FilePath);
    FullPathSize = (UINT32)DPLength (FullPath);
  }

    //Allocate Event log memory
    Status = pBS->AllocatePool( EfiBootServicesData,
                             _TPM_STRUCT_PARTIAL_SIZE( TCG_PCR_EVENT, Event )
                             + ((sizeof (*ImageLoad)
                             - sizeof (ImageLoad->DevicePath)) + FullPathSize),
                             &TcgEventlog );
  //
  // Determine destination PCR by BootPolicy
  //
  TcgEvent.PCRIndex   = BootPolicy ? 4 : 2;
  TcgEvent.EventSize  = sizeof (*ImageLoad) - sizeof (ImageLoad->DevicePath);
  TcgEvent.EventSize += FullPathSize;

  switch (ImageType) {
    case EFI_IMAGE_SUBSYSTEM_EFI_APPLICATION:
      TcgEvent.EventType = EV_EFI_BOOT_SERVICES_APPLICATION;
      break;
    case EFI_IMAGE_SUBSYSTEM_EFI_BOOT_SERVICE_DRIVER:
      TcgEvent.EventType = EV_EFI_BOOT_SERVICES_DRIVER;
      break;
    case EFI_IMAGE_SUBSYSTEM_EFI_RUNTIME_DRIVER:
      TcgEvent.EventType = EV_EFI_RUNTIME_SERVICES_DRIVER;
      break;
    default:
            TRACE(( TRACE_ALWAYS,
                __FUNCTION__ ": Unknown subsystem type %d",
                ImageType));

      ASSERT (FALSE);
      TcgEvent.EventType = ImageType;
      Status = EFI_UNSUPPORTED;
      goto Done;
  }

  //do measure images from ROM that call LoadImage themselves
  // without the correct Devicepath
  if(ImageType == EFI_IMAGE_SUBSYSTEM_EFI_BOOT_SERVICE_DRIVER 
                    && BootLaunchDone == FALSE){
      return EFI_SUCCESS;
  }
        

   PERF_START(0,L"MeasurePeImg",NULL,0);

    Status = pBS->AllocatePool( EfiBootServicesData,
                                TcgEvent.EventSize,
                                &ImageLoad );

  if (ImageLoad == NULL) {
    Status = EFI_OUT_OF_RESOURCES;
    goto Done;
  }

  ImageLoad->ImageLocationInMemory = ImageAddress;
  ImageLoad->ImageLengthInMemory   = ImageSize;
  ImageLoad->ImageLinkTimeAddress  = LinkTimeBase;
  ImageLoad->LengthOfDevicePath    = FullPathSize;
    pBS->CopyMem( ImageLoad->DevicePath, FullPath,  FullPathSize );

  //
  // Check PE/COFF image
  //
  DosHdr = (TCG_EFI_IMAGE_DOS_HEADER *)(UINTN)ImageAddress;
  PeCoffHeaderOffset = 0;
  if (DosHdr->e_magic == TCG_EFI_IMAGE_DOS_SIGNATURE) {
    PeCoffHeaderOffset = DosHdr->e_lfanew;
  }
  if (((TCG_EFI_TE_IMAGE_HEADER *)((UINT8 *)(UINTN)ImageAddress + PeCoffHeaderOffset))->Signature 
       == TCG_EFI_TE_IMAGE_HEADER_SIGNATURE) {
    goto Done;
  }

  //
  // PE/COFF Image Measurement
  //
  //    NOTE: The following codes/steps are based upon the authenticode image hashing in 
  //      PE/COFF Specification 8.0 Appendix A.
  //      
  //

  // 1.	Load the image header into memory.
  
  // 2.	Initialize a SHA hash context.
//  Status = SHA1_init(TcgProtocol, &Sha1Ctx);
    SHA1Init(&Sha1Ctx );

  //
  // Measuring PE/COFF Image Header; 
  // But CheckSum field and SECURITY data directory (certificate) are excluded
  //
  Hdr   = (TCG_EFI_IMAGE_NT_HEADERS *)((UINT8 *)(UINTN)ImageAddress + PeCoffHeaderOffset);

  //
  // 3.	Calculate the distance from the base of the image header to the image checksum address.
  // 4.	Hash the image header from its base to beginning of the image checksum.
  //
  HashBase = (UINT8 *)(UINTN)ImageAddress;
  HashSize = (UINTN) ((UINT8 *)(&Hdr->OptionalHeader.CheckSum) - HashBase);
  
/*Status   = SHA1_update(TcgProtocol,
               &Sha1Ctx,
               HashBase,
               HashSize
               );
*/
  SHA1Update(&Sha1Ctx, HashBase, (u32)HashSize );

  //
  // 5.	Skip over the image checksum (it occupies a single ULONG).
  // 6.	Get the address of the beginning of the Cert Directory.
  // 7.	Hash everything from the end of the checksum to the start of the Cert Directory.
  //
  HashBase = (UINT8 *) &Hdr->OptionalHeader.CheckSum + sizeof (UINT32);
  HashSize = (UINTN) ((UINT8 *)(&Hdr->OptionalHeader.DataDirectory[TCG_EFI_IMAGE_DIRECTORY_ENTRY_SECURITY]) - HashBase);

/*  Status   = SHA1_update(TcgProtocol,
               &Sha1Ctx,
               HashBase,
               HashSize
               );  
*/
    SHA1Update(&Sha1Ctx, HashBase, (u32)HashSize );

  //
  // 8.	Skip over the Cert Directory. (It is sizeof(IMAGE_DATA_DIRECTORY) bytes.)
  // 9.	Hash everything from the end of the Cert Directory to the end of image header.
  //
  HashBase = (UINT8 *) &Hdr->OptionalHeader.DataDirectory[TCG_EFI_IMAGE_DIRECTORY_ENTRY_SECURITY + 1];
  HashSize = Hdr->OptionalHeader.SizeOfHeaders - 
             (UINTN) ((UINT8 *)(&Hdr->OptionalHeader.DataDirectory[TCG_EFI_IMAGE_DIRECTORY_ENTRY_SECURITY + 1]) - (UINT8 *)(UINTN)ImageAddress);

/*  Status   = SHA1_update(TcgProtocol,
               &Sha1Ctx,
               HashBase,
               HashSize
               );
*/
  SHA1Update(&Sha1Ctx, HashBase, (u32)HashSize );

  //
  // 10. Set the SUM_OF_BYTES_HASHED to the size of the header 
  //
  SumOfBytesHashed = Hdr->OptionalHeader.SizeOfHeaders;

  //
  // 11. Build a temporary table of pointers to all the IMAGE_SECTION_HEADER 
  //     structures in the image. The 'NumberOfSections' field of the image 
  //     header indicates how big the table should be. Do not include any 
  //     IMAGE_SECTION_HEADERs in the table whose 'SizeOfRawData' field is zero.   
  //

   Status = pBS->AllocatePool (EfiBootServicesData, sizeof (TCG_EFI_IMAGE_SECTION_HEADER) * Hdr->FileHeader.NumberOfSections, &SectionHeader);
   if(SectionHeader==NULL)return EFI_OUT_OF_RESOURCES;
   pBS->SetMem (SectionHeader, sizeof (TCG_EFI_IMAGE_SECTION_HEADER) * Hdr->FileHeader.NumberOfSections , 0);

  //
  // 12.	Using the 'PointerToRawData' in the referenced section headers as 
  //      a key, arrange the elements in the table in ascending order. In other 
  //      words, sort the section headers according to the disk-file offset of 
  //      the section.
  //
  Section = (TCG_EFI_IMAGE_SECTION_HEADER *) (
               (UINT8 *)(UINTN)ImageAddress +
               PeCoffHeaderOffset +
               sizeof(UINT32) + 
               sizeof(TCG_EFI_IMAGE_FILE_HEADER) + 
               Hdr->FileHeader.SizeOfOptionalHeader
               );  
  for (Index = 0; Index < Hdr->FileHeader.NumberOfSections; Index++) {
    iPos = Index;
    while ((iPos > 0) && (Section->PointerToRawData < SectionHeader[iPos - 1].PointerToRawData)) {
      MemCpy (&SectionHeader[iPos], &SectionHeader[iPos - 1], sizeof(TCG_EFI_IMAGE_SECTION_HEADER));
      iPos--;
    }
            MemCpy( &SectionHeader[iPos], Section,
                    sizeof(TCG_EFI_IMAGE_SECTION_HEADER));
    Section += 1;    
  }
  
  //
  // 13.	Walk through the sorted table, bring the corresponding section 
  //      into memory, and hash the entire section (using the 'SizeOfRawData' 
  //      field in the section header to determine the amount of data to hash).
  // 14.	Add the section's 'SizeOfRawData' to SUM_OF_BYTES_HASHED .
  // 15.	Repeat steps 13 and 14 for all the sections in the sorted table.
  //
  for (Index = 0; Index < Hdr->FileHeader.NumberOfSections; Index++) {
    Section  = (TCG_EFI_IMAGE_SECTION_HEADER *) &SectionHeader[Index];
    if (Section->SizeOfRawData == 0) {
      continue;
    }
    HashBase = (UINT8 *)(UINTN)ImageAddress + Section->PointerToRawData;
    HashSize = (UINTN) Section->SizeOfRawData;
/*
    Status   = SHA1_update(TcgProtocol,
               &Sha1Ctx,
               HashBase,
               HashSize
               );
*/
    SHA1Update(&Sha1Ctx, HashBase, (u32)HashSize );

    SumOfBytesHashed += HashSize;
  }    

  //
  // 16.	If the file size is greater than SUM_OF_BYTES_HASHED, there is extra
  //      data in the file that needs to be added to the hash. This data begins 
  //      at file offset SUM_OF_BYTES_HASHED and its length is:
  //             FileSize  -  (CertDirectory->Size)
  //
  if (ImageSize > SumOfBytesHashed) {
    HashBase = (UINT8 *)(UINTN)ImageAddress + SumOfBytesHashed;
    HashSize = (UINTN)(ImageSize -
               Hdr->OptionalHeader.DataDirectory[TCG_EFI_IMAGE_DIRECTORY_ENTRY_SECURITY].Size -
               SumOfBytesHashed);
/*
    Status   = SHA1_update(TcgProtocol,
               		&Sha1Ctx,
               		HashBase,
               		HashSize
               	   );
*/
    SHA1Update(&Sha1Ctx, HashBase, (u32)HashSize );
  }

  //
  // 17.	Finalize the SHA hash.
  //
//  Status = SHA1_final(TcgProtocol, &Sha1Ctx, &Sha1Digest);
  SHA1Final((unsigned char *)&Sha1Digest->digest, &Sha1Ctx);

  pBS->CopyMem (&TcgEvent.Digest.digest,Sha1Digest->digest, sizeof (TcgEvent.Digest.digest));

  //
  // HashLogExtendEvent 
  //
  
  //hash has been generated so extend it
  TpmProtocol->Init(TpmProtocol);

  Status = TcgDxeCommonExtend (
			 (void *)TcgProtocol,
			 TcgEvent.PCRIndex,
			 &TcgEvent.Digest,
              Sha1Digest
			);

  TpmProtocol->Close(TpmProtocol);

  if (!EFI_ERROR (Status)) {  

 //Now log the event
    TcgEventlog->PCRIndex  = TcgEvent.PCRIndex;
    TcgEventlog->EventType = TcgEvent.EventType;
    TcgEventlog->EventSize = TcgEvent.EventSize;
    MemCpy(&TcgEventlog->Digest, &TcgEvent.Digest, sizeof(TCG_DIGEST));
    MemCpy(&TcgEventlog->Event, ImageLoad, TcgEvent.EventSize);
    Status = TcgProtocol->LogEvent(TcgProtocol, TcgEventlog, &EventNumber,0x01);
  }

  PERF_END(0,L"MeasurePeImg",NULL,0);

  if(BootPolicy == TRUE && BootLaunchDone == FALSE){
    PERF_START(0,L"MeasureGpt",NULL,0);
    TcgMeasureGptTable(FullPath);
    PERF_END(0,L"MeasureGpt",NULL,0);
  }

#if (defined(TCGMeasureSecureBootVariables) && (TCGMeasureSecureBootVariables != 0))
  FindandMeasureSecureBootCertificate(BootPolicy);
#endif

  if(BootPolicy == TRUE && BootLaunchDone == FALSE){
    BootLaunchDone = TRUE;
  }

  TpmProtocol->Close(TpmProtocol);

Done:
  if (ImageLoad != NULL) {
    pBS->FreePool (ImageLoad);
  }

  if (TcgEventlog != NULL )
  {
    pBS->FreePool( TcgEventlog );
  }
  if (FullPathSize > 0) {
    pBS->FreePool (FullPath);
  }
  if (SectionHeader != NULL) {
    pBS->FreePool (SectionHeader);
  }
  return Status;
}






EFI_STATUS
EFIAPI
GptDevicePathToHandle (
  IN     EFI_DEVICE_PATH_PROTOCOL   *DevicePath,
     OUT EFI_HANDLE                 *GptHandle
  )
{
  EFI_STATUS                         Status;
  EFI_DEVICE_PATH_PROTOCOL           *DevicePathNode;
  EFI_DEVICE_PATH_PROTOCOL           *NewDevicePathNode;
  EFI_DEVICE_PATH_PROTOCOL           *PreDevicePathNode;
  HARDDRIVE_DEVICE_PATH              *HdDevicePath;
  EFI_HANDLE                         Handle;
  BOOLEAN                            GptDiskFound;
 
  NewDevicePathNode = TcgEfiLibAllocateZeroPool (DPLength (DevicePath));
  MemCpy (NewDevicePathNode, DevicePath, DPLength (DevicePath));
  DevicePathNode = NewDevicePathNode;

  //
  // The device should support blockIO protocol. Check it.
  //
  Status = pBS->LocateDevicePath (&gEfiBlockIoProtocolGuid, &DevicePathNode, &Handle);
  if (EFI_ERROR (Status)) {
    pBS->FreePool (NewDevicePathNode);
    return EFI_UNSUPPORTED;
  }  
  //
  // Find the gpt partion on the given devicepath, if not, return.
  //
  GptDiskFound      = FALSE;
  PreDevicePathNode = NULL;
  HdDevicePath      = NULL;
  DevicePathNode    = NewDevicePathNode;
  while (!IsDevicePathEnd (DevicePathNode)) {
    //
    // Find the Gpt partition
    //
    if (DevicePathType (DevicePathNode) == MEDIA_DEVICE_PATH &&
          DevicePathSubType (DevicePathNode) == MEDIA_HARDDRIVE_DP) {
      HdDevicePath = (HARDDRIVE_DEVICE_PATH *) DevicePathNode;
      //
      // Check whether it is a gpt partition or not
      //                           
      if (PreDevicePathNode != NULL &&
            HdDevicePath->MBRType == MBR_TYPE_EFI_PARTITION_TABLE_HEADER && 
            HdDevicePath->SignatureType == SIGNATURE_TYPE_GUID) {
        GptDiskFound = TRUE;
        break;    
      }
    }
    PreDevicePathNode = DevicePathNode;
    DevicePathNode    = NextDevicePathNode (DevicePathNode);
  }
  if (!GptDiskFound) {
    pBS->FreePool (NewDevicePathNode);
    return EFI_UNSUPPORTED; 
  }
  
  //
  // Change the device path to the parent device path and get the handle.
  //
  DevicePathNode->Type    = 0xFF;
  DevicePathNode->SubType = 0xFF;
  DevicePathNode          = NewDevicePathNode;
  Status = pBS->LocateDevicePath (
                  &gEfiDiskIoProtocolGuid,
                  &DevicePathNode,
                  &Handle
                  );
  if (EFI_ERROR (Status)) {
    pBS->FreePool (NewDevicePathNode);
    return Status;
  }
  *GptHandle = Handle;
  pBS->FreePool (NewDevicePathNode);
  return EFI_SUCCESS;
}




EFI_DEVICE_PATH_PROTOCOL *
HandleBootDevicePath(
    EFI_DEVICE_PATH_PROTOCOL *DevicePath
)
{
    EFI_STATUS	    Status;
    EFI_HANDLE	    *Handle;
    UINTN		    Count, i;
    EFI_DEVICE_PATH_PROTOCOL *FullDevicePath=NULL;
    HARDDRIVE_DEVICE_PATH    *BootParitionDevicePath  = (HARDDRIVE_DEVICE_PATH*)DevicePath;

    Status = pBS->LocateHandleBuffer(ByProtocol,&gEfiBlockIoProtocolGuid,NULL,&Count,&Handle);
    if (EFI_ERROR(Status)) return NULL;

    for( i=0; i<Count; i++ )
    {
        EFI_BLOCK_IO_PROTOCOL		*BlockIo;
        EFI_DEVICE_PATH_PROTOCOL	*PartitionDevicePath, *TmpDevicePath;
        HARDDRIVE_DEVICE_PATH*		PartitionNode;

        Status = pBS->HandleProtocol(Handle[i],&gEfiBlockIoProtocolGuid,&BlockIo);
        if (EFI_ERROR(Status))
			continue;

        // if this is not partition, continue
        if (!BlockIo->Media->LogicalPartition)
			continue;

		Status = pBS->HandleProtocol(Handle[i],&gEfiDevicePathProtocolGuid,&PartitionDevicePath);
        if (EFI_ERROR(Status))
			continue;

        // Get last node of the device path. It should be partition node
        PartitionNode = (HARDDRIVE_DEVICE_PATH*)PartitionDevicePath;

        for( TmpDevicePath = PartitionDevicePath;
             !IsDevicePathEndType(TmpDevicePath);
             TmpDevicePath=NextDevicePathNode(TmpDevicePath) )
		{
			PartitionNode = (HARDDRIVE_DEVICE_PATH*)TmpDevicePath;
		}

        //Check if our partition matches Boot partition
        if (PartitionNode->Header.Type!=MEDIA_DEVICE_PATH || PartitionNode->Header.SubType!=MEDIA_HARDDRIVE_DP)
			continue;

        if ( PartitionNode->PartitionNumber==BootParitionDevicePath->PartitionNumber &&
             PartitionNode->SignatureType==BootParitionDevicePath->SignatureType &&
             !MemCmp(PartitionNode->Signature,BootParitionDevicePath->Signature,16) )
        {
            //Match found
            FullDevicePath = TcgAppendDevicePath(PartitionDevicePath,NextDevicePathNode(DevicePath));
            break;
        }
    }

    pBS->FreePool(Handle);
    return FullDevicePath;
}


EFI_STATUS
EFIAPI
TcgMeasureGptTable (
  IN      EFI_DEVICE_PATH_PROTOCOL  *DevicePath
  )
{
 
  EFI_STATUS                        Status;
  EFI_BLOCK_IO_PROTOCOL             *BlockIo;
  EFI_DISK_IO_PROTOCOL              *DiskIo;
  TCG_EFI_PARTITION_TABLE_HEADER    *PrimaryHeader;
  TCG_EFI_PARTITION_ENTRY           *PartitionEntry;
  UINT8                             *EntryPtr;
  UINTN                             NumberOfPartition;
  UINT32                            Index;
  TCG_PCR_EVENT                     *TcgEvent;
  TCG_EFI_GPT_DATA                  *GptData;  
  EFI_GUID                          NullGuid = EFI_NULL_GUID;
  EFI_HANDLE                        Handle;
  EFI_TCG_PROTOCOL			        *TcgProtocol;
  EFI_TPM_DEVICE_PROTOCOL			*TpmProtocol;
  UINT32                            evNum;
  EFI_PHYSICAL_ADDRESS              Last;
  UINTN                             GptIndex;

  if(AutoSupportType()){
    return EFI_SUCCESS;
  }

  Status = GptDevicePathToHandle (DevicePath, &Handle);
  if (EFI_ERROR (Status)) {
    return EFI_UNSUPPORTED;
  }

  Status = pBS->HandleProtocol (Handle, &gEfiBlockIoProtocolGuid, &BlockIo);
  if (EFI_ERROR (Status)) {
    return EFI_UNSUPPORTED;
  }

  Status = pBS->HandleProtocol (Handle, &gEfiDiskIoProtocolGuid, &DiskIo);

  Status = pBS->LocateProtocol (&gEfiTcgProtocolGuid,  NULL, &TcgProtocol);
  if (EFI_ERROR (Status)) {
      return Status;
   }

  Status = pBS->LocateProtocol (&gEfiTpmDeviceProtocolGuid,  NULL, &TpmProtocol );
  if (EFI_ERROR (Status)) {
      return Status;
   }


  //
  // Read the EFI Partition Table Header
  //  

  Status = pBS->AllocatePool( EfiBootServicesData,
                              BlockIo->Media->BlockSize,
                             &PrimaryHeader );

  if (PrimaryHeader == NULL) {
    return EFI_OUT_OF_RESOURCES;
  }  

  Status = DiskIo->ReadDisk (
                     DiskIo,
                     BlockIo->Media->MediaId,
                     1 * BlockIo->Media->BlockSize,
                     BlockIo->Media->BlockSize,
                     (UINT8 *)PrimaryHeader
                     );

  if (EFI_ERROR (Status)) {
    TRACE ((TRACE_ALWAYS, "Failed to Read Partition Table Header!\n"));
    pBS->FreePool (PrimaryHeader);
    return EFI_DEVICE_ERROR;
  }  
  //
  // Read the partition entry.
  //
  Status = pBS->AllocatePool( EfiBootServicesData,
                              PrimaryHeader->NumberOfPartitionEntries * PrimaryHeader->SizeOfPartitionEntry,
                              &EntryPtr );

  if (EntryPtr == NULL) {
    pBS->FreePool (PrimaryHeader);
    return EFI_OUT_OF_RESOURCES;
  }

  Status = DiskIo->ReadDisk (
                     DiskIo,
                     BlockIo->Media->MediaId,
                     Mul64(PrimaryHeader->PartitionEntryLba, BlockIo->Media->BlockSize),
                     PrimaryHeader->NumberOfPartitionEntries * PrimaryHeader->SizeOfPartitionEntry,
                     EntryPtr);

  if (EFI_ERROR (Status)) {
    pBS->FreePool (PrimaryHeader);
    pBS->FreePool (EntryPtr);
    return EFI_DEVICE_ERROR;
  }

  
  //
  // Count the valid partition
  //
  PartitionEntry    = (TCG_EFI_PARTITION_ENTRY *)EntryPtr;
  NumberOfPartition = 0;
  for (Index = 0; Index < PrimaryHeader->NumberOfPartitionEntries; Index++) {
    if (MemCmp(&PartitionEntry->PartitionTypeGuid, &NullGuid, sizeof(EFI_GUID))) {
      NumberOfPartition++;  
    }
    PartitionEntry++;
  }   
  //
  // Parepare Data for Measurement
  //  

  //allocate memory for TCG event
  Status = pBS->AllocatePool( EfiBootServicesData,
                              sizeof(TCG_PCR_EVENT_HDR) + \
                             (UINT32)(sizeof (TCG_EFI_PARTITION_TABLE_HEADER) + sizeof(UINTN)\
                             + (NumberOfPartition * PrimaryHeader->SizeOfPartitionEntry)),
                             &TcgEvent );

  TcgEvent->PCRIndex   = 5;
  TcgEvent->EventType  = EV_EFI_GPT_EVENT;
  TcgEvent->EventSize  =  (UINT32)(sizeof (TCG_EFI_PARTITION_TABLE_HEADER) + sizeof(UINTN)\
                             + (NumberOfPartition * PrimaryHeader->SizeOfPartitionEntry));


  Status = pBS->AllocatePool( EfiBootServicesData,
                              TcgEvent->EventSize,
                              &GptData );
  if (GptData == NULL) {
    pBS->FreePool (PrimaryHeader);
    pBS->FreePool (EntryPtr);
    return EFI_OUT_OF_RESOURCES;
  }  

  MemSet(GptData, TcgEvent->EventSize, 0);
  //
  // Copy the EFI_PARTITION_TABLE_HEADER and NumberOfPartition
  //  
  MemCpy ((UINT8 *)GptData, (UINT8*)PrimaryHeader, sizeof (TCG_EFI_PARTITION_TABLE_HEADER));
  GptData->NumberOfPartitions = NumberOfPartition;
  //
  // Copy the valid partition entry
  //

  PartitionEntry = (TCG_EFI_PARTITION_ENTRY*)EntryPtr;
  GptIndex = 0;
  for (Index = 0; Index < PrimaryHeader->NumberOfPartitionEntries; Index++) {
    if (MemCmp (&PartitionEntry->PartitionTypeGuid, &NullGuid, sizeof(EFI_GUID))) {
      MemCpy (
        (UINT8 *)&GptData->Partitions + (GptIndex * sizeof (TCG_EFI_PARTITION_ENTRY)),
        (UINT8 *)PartitionEntry,
        sizeof (TCG_EFI_PARTITION_ENTRY)
        );
        GptIndex+=1;
    }
    PartitionEntry++;
  }
  //
  // Measure the GPT data
  // 

  pBS->CopyMem (TcgEvent->Event,
        		GptData,
        		TcgEvent->EventSize);

  TpmProtocol ->Init( TpmProtocol );

  Status = TcgProtocol->HashLogExtendEvent(
        TcgProtocol,
        (EFI_PHYSICAL_ADDRESS)GptData,
        TcgEvent->EventSize,
        TCG_ALG_SHA,
        TcgEvent,
        &evNum,
        &Last);


  TpmProtocol ->Close( TpmProtocol );

  pBS->FreePool (PrimaryHeader);
  pBS->FreePool (EntryPtr);
  pBS->FreePool (TcgEvent);
  pBS->FreePool (GptData);

  TRACE(( TRACE_ALWAYS,"GPT_EXIT"));
  return Status;
}



EFI_STATUS
TcgMeasureAction(
  IN      CHAR8				*String
  )
{

  TCG_PCR_EVENT		                *TcgEvent = NULL;
  EFI_PHYSICAL_ADDRESS				Last;
  EFI_TCG_PROTOCOL					*tcgSvc;
  UINT32							evNum;
  UINT32							Len;
  EFI_STATUS						Status;


  Status = pBS->LocateProtocol (
				&gEfiTcgProtocolGuid,
				NULL,
				&tcgSvc);

  ASSERT(!EFI_ERROR(Status));

  Len = (UINT32)Strlen(String);
  Status = pBS->AllocatePool (EfiBootServicesData,
        							_TPM_STRUCT_PARTIAL_SIZE (TCG_PCR_EVENT, Event) + 
        							Len,
        							&TcgEvent);

  ASSERT(!EFI_ERROR(Status));

  TcgEvent->PCRIndex 	= 5;
  TcgEvent->EventType 	= EV_EFI_ACTION;
  TcgEvent->EventSize 	= Len;

  pBS->CopyMem (TcgEvent->Event,
        		String,
        		Len);

   Status = tcgSvc->HashLogExtendEvent (
				tcgSvc,
				(EFI_PHYSICAL_ADDRESS)String,
				TcgEvent->EventSize,
				TCG_ALG_SHA,
				TcgEvent,
				&evNum,
				&Last);

  if(TcgEvent!=NULL)
  {
		pBS->FreePool (TcgEvent);
  }

  return Status;
}

UINT8 GetPlatformSupportType()
{
   return (AutoSupportType());
}


static EFI_TCG_PLATFORM_PROTOCOL  mTcgPlatformProtocol = {
  TcgMeasurePeImage,
  TcgMeasureAction,
  TcgMeasureGptTable
};


static AMI_TCG_PLATFORM_PROTOCOL  mAmiTcgPlatformProtocol = {
  GetPlatformSupportType
};


EFI_STATUS EFIAPI TcmDxeEntry (
    IN EFI_HANDLE       ImageHandle,
    IN EFI_SYSTEM_TABLE *SystemTable);

TpmDxeEntry(
    IN EFI_HANDLE ImageHandle,
    IN EFI_SYSTEM_TABLE          * SystemTable);



EFI_STATUS
EFIAPI TcgDxeEntry (
    IN EFI_HANDLE       ImageHandle,
    IN EFI_SYSTEM_TABLE *SystemTable );

EFI_STATUS
EFIAPI Tcg20DxeEntry(
    IN EFI_HANDLE       ImageHandle,
    IN EFI_SYSTEM_TABLE *SystemTable );




//**********************************************************************
//<AMI_PHDR_START>
// Procedure:   CommonTcgDxEntryPoint
//
// Description: Common entry point for Tcgdxe
//
// Input:       IN EFI_HANDLE        ImageHandle
//              IN EFI_SYSTEM_TABLE *SystemTable
//
// Output:
//
// Modified:
//
// Referrals:
//
// Notes:
//<AMI_PHDR_END>
//**********************************************************************
EFI_STATUS
EFIAPI CommonTcgDxEntryPoint(
    IN EFI_HANDLE       ImageHandle,
    IN EFI_SYSTEM_TABLE *SystemTable )
{
    EFI_STATUS                      Status;
    TCG_PLATFORM_SETUP_PROTOCOL     *ProtocolInstance;
    EFI_GUID                        Policyguid = TCG_PLATFORM_SETUP_POLICY_GUID;
    BOOLEAN                         TpmInitError = FALSE;
#if TCG_LEGACY == 1
    BOOLEAN			                TpmLegBin = TRUE;
#else
    BOOLEAN			                TpmLegBin = FALSE;
#endif
    TCG_CONFIGURATION               Config;
    EFI_TCG_PROTOCOL			    *TcgProtocol;
    EFI_GUID                        TcgFirstbootGuid = AMI_TCG_RESETVAR_HOB_GUID;
    void                            ** DummyPtr;
    BOOLEAN                         *ResetAllTcgVar = NULL;


    InitAmiLib( ImageHandle, SystemTable );

    Status = pBS->LocateProtocol (&Policyguid,  NULL, &ProtocolInstance);
    if (EFI_ERROR (Status)) {
      return Status;
    }

    MemCpy(&Config, &ProtocolInstance->ConfigFlags, sizeof(TCG_CONFIGURATION));
    
    Config.TcgSupportEnabled = 0;
    
    if((AutoSupportType()== TRUE) || (TpmLegBin == TRUE))
    {
        if( Config.TpmSupport != 0x00)
        {
#if TCG_LEGACY == 0
            Config.TcmSupport = TRUE;
            Status = TcmDxeEntry( ImageHandle, SystemTable );
#else
            Config.TcmSupport = FALSE; 
            Status = TpmDxeEntry( ImageHandle, SystemTable);
#endif 
           if(Status){
                Config.TpmHardware = TRUE; 
                TpmInitError = TRUE;
           }              
        }
    }else{
         Config.TcmSupport = FALSE;  
         Status = TpmDxeEntry( ImageHandle, SystemTable );
         if(Status){
            Config.TpmHardware = TRUE; 
            TpmInitError = TRUE;
         }else{
            Config.TpmHardware = FALSE; //negative logic False means present
        }              
    }

    if(TpmInitError){
         Config.Tpm20Device = 0;
         ProtocolInstance->UpdateStatusFlags(&Config, TRUE); 
         return Status;
    }
    
    Status = Tcg20DxeEntry( ImageHandle, SystemTable );
    if(Status != EFI_UNSUPPORTED){
      //all dependent components will depend on
      //the TrEEProtocol installed above
      return EFI_SUCCESS;
    }

    Status = TcgDxeEntry( ImageHandle, SystemTable );
    
    if(EFI_ERROR(Status)){
             
        //if Support was enabled don't change TPM state
        if((ProtocolInstance->ConfigFlags.TcgSupportEnabled!=0 &&
            ProtocolInstance->ConfigFlags.TpmSupport == 0) || 
           (ProtocolInstance->ConfigFlags.TcgSupportEnabled!=0 &&
            ProtocolInstance->ConfigFlags.TcmSupport == 0))
        {  
            Config.TcgSupportEnabled = FALSE;
        }
        else{
            Config.TpmEnable        = 0;
            Config.TpmOperation     = 0;
            Config.TpmEnaDisable    = TRUE;
            Config.TpmActDeact      = TRUE;
            Config.TpmOwnedUnowned  = FALSE;
        }
 
        Config.PpiSetupSyncFlag = TRUE;
        ProtocolInstance->UpdateStatusFlags(&Config, TRUE); 
        return Status;
    }else{
        
        Status = pBS->LocateProtocol (&gEfiTcgProtocolGuid,  NULL, &TcgProtocol);
        if (EFI_ERROR (Status)) {
            Config.TcgSupportEnabled = FALSE;            
            ResetAllTcgVar = (UINT8*)LocateATcgHob(
                                pST->NumberOfTableEntries,
                                pST->ConfigurationTable,
                                &TcgFirstbootGuid);

            DummyPtr = &ResetAllTcgVar;
            if ( *DummyPtr != NULL )
            {
                if ( *ResetAllTcgVar == TRUE )
                {
                    Config.PpiSetupSyncFlag = TRUE;
                }
            }
            
            ProtocolInstance->UpdateStatusFlags(&Config, TRUE); 
            return Status;
        }
        
        Config.Tpm20Device = 0;
        Config.TcgSupportEnabled = TRUE;        
        ProtocolInstance->UpdateStatusFlags(&Config, TRUE); 
    }

    Status = pBS->InstallProtocolInterface(
                &ImageHandle,
                &gEfiTcgPrivateInterfaceGuid,
                EFI_NATIVE_INTERFACE,
                &mTcgPlatformProtocol);

    Status = pBS->InstallProtocolInterface(
                &ImageHandle,
                &AmiTcgPlatformProtocolGuid,
                EFI_NATIVE_INTERFACE,
                &mAmiTcgPlatformProtocol);

    return Status;
}

//**********************************************************************
//**********************************************************************
//**                                                                  **
//**        (C)Copyright 1985-2010, American Megatrends, Inc.         **
//**                                                                  **
//**                       All Rights Reserved.                       **
//**                                                                  **
//**         5555 Oakbrook Parkway, Suite 200, Norcross, GA 30093     **
//**                                                                  **
//**                       Phone: (770)-246-8600                      **
//**                                                                  **
//**********************************************************************
//**********************************************************************
