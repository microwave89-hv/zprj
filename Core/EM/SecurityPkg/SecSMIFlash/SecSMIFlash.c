//**********************************************************************
//**********************************************************************
//**                                                                  **
//**        (C)Copyright 1985-2014, American Megatrends, Inc.         **
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
// $Header: /Alaska/SOURCE/Modules/SecureFlashPkg/SecureSmiFlash/SecSMIFlash.c 61    9/10/14 5:03p Alexp $
//
// $Revision: 61 $
//
// $Date: 9/10/14 5:03p $
//**********************************************************************
// Revision History
// ----------------
// $Log: /Alaska/SOURCE/Modules/SecureFlashPkg/SecureSmiFlash/SecSMIFlash.c $
// 
// 61    9/10/14 5:03p Alexp
// EIP176297: Harden external parameter checks in SW SMI API
// Fixes are made to address:
// #7. Arbitrary SMRAM overwrite in SetFlUpdMethod()
// #8. Integer overflow leading to buffer overflow in 
// LoadFwImage in SecSMIFlash SMI handler
// 
// 60    8/04/14 11:59a Alexp
// 1. Use internal RomLayout map to process Flash Erase/Write requests. 
//     Issue- new RomMap may be different - exposing rom holes in wrong
// places
// 2. SetFlUpdMethod() - SecSmiFlash.RomLayout is updated to a map from a
// new image but not used. 
//    Later may compare the maps to find inconsistencies. 
// 3. BeforeSecureUpdate() - bug in calculating the flash range within
// RomArea
// 
// 59    7/29/14 12:07p Alexp
//  Add a code to erase existing CapsuleUpdate and FlashUdate vars
//  Fixes the case when vars exist with different attributes which prevent
//  SecSmiFlash to set new valid var.
// 
// 57    7/03/14 10:16a Alexp
// EIP176297: Harden external parameter checks in SW SMI API
// 
// 56    6/11/14 10:16a Alexp
// EIP#168391:The power button does not work with failed NVRAM
// - harden SmiS5CapsuleCallback()
// - memory allocation for gpEfiCapsuleHdr changed from runtime memory to
// SMRAM.
// 
// 55    3/20/14 3:20p Alexp
// 1. EIP#159507 : S3 resume time improvement: Use EfiReservedMemoryType 
//  instead of EfiACPIMemoryNVS for large buffer allocations. 
//  FwCapsule buffer to be allocated below 4GB.
// 2. Allow gpPubKeyHndl to be accessed from externally linked code
// 
// 54    1/24/14 4:02p Alexp
// SetFlUpdMethod()
// 1. Set SecSmiFlash.RomLayout only for Runtime and Capsule update
// 2. removed dummy code " SecSmiFlash.pFwCapsule =
// SecSmiFlash.pFwCapsule" 
// 
// 53    10/11/13 2:50p Alexp
// 
// 52    6/21/13 10:56a Alexp
// EIP#125800: add more error checking in release mode inside
// InSmmFunction()
// 
// 51    6/12/13 3:52p Alexp
// CapsuleValidate() made external function in SecSmiFlash API
// 
// 50    6/06/13 4:03p Alexp
// EIP#125800 : Privilege escalation into SMM via Secure SMI Flash SMM
// driver via GetFlUpdPolicy and SetFlUpdMethod - BugID 305294 
// add IsAddressInSmram() checks inside exposed API functions 
// 
// 49    4/23/13 2:49p Alexp
// GetFlUpdPolicy() to return FwKey up to 256 bytes.
// 
// 
// 47    2/26/13 6:14p Alexp
//  Set data size for Capsule Upd variable as 
//  size of (EFI_PHYSICAL_ADDRESS)
// 
// 
// 45    12/28/12 2:19p Alexp
// fix "cppcheck: code style issues
// 
// 42    11/21/12 10:42a Alexp
// Replace direct calls to Hash() in CryptoLib with API calls
// 
// 41    11/13/12 3:26p Alexp
// 1. Calculate offset to RomLayout table within FwCapsHdr instead of
// using hardwired location. Pkcs#7 
//     cert will differ in size and offset may change 
// 2. Remove assert after GetKey function. 
// 
// 40    11/09/12 5:44p Alexp
// fixed branch for FWCAPSULE_2_0_SUPPORT
// 
// 39    10/18/12 10:17a Alexp
// Bug fix: make allocation of HashCtx buffer not to be dependent on
// CAPSULE_RECOVERY support.
// 
// 38    8/28/12 4:12p Alexp
// fix spelling
// 
// 37    8/22/12 9:40a Alexp
// Allow to insrtall SecSmi Flash handler if RomLayout map not detected
// during module Init
// 
// 36    8/16/12 11:31a Alexp
// use global pSmmBase ptr in InSmmFunction()
// 
// 35    7/25/12 6:21p Alexp
// replaced custom Capsule module defined _EFI_CAPSULE_BLOCK_DESCRIPTOR_
// with generic UEFI EFI_CAPSULE_BLOCK_DESCRIPTOR structure
// 
// 34    6/26/12 9:49a Alexp
// include GetRomLayout under 
// #if RUNTIME_SECURE_UPDATE_FLOW == 1
// 
// 33    6/12/12 5:33p Alexp
// EIP74625:New Capsule PPI required by latest Intel's MRC code
//      -Fw Capsule upload supports new Capsule_2_0 format without extra
//       CapHdr in the Mailbox
// EIP90678: MonotonicCounter variable guid changed
//     -Use AMI_GLOBAL_VARIABLE_GUID
// 
// 30    5/21/12 4:55p Alexp
// keep a pointer to FwCaps Hdr withing Capsule image. Streamlines
// creation of Capsule Mailbox. 
// 
// 29    5/18/12 5:27p Alexp
// 1. Replace Hash PPI calls with calls to Crypto lib functions.
// 2. Enforce flash update security by replacing SMM Flash protocol
// Write/Erase functions with local functions
// 3. Include RomLayout map pointer to SecSmiFlash protocol table. Local
// RomMap table is replaced with new one from valid FwCapsule image
// 
// 28    2/29/12 4:15p Alexp
// Removed "gAmiSig->GetKey" from driver entry point. Will use VerifyKey
// instead. FW Key may be stored as a Hash in FW Key file storage.
// 
// 27    2/16/12 9:38a Alexp
// SetFlUpdMethod() - removed condition #if NEW_BIOS_MEM_ALLOC != 0 left
// out from older logic
// 
// 26    2/03/12 2:42p Alexp
// Use SHA256 Hash for Hash table
// 
// 25    1/27/12 12:14p Alexp
// move defines for HASH_TBL_... to SecSmiFlash header file
// 
// 23    1/13/12 4:18p Alexp
// Replace "AFU_FLASH_PAGE_SIZE" with "FLASH_BLOCK_SIZE"
// 
// 22    1/10/12 6:22p Alexp
// 1. Always perform Hash match for new bios data block with one
// calculated during Capsule verification
// 2. Flash block available for hashing is determined by SDL token
// FLASH_BLOCK_SIZE and not by AFU interface
// 
// 21    12/16/11 1:19p Alexp
// Bug fix: UpdateCapsule()
// While preparing MailBox discriptor, the pointer gpCapsuleMailboxPtr
// went outside of allocated memory pEfiCapsuleHdr
// 
// 19    12/01/11 3:34p Alexp
// 1.SmiS5CapsuleCallback-> Introduce a call to Chipset defined
//  SBLib_ResetSystem(WarmReset)
//  Call is included based on the SDL switch CSLIB_WARM_RESET_SUPPORTED
//  It replaces sample oimplementation of WarmReset via S3 & RTC wake up
// 2. SetFlUpdMethod-> Add temp w/a for AFU rev 3.0. Wrong image size(0)
//  is reported by AFU in pSessionBlock->FlUpdBlock.ImageSize
// 3. Updated conditional statements to match newly defined SDL tokens:
//  INSTALL_SECURE_FLASH_SW_SMI_HNDL and CSLIB_WARM_RESET_SUPPORTED
// 
// 17    11/30/11 8:11p Alexp
// 1. Replaced dependencies from WARM_REBOOT flag to generic
// FWCAPSULE_RECOVERY_SUPPORT
// 2. SetFlUpdMethod() corercted behavior of some AFU implementations for
// CApsule Set mode. Size should have been provided
// 3. Memory for Capsule Mailbox allocation moved form "EfiRuntime" to
// more appropriate "AcpiNvs"
// 
// 16    11/11/11 12:50p Alexp
// fixed InSmmFunction() when building without FWCAPSULE_RECOVERY_SUPPORT
// 
// 15    11/03/11 6:45p Alexp
// skip SecSMIFlashSMIHandler() if OFBD Secure Flash module is active
// 
// 14    10/17/11 11:25a Alexp
// update Hdr & Footer. Clear BIOS buffer  
// 
// 13    10/11/11 12:28p Alexp
// add OFBD dependency
// 
// 12    9/30/11 4:39p Alexp
// add porting notes
// 
// 11    8/24/11 6:51p Alexp
// replaced CAPSULE_SUPPORT check to FWCAPSULE_RECOVERY_SUPPORT
// 
// 10    8/24/11 11:30a Alexp
// Clear Capsule update capability in gFlUpdatePolicy.FlashUpdate if no
// Capsule Driver or WarmReboot tokens are defined
// 
// 9     8/09/11 7:45p Alexp
// 
// 8     8/09/11 9:54a Alexp
// bug fix: NEW #if NEW_BIOS_MEM_ALLOC != 0, OLD: #if NEW_BIOS_MEM_ALLOC
// 
// 7     8/08/11 7:23p Alexp
// SetFlashUpdateVar - assign Attributes to SetVar via CounterHi variable.
// old init method "A | B | C" had wrong Attributes passed to the SetVar
// 
// 6     8/06/11 11:35a Alexp
// LoadImage-> clear out FSHndl. Need to be set to valid value only if
// image Verification complete inside SetFlMethod 
// 
// 5     8/05/11 3:43p Alexp
// hardwire Flash Upd policy (staticly provided from SDL tokens)
// 
// 4     7/21/11 3:13p Alexp
// removed  mistakenly put while(1){} statement at the end of
// SmiS5CapsuleCallback() 
// 
// 3     7/20/11 7:20p Alexp
// removed dependency on Capsule module.
// 
// 2     7/20/11 6:22p Alexp
// include sample implementation to enter S3 on AMD chipsets
// 
// 1     7/01/11 4:41p Alexp
// 
// 1     7/01/11 4:37p Alexp
// 
// 10    6/24/11 4:32p Alexp
// move around debug comments
// 
// 9     6/24/11 2:09p Alexp
// SetFlUpd: abort if capsule size passed by AFU is greater then allocated
// buffer in gRomFileSize
// 
// 8     6/23/11 7:08p Alexp
// SetFlashUpd: update local buffer with Ptr to AFU allocated buffer with
// rom image
// 
// 14    6/20/11 2:10p Alexp
//                 // AFU updates the address in CapsuleMailboxPtr if 
// SetFlashMethod: update for the case if AFU provided address in memory
// for new BIOS image
// 
// 7     6/17/11 5:47p Alexp
// bug fix: GetKey expects valid buffer size on input
// 
// 6     6/01/11 12:35p Alexp
// fix FSHandle init value
// 
// 5     5/25/11 8:31p Alexp
// forse Implemented flag to "1" if SecSMIFlash supported. ASFU would
// check for combination, Version>-12 and this flag to determine if SecSMI
// Flash API is supported
// 
// 4     5/17/11 12:58p Alexp
// add build switch for location of temp BIOS image
// 
// 3     5/12/11 7:58p Alexp
// 
// 2     5/10/11 5:10p Alexp
// Hash guids are defined globally
// 
// 1     5/10/11 10:01a Alexp
// 
// 13    5/06/11 11:59a Alexp
// 
// 12    5/02/11 3:22p Alexp
// merged capsule hdr and mailbox into one mem allocation unit
// 
// 11    4/28/11 6:21p Alexp
// tbd: in release mode get FW pub key may fail
// 
// 10    4/28/11 10:45a Alexp
// update Capsule mailbox format. Add extra Efi Capsule Hdr that will be
// discarded by CApsul PEI service while coalescing the Capsule into a Hob
// 
// 8     4/22/11 4:36p Alexp
// temp debug: init MC field in FlashUpd var with 0 if MC Var is missing.
// 
// 7     4/19/11 6:42p Alexp
// tested Reboot and Online flash. Recovery flow fails. 
// 
// 6     4/18/11 7:22p Alexp
// working version. Need to review HashTable as it may not be practical if
// block sizes do not mach BLOCK_SIZE
// 
// 5     4/13/11 7:14p Alexp
// locate RomMap for easy location of Fid.ffs for VersionControl
// Create HashTable for uplaoded Fw Image. Used for runtime updates only
// generate FSHandle for future use
// 
// 4     4/11/11 2:10p Alexp
// -Revision 12 and upper to support "Installed" field in Flash Info as
// bit mask
// -Add support for new CApsule SigningCert header
// - Replace PKpub with new FW Sign key as a root Platform key to verify
// Capsule Sig with
// 
// 3     4/05/11 6:38p Alexp
// use GetVariable to get PK Pub key
// 
// 2     3/11/11 6:51p Alexp
// 
// 1     3/10/11 4:59p Alexp
// 
// 1     3/03/11 6:34p Alexp
// 
//**********************************************************************

#include <Token.h>
#include <AmiDxeLib.h>
#include <Protocol\SmiFlash.h>
#include <Protocol\SmmBase.h>
#include <Protocol\SmmSwDispatch.h>
#include <Protocol\SmmSxDispatch.h>
#include <Protocol\DevicePath.h>
#include <Protocol\LoadedImage.h>
#include <AmiSmm.h>
//PI 1.1 ++
#if defined(PI_SPECIFICATION_VERSION)&&(PI_SPECIFICATION_VERSION>=0x0001000A)
#include <Protocol\SmmAccess2.h>
#else
#include <Protocol\SmmAccess.h>
#endif

#if FWCAPSULE_RECOVERY_SUPPORT == 1
#include <Capsule.h>
#endif

#include <AmiHobs.h>

#include <Protocol\SecSmiFlash.h>
#include <Protocol\FlashProtocol.h>

//----------------------------------------------------------------------
// Module defined global variables
static EFI_GUID gSwSmiCpuTriggerGuid = SW_SMI_CPU_TRIGGER_GUID;
static EFI_GUID gEfiSmmSwDispatchProtocolGuid = EFI_SMM_SW_DISPATCH_PROTOCOL_GUID;
static EFI_GUID gEfiSmmSxDispatchProtocolGuid = EFI_SMM_SX_DISPATCH_PROTOCOL_GUID;
//extern EFI_GUID gEfiSmmSxDispatchProtocolGuid             = EFI_SMM_SX_DISPATCH_PROTOCOL_GUID;

// AMI_GLOBAL_VARIABLE_GUID must be defined in AmiLib.h (Core 4.6.5.4 +)
#if defined(AMI_GLOBAL_VARIABLE_GUID)
static EFI_GUID gAmiGlobalVariableGuid = AMI_GLOBAL_VARIABLE_GUID;    
#else
static EFI_GUID gAmiGlobalVariableGuid = EFI_GLOBAL_VARIABLE;
#endif

static EFI_GUID FlashUpdGuid    = FLASH_UPDATE_GUID;

EFI_GUID gFWCapsuleGuid         = APTIO_FW_CAPSULE_GUID;
EFI_GUID gPRKeyGuid             = PR_KEY_GUID;
EFI_GUID gFwCapFfsGuid          = AMI_FW_CAPSULE_FFS_GUID;

static FLASH_UPD_POLICY FlUpdatePolicy = {FlashUpdatePolicy, BBUpdatePolicy};

EFI_SHA256_HASH  *gHashTbl = NULL;
UINT8             gHashDB[SHA256_DIGEST_SIZE];
CRYPT_HANDLE      gpPubKeyHndl;

AMI_DIGITAL_SIGNATURE_PROTOCOL *gAmiSig;

#if FWCAPSULE_RECOVERY_SUPPORT == 1
static EFI_GUID     CapsuleVendorGuid  = EFI_CAPSULE_AMI_GUID;
EFI_CAPSULE_BLOCK_DESCRIPTOR  *gpEfiCapsuleHdr    = NULL;
#endif

// BIOS allocates the space in AcpiNVS for new BIOS image to be uploaded by Flash tool
// Alternatively the buffer may be reserved within the SMM TSEG. Check NEW_BIOS_MEM_ALLOC Token
// AFU would have to execute a sequence of SW SMI calls to load new BIOS image to mem
UINTN    gFwCapMaxSize     = FWCAPSULE_IMAGE_SIZE;
UINT32   *pFwCapsuleLowMem = NULL;

static EFI_SMRAM_DESCRIPTOR *mSmramRanges;
static UINTN                mSmramRangeCount;
//----------------------------------------------------------------------
// Flash Upd Protocol defines
//----------------------------------------------------------------------
typedef EFI_STATUS (EFIAPI *FLASH_READ_WRITE)(
    VOID* FlashAddress, UINTN Size, VOID* DataBuffer
);
typedef EFI_STATUS (EFIAPI *FLASH_ERASE)(
    VOID* FlashAddress, UINTN Size
);

FLASH_PROTOCOL      *Flash;

FLASH_READ_WRITE    pFlashWrite; // Original Ptr inside FlashAPI
FLASH_ERASE         pFlashErase;

static   UINT32    Flash4GBMapStart;
ROM_AREA *RomLayout = NULL;
//----------------------------------------------------------------------

//----------------------------------------------------------------------
// UpFront Function definitions
BOOLEAN SupportUpdateCapsuleReset ( 
    VOID 
);
EFI_STATUS CapsuleValidate (
    IN OUT UINT8     **pFwCapsule,
    IN OUT APTIO_FW_CAPSULE_HEADER     **pFwCapsuleHdr
);
EFI_STATUS LoadFwImage(
    IN OUT FUNC_BLOCK  *pFuncBlock
);
EFI_STATUS GetFlUpdPolicy(
    IN OUT FLASH_POLICY_INFO_BLOCK  *InfoBlock
);
EFI_STATUS SetFlUpdMethod(
    IN OUT FUNC_FLASH_SESSION_BLOCK  *pSessionBlock
);
EFI_STATUS FindCapHdrFFS(
    IN  VOID    *pCapsule,
    OUT UINT8  **pFfsData
);
BOOLEAN IsAddressInSmram (
    IN EFI_PHYSICAL_ADDRESS  Buffer,
    IN UINT64                Length
);

//----------------------------------------------------------------------
//<AMI_PHDR_START>
//----------------------------------------------------------------------
// Procedure:   SecSmiFlash
//
// Description: 
//
// Input:   
//
// Output: 
//
// Returns: 
//
//----------------------------------------------------------------------
//<AMI_PHDR_END>
EFI_SEC_SMI_FLASH_PROTOCOL    SecSmiFlash = {
    LoadFwImage,
    GetFlUpdPolicy,
    SetFlUpdMethod,
    CapsuleValidate,
    0,// pFwImageLowMem
    0,// RomLayout,
    0,// gSha256HashTbl,
    0,// FSHandle
};

#if FWCAPSULE_RECOVERY_SUPPORT == 1

#if CSLIB_WARM_RESET_SUPPORTED == 0

//#if (defined x64_BUILD && x64_BUILD == 1)
//VOID    flushcaches();
void    DisableCacheInCR0();
//#endif

//<AMI_PHDR_START>
//---------------------------------------------------------------------------
//
// FUNCTION:  ReadRtcIndexedRegister
//
// DESCRIPTION: Used to read RTC register indexed by the argument
//
// Input:
//    IN UINT8    Index        Index of the register to read
//                                                         
//
// Output:
//    UINT8                    Current value of the register
//
//---------------------------------------------------------------------------
//<AMI_PHDR_END>
UINT8 ReadRtcIndexedRegister(IN UINT8 Index){

    UINT8 Byte = IoRead8(0x70) & 0x80;   // preserve bit 7
    IoWrite8(0x70, Index | Byte);
    Byte = IoRead8(0x71);
    return Byte;
}

//<AMI_PHDR_START>
//---------------------------------------------------------------------------
//
// FUNCTION:  ReadRtcIndexedRegister
//
// DESCRIPTION: Used to write to RTC register indexed by the argument
//
// Input:
//    IN UINT8    Index        Index of the register to write to 
//                                                         
//      IN UINT8  Value        Value to write to the RTC register
//
// Output:
//    VOID
//
//---------------------------------------------------------------------------
//<AMI_PHDR_END>
VOID WriteRtcIndexedRegister(IN UINT8 Index, IN UINT8 Value){
 
    IoWrite8(0x70,Index | (IoRead8(0x70) & 0x80));
    IoWrite8(0x71,Value);   
}

//<AMI_PHDR_START>
//----------------------------------------------------------------------------
//
// Procedure:   S3RTCresume
//
// Description: This function puts system into ACPI S3 State.
//              if token ENABLE_RTC_ONE_SECOND_WAKEUP = 1, then it setups RTC
//              1 second alarm as well.
//
// Input:       None
//
// Output:      None, system will enter ACPI S3 State.
//----------------------------------------------------------------------------
//<AMI_PHDR_END>

VOID S3RTCresume (VOID)
{
    UINT32 IoData;
    UINT8 Hour, Minute, Second;
    BOOLEAN     inBCD = TRUE;

    //flush caches befor going to S3
//#if (defined x64_BUILD && x64_BUILD == 1)
//        flushcaches();
    DisableCacheInCR0();
//#else
//        _asm wbinvd
//#endif
    
    // determine if RTC is in BCD mode
    if( ReadRtcIndexedRegister(0xB) & 0x4 ) // bit 2
        inBCD = FALSE;
    // wait for time update to complete before reading the values
    while( ReadRtcIndexedRegister(0xA) & 0x80 ); // while bit 7 is set the 
                                                // time update is in progress
    //read current hour, minute, second
    Hour = ReadRtcIndexedRegister(0x4);
    Minute = ReadRtcIndexedRegister(0x2);
    Second = ReadRtcIndexedRegister(0x0);

    //convert second to decimal from BCD and increment by 1
    if(inBCD)
        Second = (Second >> 4) * 10 + (Second & 0x0F);
    Second += 2;
    
    if(Second > 59){
        Second -= 60;
        if(inBCD)
            Minute = (Minute >> 4) * 10 + (Minute & 0x0F);
        Minute++;
        if(Minute > 59){
            Minute = 0;
            if(inBCD)
                Hour = (Hour >> 4) * 10 + (Hour & 0x0F);
            Hour++;
            // check 24 hour mode/12 hour mode
            if( ReadRtcIndexedRegister(0xB) & 0x2 ) {// bit 1 1=24hour else 12 hour
                if(Hour > 23)
                    Hour = 0;
            } else {
                if(Hour > 11)
                    Hour = 0;
            }

            if(inBCD)
                Hour = Hour % 10 + ( (Hour / 10) << 4 ) ;
        }
        if(inBCD)
            Minute = Minute % 10 + ( (Minute / 10) << 4 ) ;
    }

    //convert from decimal to BCD
    if(inBCD)
        Second = Second % 10 + ( (Second / 10) << 4 ) ;
    
    //set the alarm

    WriteRtcIndexedRegister(0x5, Hour);
    WriteRtcIndexedRegister(0x3, Minute);
    WriteRtcIndexedRegister(0x1, Second);
    //enable the alarm
    WriteRtcIndexedRegister(0xB, ( ReadRtcIndexedRegister(0xB) | ((UINT8)( 1 << 5 )) ));

// ========== PORTING REQUIRED ===========================================================
//  Current implementation to simulate the Warm Reboot may not be sufficient on some platforms. 
//  S3 transition may require additional Chipset/Platform coding.
//  If needed add any necessary OEM hooks to be able to put the system into S3 at the end of this handler
//========================================================================================

    //set RTC_EN bit in PM1_EN to wake up from the alarm
    IoWrite16(PM_BASE_ADDRESS + 0x02, ( IoRead16(PM_BASE_ADDRESS + 0x02) | (1 << 10) ));
    
    //Disable Sleep SMI to avoid SMI re-entrance.
//    IoWrite16(PM_BASE_ADDRESS + 0x30, ( IoRead16(PM_BASE_ADDRESS + 0x30) & (~BIT4) ));
    
    //modify power management control register to reflect S3
    IoData = IoRead32(PM_BASE_ADDRESS + 0x04);
    //following code is applicable to Intel PCH only. 
    IoData &= ~(0x1C00);
    IoData |= 0x1400; //Suspend to RAM
/*
    // AMD w/a to enter S3 state
    IoData |= 0x2C00; //Suspend to RAM
    {
        UINT8 Temp8;
        IoWrite8(0xCD6, 0x004);
        Temp8 = IoRead8(0xCD7);
        Temp8 &= ~(BIT7);
        IoWrite8(0xCD6, 0x004);
        IoWrite8(0xCD7, Temp8);
        IoWrite8(0xCD6, 0x007);
        IoWrite8(0xCD7, BIT7);
    }
} 
*/
    IoWrite32(PM_BASE_ADDRESS + 0x04, IoData );
}
//#else
//extern SBLib_ResetSystem( IN EFI_RESET_TYPE ResetType );
#endif
extern SBLib_ResetSystem( IN EFI_RESET_TYPE ResetType );
//<AMI_PHDR_START>
//---------------------------------------------------------------------------
//
// FUNCTION:  SmiS5CapsuleCallback
//
// DESCRIPTION: SMI handler to perform capsule reset (bounce from S5 to S3)
// ========== PORTING REQUIRED ===========================================================
//  Current implementation to simulate the Warm Reboot may not be sufficient on some platforms. 
//  S3 transition may require additional Chipset/Platform coding.
//  If needed add any necessary OEM hooks to be able to put the system into S3 at the end of this handler
//========================================================================================
//
// Input:
//    IN  EFI_HANDLE    DispatchHandle                   Handle of SMI dispatch
//                                                       protocol
//    IN  EFI_SMM_SX_DISPATCH_CONTEXT* DispatchContext   Pointer to SMI dispatch
//                                                       context structure
//
// Output:
//    VOID
//
//---------------------------------------------------------------------------
//<AMI_PHDR_END>
VOID SmiS5CapsuleCallback ( IN  EFI_HANDLE                    DispatchHandle,
                            IN  EFI_SMM_SX_DISPATCH_CONTEXT   *DispatchContext
){
    EFI_PHYSICAL_ADDRESS    IoData;
    UINTN                   Size;
    EFI_CAPSULE_HEADER     *CapsuleHeader;
    AMI_FLASH_UPDATE_BLOCK FlUpdateBlock;

    TRACE((TRACE_ALWAYS,"SecSMI. S5 Trap\n"));
    
    //
    //Check if the Capsule update is supported by platform policy
    //
    if (!SupportUpdateCapsuleReset()) 
        return;

    Size=sizeof(AMI_FLASH_UPDATE_BLOCK);
    if(EFI_ERROR(pRS->GetVariable(FLASH_UPDATE_VAR,&FlashUpdGuid, NULL, &Size, &FlUpdateBlock)) ||
       FlUpdateBlock.FlashOpType != FlCapsule)
        return;

    // verify the FW capsule is in memory.
    Size = sizeof(EFI_PHYSICAL_ADDRESS);
    if(EFI_ERROR(pRS->GetVariable(CAPSULE_UPDATE_VAR,&CapsuleVendorGuid, NULL, &Size, &IoData)))
         return;

    if(IoData != (EFI_PHYSICAL_ADDRESS)gpEfiCapsuleHdr ||
      !IsAddressInSmram((EFI_PHYSICAL_ADDRESS)IoData, sizeof(EFI_PHYSICAL_ADDRESS)))
        return;

    CapsuleHeader = (EFI_CAPSULE_HEADER*)gpEfiCapsuleHdr[0].DataBlock;
    //
    // Compare GUID with APTIO_FW_CAPSULE_GUID 
    //
    if (guidcmp (&CapsuleHeader->CapsuleGuid, &gFWCapsuleGuid))
        return;

#if CSLIB_WARM_RESET_SUPPORTED == 1
    SBLib_ResetSystem(EfiResetWarm);
#else
    S3RTCresume();
#endif
}

//<AMI_PHDR_START>
//----------------------------------------------------------------------------
// Procedure:    SupportUpdateCapsuleReset
//
// Description:  This function returns platform policy capability for capsule update via a system reset.
//
// Input:        None
//
// Output:      TRUE  - memory can be preserved across reset
//              FALSE - memory integrity across reset is not guaranteed
//
//----------------------------------------------------------------------------
//<AMI_PHDR_END>
BOOLEAN SupportUpdateCapsuleReset (
    VOID
)
{
  //
  //If the platform has a way to guarantee the memory integrity across a system reset, return 
  //TRUE, else FALSE. 
  //
    if( (FlUpdatePolicy.FlashUpdate & FlCapsule) || 
        (FlUpdatePolicy.BBUpdate & FlCapsule))
        return TRUE;

    return FALSE;
}

//<AMI_PHDR_START>
//----------------------------------------------------------------------------
// Procedure:    UpdateCapsule
//
// Description:    This code prepares Capsule Update EFI Variable
//
// Input:        
//  IN EFI_CAPSULE_HEADER **CapsuleHeaderArray - array of pointers to capsule headers passed in
//
// Output:      EFI_SUCCESS - capsule processed successfully
//              EFI_INVALID_PARAMETER - CapsuleCount is less than 1,CapsuleGuid is not supported
//              EFI_DEVICE_ERROR - capsule processing failed
//
//----------------------------------------------------------------------------
//<AMI_PHDR_END>
EFI_STATUS UpdateCapsule (
    IN FUNC_FLASH_SESSION_BLOCK *pSessionBlock,
    IN APTIO_FW_CAPSULE_HEADER  *pFwCapsuleHdr
){
    EFI_STATUS          Status;
    EFI_CAPSULE_HEADER *pEfiCapsuleHdr = NULL;
    EFI_CAPSULE_BLOCK_DESCRIPTOR *pCapsuleMailboxPtr;
    UINT32              Attributes, Index;

    //
    //Compare GUID with APTIO_FW_CAPSULE_GUID 
    //
    if (!pFwCapsuleHdr ||
        guidcmp (&pFwCapsuleHdr->CapHdr.CapsuleGuid, &gFWCapsuleGuid)
    )
        return EFI_DEVICE_ERROR; 

    pCapsuleMailboxPtr = gpEfiCapsuleHdr;
    Index = 0;
#if !defined(FWCAPSULE_2_0_SUPPORT) || FWCAPSULE_2_0_SUPPORT == 0
    pEfiCapsuleHdr = (EFI_CAPSULE_HEADER*)&pCapsuleMailboxPtr[4];
// New Capsule PPI supports single CapHdr.
// construct dummy EfiCapHdr struct within pEfiCapsuleHdr as 1st element to be linked from Mailbox
    MemCpy((VOID*)pEfiCapsuleHdr, &gFWCapsuleGuid, sizeof(EFI_GUID));
    pEfiCapsuleHdr->Flags = CAPSULE_FLAGS_PERSIST_ACROSS_RESET;
    pEfiCapsuleHdr->HeaderSize = sizeof(EFI_CAPSULE_HEADER);
    pEfiCapsuleHdr->CapsuleImageSize = pFwCapsuleHdr->CapHdr.CapsuleImageSize + sizeof(EFI_CAPSULE_HEADER);
    // create ScatterGather list: use pre-allocated runtime memory
    pCapsuleMailboxPtr[Index].Length = pEfiCapsuleHdr->HeaderSize;
    pCapsuleMailboxPtr[Index].DataBlock = (EFI_PHYSICAL_ADDRESS)pEfiCapsuleHdr;
    Index++;
#endif
    pCapsuleMailboxPtr[Index].Length = pFwCapsuleHdr->CapHdr.HeaderSize;
    pCapsuleMailboxPtr[Index].DataBlock = (EFI_PHYSICAL_ADDRESS)pFwCapsuleHdr;
    pCapsuleMailboxPtr[Index+1].Length = pFwCapsuleHdr->CapHdr.CapsuleImageSize-pFwCapsuleHdr->CapHdr.HeaderSize;
    if((UINT32*)pFwCapsuleLowMem == (UINT32*)pFwCapsuleHdr) {
    // Fw Cap Hdr is on top of Payload

        pCapsuleMailboxPtr[Index+1].DataBlock = pCapsuleMailboxPtr[Index].DataBlock+pCapsuleMailboxPtr[Index].Length;
    } else {
    // Fw Cap Hdr is embedded inside Payload
        pCapsuleMailboxPtr[Index+1].DataBlock = (EFI_PHYSICAL_ADDRESS)pFwCapsuleLowMem;
    }
    pCapsuleMailboxPtr[Index+2].Length = 0;
    pCapsuleMailboxPtr[Index+2].DataBlock = 0;
    //
    //Check if the platform supports update capsule across a system reset
    //
    if (!SupportUpdateCapsuleReset()) {
        return EFI_UNSUPPORTED;
    }
    // Erase prev copy
    Status = pRS->SetVariable ( CAPSULE_UPDATE_VAR, &CapsuleVendorGuid,0,0,NULL); 
    Attributes = EFI_VARIABLE_NON_VOLATILE | EFI_VARIABLE_RUNTIME_ACCESS | EFI_VARIABLE_BOOTSERVICE_ACCESS;
    Status = pRS->SetVariable ( CAPSULE_UPDATE_VAR, &CapsuleVendorGuid, 
                                Attributes, sizeof(EFI_PHYSICAL_ADDRESS),(VOID*)&pCapsuleMailboxPtr);

    if(!EFI_ERROR(Status))
        return Status;
 
    return EFI_DEVICE_ERROR;
}

#endif //#if FWCAPSULE_RECOVERY_SUPPORT == 1

//<AMI_PHDR_START>
//----------------------------------------------------------------------------
// Procedure:    SetFlashUpdateVar
//
// Description:    This code finds if the capsule needs reset to update, if no, update immediately.
//
// Input:
//  IN EFI_CAPSULE_HEADER **CapsuleHeaderArray - array of pointers to capsule headers passed in
//  IN UINTN CapsuleCount - number of capsule
//  IN EFI_PHYSICAL_ADDRESS ScatterGatherList - physical address of datablock list points to capsule
//
// Output:        EFI_SUCCESS - capsule processed successfully
//              EFI_INVALID_PARAMETER - CapsuleCount is less than 1,CapsuleGuid is not supported
//              EFI_DEVICE_ERROR - capsule processing failed
//
//----------------------------------------------------------------------------
//<AMI_PHDR_END>
EFI_STATUS SetFlashUpdateVar (
    IN FUNC_FLASH_SESSION_BLOCK    *pSessionBlock
){
    EFI_STATUS          Status;
    UINTN               Size;
    UINT32              CounterHi;

    if(pSessionBlock->FlUpdBlock.FlashOpType == FlRecovery &&
        pSessionBlock->FlUpdBlock.FwImage.AmiRomFileName[0] == 0
    )
        return EFI_DEVICE_ERROR;

    CounterHi = 0;
    Size = sizeof(UINT32);
// MonotonicCounter is a boot time service, hence the variable may have restricted access in runtime
    if(EFI_ERROR(pRS->GetVariable(L"MonotonicCounter", &gAmiGlobalVariableGuid,
                  NULL, &Size, &CounterHi))
    )
//        return Status;//EFI_DEVICE_ERROR;
//SetMode should set FlashUpd even if no MC var detected.
        CounterHi=0xffffffff;

    pSessionBlock->FlUpdBlock.MonotonicCounter = CounterHi;
    CounterHi = (EFI_VARIABLE_NON_VOLATILE |
        EFI_VARIABLE_RUNTIME_ACCESS |
        EFI_VARIABLE_BOOTSERVICE_ACCESS);
    // Erase prev copy
    Status = pRS->SetVariable ( FLASH_UPDATE_VAR, &FlashUpdGuid,0,0,NULL); 
    Status = pRS->SetVariable ( FLASH_UPDATE_VAR, &FlashUpdGuid, CounterHi,
        sizeof(AMI_FLASH_UPDATE_BLOCK), (VOID*) &pSessionBlock->FlUpdBlock
    );

    if(!EFI_ERROR(Status))
        return Status;

    return EFI_DEVICE_ERROR;
}

//<AMI_PHDR_START>
//----------------------------------------------------------------------
// Procedure:   GetFlUpdPolicy
//
// Description: 
//
// Input:   
//
// Output: 
//
// Returns: 
//
//----------------------------------------------------------------------
//<AMI_PHDR_END>
EFI_STATUS GetFlUpdPolicy(
    IN OUT FLASH_POLICY_INFO_BLOCK  *InfoBlock
)
{
    UINT32  KeySize = DEFAULT_RSA_KEY_MODULUS_LEN;

//TRACE((TRACE_ALWAYS,"SecSMI. GetPolicy. %X_%X\n",FlUpdatePolicy.FlashUpdate, FlUpdatePolicy.BBUpdate));

    if(IsAddressInSmram((EFI_PHYSICAL_ADDRESS)InfoBlock, sizeof(FLASH_POLICY_INFO_BLOCK)))
        return EFI_DEVICE_ERROR;

    MemCpy(&InfoBlock->FlUpdPolicy, &FlUpdatePolicy, sizeof(FLASH_UPD_POLICY));
    MemSet(&InfoBlock->PKpub, KeySize, 0xFF);
    if(gpPubKeyHndl.BlobSize < KeySize)
        KeySize = gpPubKeyHndl.BlobSize;
    MemCpy(&InfoBlock->PKpub, gpPubKeyHndl.Blob, KeySize);

    InfoBlock->ErrorCode = 0;

    return EFI_SUCCESS;
}
//<AMI_PHDR_START>
//----------------------------------------------------------------------
// Procedure:   SetFlUpdMethod
//
// Description: 
//
// Input:   
//
// Output: 
//
// Returns: 
//
//----------------------------------------------------------------------
//<AMI_PHDR_END>
EFI_STATUS SetFlUpdMethod(
    IN OUT FUNC_FLASH_SESSION_BLOCK    *pSessionBlock
)
{
    EFI_STATUS          Status = EFI_DEVICE_ERROR;
#if RUNTIME_SECURE_UPDATE_FLOW == 1
    UINT32              HashBlock;
    UINT32              BlockSize;
    UINT8              *BlockAddr;
#endif
    UINT32             *FSHandl;
    APTIO_FW_CAPSULE_HEADER    *pFwCapsuleHdr;

//TRACE((TRACE_ALWAYS,"SecSMI. SetFlash\nSize     : %X\n",pSessionBlock->FlUpdBlock.ImageSize));

    if(IsAddressInSmram((EFI_PHYSICAL_ADDRESS)pSessionBlock, sizeof(FUNC_FLASH_SESSION_BLOCK)))
        return EFI_DEVICE_ERROR;

//if(pSessionBlock->FlUpdBlock.FlashOpType == FlRecovery)
//TRACE((TRACE_ALWAYS,"File Name: %s\n",pSessionBlock->FlUpdBlock.FwImage.AmiRomFileName));
//else
//TRACE((TRACE_ALWAYS,"Image Adr: %X\n",pSessionBlock->FlUpdBlock.FwImage.CapsuleMailboxPtr[0]));

//TRACE((TRACE_ALWAYS,"ROMmap   : %X\n",pSessionBlock->FlUpdBlock.ROMSection));
//TRACE((TRACE_ALWAYS,"FlOpType : %X\n",pSessionBlock->FlUpdBlock.FlashOpType));
// Verify if chosen Flash method is compatible with FlUpd Policy
    if(((pSessionBlock->FlUpdBlock.ROMSection & (1<<BOOT_BLOCK)) && (pSessionBlock->FlUpdBlock.FlashOpType & FlUpdatePolicy.BBUpdate)) || 
      (!(pSessionBlock->FlUpdBlock.ROMSection & (1<<BOOT_BLOCK))&& (pSessionBlock->FlUpdBlock.FlashOpType & FlUpdatePolicy.FlashUpdate))
    ){

//TRACE((TRACE_ALWAYS,"Buff Adr : %X\nBuff Size: %X\n",pFwCapsuleLowMem, gRomFileSize));
//!!! make sure Flash blocks BOOT_BLOCK, MAIN_, NV_ and EC_ are matching enum types in FlashUpd.h
        // Get Flash Update mode   
        switch(pSessionBlock->FlUpdBlock.FlashOpType)
        {
#if FWCAPSULE_RECOVERY_SUPPORT == 1
            case FlCapsule:
#endif
            case FlRuntime:
            //  common for FlRuntime or Capsule
                if(pSessionBlock->FlUpdBlock.ImageSize > gFwCapMaxSize)
                    break; // suspecting buffer overrun. 

                SecSmiFlash.pFwCapsule = pFwCapsuleLowMem;
                // AFU updates the address in CapsuleMailboxPtr if 
                // it's capable of allocating large buffer to load entire FW Capsule image
                if(pSessionBlock->FlUpdBlock.FwImage.CapsuleMailboxPtr[0] != 0 )
                {
                    if(IsAddressInSmram((EFI_PHYSICAL_ADDRESS)pSessionBlock->FlUpdBlock.FwImage.CapsuleMailboxPtr[0],
                                            pSessionBlock->FlUpdBlock.ImageSize))
                        return EFI_DEVICE_ERROR;
#if NEW_BIOS_MEM_ALLOC != 2
                    if(SecSmiFlash.pFwCapsule != NULL) {
                        // prevent leaking of the SMM code to the external buffer
                        if(!IsAddressInSmram((EFI_PHYSICAL_ADDRESS)SecSmiFlash.pFwCapsule, sizeof(UINTN)))
                            return EFI_DEVICE_ERROR;

                        MemCpy((UINT8*)SecSmiFlash.pFwCapsule,
                            (UINT8*)pSessionBlock->FlUpdBlock.FwImage.CapsuleMailboxPtr[0],
                            pSessionBlock->FlUpdBlock.ImageSize);
                    }
                    else
#endif
                        SecSmiFlash.pFwCapsule = (UINT32*)pSessionBlock->FlUpdBlock.FwImage.CapsuleMailboxPtr[0];
                } 
                // else AFU must've uploaded the image to designated SMM space using LoadFw command

                // verify we got a capsule at pFwCapsuleLowMem, update a ptr to FwCapHdr within Payload image
                Status = CapsuleValidate((UINT8**)&(SecSmiFlash.pFwCapsule), &pFwCapsuleHdr);
                if(!pFwCapsuleHdr || 
                    EFI_ERROR(Status)) break;
                // capture RomLayout from new Secure Image if it's loaded in memory and validated
                SecSmiFlash.RomLayout = (ROM_AREA *)(UINTN)((UINT32)pFwCapsuleHdr+pFwCapsuleHdr->RomLayoutOffset);
                if(pSessionBlock->FlUpdBlock.FlashOpType == FlRuntime)
                {
#if RUNTIME_SECURE_UPDATE_FLOW == 1
                    // Fill in gShaHashTbl Hash Table
                    BlockSize = FLASH_BLOCK_SIZE;
                    BlockAddr = (UINT8*)SecSmiFlash.pFwCapsule;
                    for(HashBlock = 0; HashBlock < SEC_FLASH_HASH_TBL_BLOCK_COUNT; HashBlock++) 
                    {

                        Status = gAmiSig->Hash(gAmiSig, &gEfiHashAlgorithmSha256Guid, 
                            1, &BlockAddr, (const UINTN*)&BlockSize, gHashTbl[HashBlock]); 
                        if (EFI_ERROR(Status)) break;
                        BlockAddr+= (UINTN)(BlockSize);
                    }
#endif
                    // done for Runtime Upd
                    break;
                }
            // Set Capsule EFI Var if Capsule(Verify Capsule Mailbox points to FW_CAPSULE) 
                pSessionBlock->FlUpdBlock.ImageSize = pFwCapsuleHdr->CapHdr.CapsuleImageSize;
#if FWCAPSULE_RECOVERY_SUPPORT == 1
                Status = UpdateCapsule (pSessionBlock, pFwCapsuleHdr);
                if(EFI_ERROR(Status)) break;
#endif
            //  common for Recovery or Capsule
            case FlRecovery:
                //  Set FlUpd EFI Var (Get MC, verify RecFileName)
                Status = SetFlashUpdateVar (pSessionBlock);
                break;

            default:
                Status = EFI_DEVICE_ERROR;
        }
    }

    // Set Error Status
    if (Status != EFI_SUCCESS) { 
        SecSmiFlash.FSHandle = 0;
        SecSmiFlash.pFwCapsule = NULL;
        SecSmiFlash.RomLayout = RomLayout; // back to default RomLayout
        pSessionBlock->FSHandle  = 0;
        pSessionBlock->ErrorCode = 1;

        return EFI_DEVICE_ERROR;
    }
    // FSHandle is updated if Capsule validation passed.
    // Create FSHandle as 1st 4 bytes of gHashTbl. It must be different each time 
    //  SetMethod is called with new Image
    FSHandl = (UINT32*)gHashTbl;
    SecSmiFlash.FSHandle = *FSHandl; // should be unique per Capsule;
    pSessionBlock->FSHandle  = SecSmiFlash.FSHandle;
    pSessionBlock->ErrorCode = 0;

    return EFI_SUCCESS;
}

//<AMI_PHDR_START>
//----------------------------------------------------------------------
// Procedure:   LoadFwImage
//
// Description: Routine is called in a loop by the Flash tool. 
//              Depending on the OS environment, Flash tool passes either an entire 
//              Flash Image into SMM buffer or block by block. 
//              E.g AFUDOS could allocate a contiguous buffer for the entire ROM buffer,
//              while certain OSes (Linux) may only allocate limited buffer sizes
//
// Input:       FUNC_BLOCK -> Address, size
//
// Output:      FUNC_BLOCK -> Status
//
// Returns:
//
//----------------------------------------------------------------------
//<AMI_PHDR_END>
EFI_STATUS LoadFwImage(
    IN OUT FUNC_BLOCK   *pFuncBlock
)
{
    if(IsAddressInSmram((EFI_PHYSICAL_ADDRESS)pFuncBlock, sizeof(FUNC_BLOCK)))
        return EFI_DEVICE_ERROR;

    // prevent leaking of the SMM code to the external buffer
    if(IsAddressInSmram((EFI_PHYSICAL_ADDRESS)pFuncBlock->BufAddr, pFuncBlock->BlockSize))
        return EFI_DEVICE_ERROR;

    pFuncBlock->ErrorCode = 1;

    SecSmiFlash.FSHandle = 0; // clear out Hndl. Will be set to valid number in SetFlashMethod
    SecSmiFlash.pFwCapsule = NULL;
    SecSmiFlash.RomLayout = RomLayout; // back to default RomLayout

//TRACE((TRACE_ALWAYS,"SecSMI. LoadImage at %X, size %X\n",(UINT32)pFwCapsuleLowMem + pFuncBlock->BlockAddr, pFuncBlock->BlockSize));

    if(pFwCapsuleLowMem == NULL) 
        return EFI_DEVICE_ERROR;

// assuming the address in 0 based offset in new ROM image
    if((UINT64)((UINT32)pFwCapsuleLowMem + pFuncBlock->BlockAddr + pFuncBlock->BlockSize) >
       (UINT64)((UINT32)pFwCapsuleLowMem + gFwCapMaxSize)
    )
        return EFI_DEVICE_ERROR;

    MemCpy((VOID*)((UINT32)pFwCapsuleLowMem+pFuncBlock->BlockAddr), 
            (UINT8*)pFuncBlock->BufAddr, pFuncBlock->BlockSize);

    pFuncBlock->ErrorCode = (UINT8)MemCmp(
        (VOID*)((UINT32)pFwCapsuleLowMem+pFuncBlock->BlockAddr), 
        (VOID*)pFuncBlock->BufAddr, pFuncBlock->BlockSize);

    pFuncBlock->ErrorCode = 0;

    return EFI_SUCCESS;
}
// End Secured Flash Update API

#if RUNTIME_SECURE_UPDATE_FLOW == 1
// <AMI_PHDR_START>
//----------------------------------------------------------------------------
//
// Name: BeforeSecureUpdate
//
// Description: Verifies if the Update range is protected by Signature
//              1. return Success if flash region is inside unSigned RomArea
//              2. if region is signed - compare its hash with pre-calculated Hash in smm
//                  and return pointer to internal DataBuffer
//
// Input:
//  VOID*       FlashAddress    Pointer to address of a flash 
//
// Output:      Status
//
//--------------------------------------------------------------------------
// <AMI_PHDR_END>
EFI_STATUS BeforeSecureUpdate (
    VOID* FlashAddress, UINTN Size, UINT8 **DataBuffer
)
{
    EFI_STATUS  Status = EFI_SUCCESS;
    ROM_AREA    *Area;
    UINT8       *BuffAddr;
    UINT8       *PageAddr;
    UINT8       HashCounter;
    UINTN       PageSize;
    UINTN       PageCount;
    UINT32      *FSHandl;

    // enforce write protection if RomArea undefined
    if ( RomLayout == NULL )
        Status = EFI_WRITE_PROTECTED;

    for (Area = RomLayout; Area && Area->Size!=0; Area++)
    {
        if(Area->Address == 0) // construct an Address field if not initialized
            Area->Address = (UINT64)((0xFFFFFFFF - FLASH_SIZE) + 1)+Area->Offset;
//TRACE((-1, "RomArea %8X(%8X) + Size %8X = %8X, Attr %X\n",Area->Address,Area->Offset, Area->Size, (UINT64)((UINTN)Area->Address+Area->Size), Area->Attributes));
        if(
            (((UINT64)FlashAddress >= (UINT64)(Area->Address)) && 
             ((UINT64)FlashAddress  < (UINT64)(Area->Address+Area->Size))) 
             ||
            (((UINT64)(Area->Address) >= (UINT64)FlashAddress) && 
             ((UINT64)(Area->Address)  < (UINT64)((UINT64)FlashAddress + Size))) ) 
        {
            if (Area->Attributes & ROM_AREA_FV_SIGNED)
            {
                Status = EFI_WRITE_PROTECTED;
                break;
            }
//TRACE((-1, "\nSignAttr %x(%x)\nRomArea %8X, Size %8X, (%8X)\nFlsAddr %8X, Size %8X, (%8X)\n", Area->Attributes, (Area->Attributes & ROM_AREA_FV_SIGNED),
//        Area->Address, Area->Size, (UINT64)((UINTN)Area->Address+Area->Size), 
//        (UINTN)FlashAddress, Size, (UINT64)((UINTN)FlashAddress+Size)));
        }
    }
//if(Status != EFI_WRITE_PROTECTED) {
//    TRACE((-1, "SpiOffs %8X, Size %8X, (%8X)\n", (0-(UINTN)FlashAddress), Size, (0-(EFI_PHYSICAL_ADDRESS)((UINTN)FlashAddress+Size))));
//}
    if(Status == EFI_WRITE_PROTECTED &&
        (FlUpdatePolicy.FlashUpdate & FlRuntime)
    ){
        // check Verify status by comparing FSHandl with gHashTbl[0]
        // should be unique per Capsule;
        FSHandl = (UINT32*)gHashTbl;
        if(SecSmiFlash.FSHandle == 0 || 
           SecSmiFlash.FSHandle != *FSHandl)
            return Status; // EFI_WRITE_PROTECTED

        PageSize = FLASH_BLOCK_SIZE;
        PageCount=( (UINTN)FlashAddress - Flash4GBMapStart) / PageSize;

        if(SecSmiFlash.pFwCapsule != NULL)
        {
            // Flash Write -> Update ptr to internal Acpi NVS or SMM Buffer
            BuffAddr = (UINT8*)SecSmiFlash.pFwCapsule;
            PageAddr = (UINT8*)((UINTN)BuffAddr + (PageSize * PageCount));
            BuffAddr = (UINT8*)((UINTN)BuffAddr + ((UINTN)FlashAddress - Flash4GBMapStart));

            Status = EFI_SUCCESS;
            HashCounter = 2; // addr may rollover to next flash page
            while(HashCounter-- && PageCount < SEC_FLASH_HASH_TBL_BLOCK_COUNT)
            { 
                // compare calculated block hash with corresponding hash from the Hw Hash Table
                // if no match -> make Size=0 to skip Flash Write Op
                Status = gAmiSig->Hash(gAmiSig, &gEfiHashAlgorithmSha256Guid, 
                    1, (const UINT8**)&PageAddr, (const UINTN*)&PageSize, gHashDB); 
                if(EFI_ERROR(Status) || 
                    MemCmp(gHashDB, SecSmiFlash.HashTbl[PageCount], SHA256_DIGEST_SIZE)
                ){   
//TRACE((-1, "Hash Err! FlashBuff = %8X, Data = %8X, BlockAddr=%x, BlockSize=%x\n", BuffAddr, *((UINT32*)BuffAddr), PageAddr, Size));
                    return EFI_WRITE_PROTECTED;
                }
                // repeat Hash check on next Flash Block if Write Block overlaps the Flash Block boundary
                PageCount++;
                PageAddr = (UINT8*)((UINTN)PageAddr + PageSize);
                if((BuffAddr+Size) <= PageAddr)
                    break;
            }
            // Erase 
            if(DataBuffer != NULL)
                *DataBuffer = BuffAddr;
        }            
    }

    return Status;
}
// <AMI_PHDR_START>
//----------------------------------------------------------------------------
//
// Name: SecureFlashWrite
//
// Description: Allows to write to flash device is Secure Capsule is loaded into memory
//              Function replacing Flash->Write API call
//
// Input:       VOID* FlashAddress, UINTN Size, VOID* DataBuffer
// 
//
// Output:      EFI_SUCCESS
//
//--------------------------------------------------------------------------
// <AMI_PHDR_END>
EFI_STATUS SecureFlashWrite (
    VOID* FlashAddress, UINTN Size, VOID* DataBuffer
)
{
    EFI_STATUS  Status;
    UINT8       *CurrBuff;

    CurrBuff = (UINT8*)DataBuffer;
    Status = BeforeSecureUpdate(FlashAddress, Size, &CurrBuff);
//TRACE((-1, "SecSMIFlash Write %X, BuffAddr=%X(%X) Lock Status=%r\n", FlashAddress, DataBuffer, CurrBuff, Status));
    if(!EFI_ERROR(Status))
        return pFlashWrite(FlashAddress, Size, CurrBuff);

    return Status;
}

// <AMI_PHDR_START>
//----------------------------------------------------------------------------
//
// Name: SecureFlashErase
//
// Description: Allows erase of flash device is Secure Capsule is loaded into memory
//              Function replacing Flash->Erase API call
//
// Input:       NON
// 
//
// Output:      EFI_SUCCESS
//
//--------------------------------------------------------------------------
// <AMI_PHDR_END>
EFI_STATUS SecureFlashErase (
    VOID* FlashAddress, UINTN Size
)
{
    EFI_STATUS  Status;

    Status = BeforeSecureUpdate(FlashAddress, Size, NULL);
//TRACE((-1, "SecSMIFlash Erase %X - %X Lock Status=%r\n", FlashAddress, Size, Status));
    if(!EFI_ERROR(Status)) 
        return pFlashErase(FlashAddress, Size);

    return Status;//EFI_SUCCESS;
}

//**********************************************************************
//<AMI_PHDR_START>
//
// Procedure:  GetFwCapFfs
//
// Description:    Loads binary from RAW section of X firwmare volume
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
GetFwCapFfs (
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
                  NameGuid, //&gFwCapFfsGuid,
                  EFI_SECTION_FREEFORM_SUBTYPE_GUID,//EFI_SECTION_RAW
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

// <AMI_PHDR_START>
//----------------------------------------------------------------------------
//
// Name: GetRomLayout
//
// Description: 
//
// Input:
//  IN EFI_HANDLE               ImageHandle     Image Handle
//  IN EFI_SYSTEM_TABLE         *SystemTable    Pointer to System Table
//
// Output:      EFI_STATUS
//
//--------------------------------------------------------------------------
// <AMI_PHDR_END>
EFI_STATUS GetRomLayout(
    IN EFI_SYSTEM_TABLE    *SystemTable,
    EFI_SMM_BASE_PROTOCOL   *SmmBase,
    OUT ROM_AREA **RomLayout
)
{
    EFI_STATUS Status;
    static EFI_GUID HobListGuid = HOB_LIST_GUID;
    static EFI_GUID AmiRomLayoutHobGuid = AMI_ROM_LAYOUT_HOB_GUID;
    ROM_LAYOUT_HOB *RomLayoutHob;
    UINTN RomLayoutSize=0, Size;
    ROM_AREA *Area;
    APTIO_FW_CAPSULE_HEADER *FwCapHdr;
    UINT8*  pFwCapHdr=NULL;

// 1. Try to locate RomLayout from embedded CapHdr Ffs 
    Status = GetFwCapFfs(&gFwCapFfsGuid, &pFwCapHdr, &Size);
    if(!EFI_ERROR(Status)) 
    {
        // Skip over Section GUID
        FwCapHdr = (APTIO_FW_CAPSULE_HEADER*)pFwCapHdr;
        (UINT8*)FwCapHdr += sizeof (EFI_GUID);
        Size -= sizeof (EFI_GUID);
        *RomLayout = (ROM_AREA *)(UINTN)((UINT32)FwCapHdr+FwCapHdr->RomLayoutOffset);
        RomLayoutSize = sizeof(ROM_AREA);
        for (Area=*RomLayout; Area->Size!=0 && RomLayoutSize<=(Size - FwCapHdr->RomLayoutOffset); Area++)
        {
            RomLayoutSize+=sizeof(ROM_AREA);
        }
//        TRACE((-1, "Get Rom Map from the FwCap FFS at %X(size 0x%X)\nRomLayout offs %X(size 0x%X)\n", FwCapHdr, Size, FwCapHdr->RomLayoutOffset, RomLayoutSize));
        Area=*RomLayout; 
    }
    else
    {
// 2. Backup: Use primary RomLayout from Rom Layout HOB. 
//  This one does not yet report the Rom Hole regions
    //----- Get HobList -------------------------------------
        RomLayoutHob = GetEfiConfigurationTable(SystemTable, &HobListGuid);
        if (RomLayoutHob!=NULL)
        {
    // -------- Get RomLayoutHob ----------------------
            if (!EFI_ERROR( 
                        FindNextHobByGuid(&AmiRomLayoutHobGuid, &RomLayoutHob)
                    ))
            {
                RomLayoutSize =   RomLayoutHob->Header.Header.HobLength
                                  - sizeof(ROM_LAYOUT_HOB);
          
                Area=(ROM_AREA*)((UINT8*)RomLayoutHob+1);
    //TRACE((-1, "Get Default Rom Map from the Hob at %X\n", Area));
            }
        }
    }
    if(RomLayoutSize)
    {
        //---Allocate memory in SMRAM for RomLayout---
        *RomLayout = NULL;
        Status = pSmst->SmmAllocatePool(EfiRuntimeServicesData, RomLayoutSize,(void **)RomLayout);
        if (EFI_ERROR(Status) || *RomLayout == NULL)
            return EFI_NOT_FOUND;

        pBS->CopyMem( *RomLayout, Area, RomLayoutSize);
    
        if(pFwCapHdr)
            pBS->FreePool(pFwCapHdr);

        return EFI_SUCCESS;
    }

    return EFI_NOT_FOUND;
}
#endif //#if RUNTIME_SECURE_UPDATE_FLOW == 1

//<AMI_PHDR_START>
//---------------------------------------------------------------------------
//
// Procedure: IsAddressInSmram
//
// Description: CThis function check if the address is in SMRAM
//
// Input: 
//  Address - the buffer address to be checked.
//  Range   - the buffer length to be checked
//
// Output: 
//  TRUE  this address is in SMRAM.
//  FALSE this address is NOT in SMRAM.
//
//---------------------------------------------------------------------------
//<AMI_PHDR_END>
BOOLEAN IsAddressInSmram (
  IN EFI_PHYSICAL_ADDRESS  Buffer,
  IN UINT64                Length
)
{
  UINTN  Index;
//TRACE((TRACE_ALWAYS,"Addr in SMRAM %X_%X\n",Buffer, Length));
  for (Index = 0; Index < mSmramRangeCount; Index ++) {
    if (((Buffer >= mSmramRanges[Index].CpuStart) && (Buffer < mSmramRanges[Index].CpuStart + mSmramRanges[Index].PhysicalSize)) ||
        ((mSmramRanges[Index].CpuStart >= Buffer) && (mSmramRanges[Index].CpuStart < Buffer + Length))) {
//TRACE((TRACE_ALWAYS,"TRUE\n"));
      return TRUE;
    }
  }
//TRACE((TRACE_ALWAYS,"FALSE\n"));
  return FALSE;
}

// !!! do not install if OFBD SecFlash is installed 
#if INSTALL_SECURE_FLASH_SW_SMI_HNDL == 1
//<AMI_PHDR_START>
//----------------------------------------------------------------------
// Procedure:   SecSMIFlashSMIHandler
//
// Description:
//
// Input:
//
// Output:
//
// Returns:
//
//----------------------------------------------------------------------
//<AMI_PHDR_END>
VOID SecSMIFlashSMIHandler (
    IN    EFI_HANDLE                    DispatchHandle,
    IN    EFI_SMM_SW_DISPATCH_CONTEXT    *DispatchContext
)
{
    EFI_SMM_CPU_SAVE_STATE    *pCpuSaveState;
    SW_SMI_CPU_TRIGGER        *SwSmiCpuTrigger;
    UINT8        Data;
    UINT64       pCommBuff;
    UINT32       HighBufferAddress = 0;
    UINT32       LowBufferAddress = 0;
    UINTN        i;
    UINTN        Cpu = pSmst->CurrentlyExecutingCpu - 1;
    
    for (i = 0; i < pSmst->NumberOfTableEntries; ++i) {
        if (guidcmp(&pSmst->SmmConfigurationTable[i].VendorGuid,&gSwSmiCpuTriggerGuid) == 0) {
            break;
        }
    }
    
    //If found table, check for the CPU that caused the software Smi.
    if (i != pSmst->NumberOfTableEntries) {
        SwSmiCpuTrigger = pSmst->SmmConfigurationTable[i].VendorTable;
        Cpu = SwSmiCpuTrigger->Cpu;
    }

    //
    // Found Invalid CPU number, return 
    //
    if(Cpu == (UINTN) -1) {
        return;
    }

    Data    = (UINT8)DispatchContext->SwSmiInputValue;
    
    pCpuSaveState        = pSmst->CpuSaveState;
    HighBufferAddress    = pCpuSaveState[Cpu].Ia32SaveState.ECX;
    LowBufferAddress     = pCpuSaveState[Cpu].Ia32SaveState.EBX;
    pCommBuff            = HighBufferAddress;
    pCommBuff            = Shl64(pCommBuff, 32);
    pCommBuff            += LowBufferAddress;

//TRACE((-1, "Sec SW SMI Flash Hook == 0x%x\n", Data));

    switch(Data)
    {
        case SecSMIflash_Load:             // 0x1d Send Flash Block to memory 
            LoadFwImage((FUNC_BLOCK *)pCommBuff);
            break;

        case SecSMIflash_GetPolicy:        // 0x1e Get Fl Upd Policy 
            GetFlUpdPolicy((FLASH_POLICY_INFO_BLOCK *)pCommBuff);
            break;
        
        case SecSMIflash_SetFlash:        // 0x1f Set Flash method
            SetFlUpdMethod((FUNC_FLASH_SESSION_BLOCK *)pCommBuff);
            break;
    }
}
#endif
//<AMI_PHDR_START>
//----------------------------------------------------------------------
// Procedure:   InSmmFunction
//
// Description: 
//
// Input:   
//
// Output: 
//
// Returns: 
//
//----------------------------------------------------------------------
//<AMI_PHDR_END>
EFI_STATUS InSmmFunction(EFI_HANDLE ImageHandle, EFI_SYSTEM_TABLE *SystemTable)
{
#if INSTALL_SECURE_FLASH_SW_SMI_HNDL == 1
    EFI_SMM_SW_DISPATCH_PROTOCOL    *pSwDispatch = NULL;
    EFI_SMM_SW_DISPATCH_CONTEXT     SwContext;
    UINTN                           Index;
#endif
#if FWCAPSULE_RECOVERY_SUPPORT == 1
    EFI_SMM_SX_DISPATCH_CONTEXT      SxDispatchContext;
    EFI_SMM_SX_DISPATCH_PROTOCOL    *SxDispatchProtocol;
#endif

    EFI_HANDLE              Handle = NULL;
    EFI_HANDLE              DummyHandle = NULL;
    EFI_STATUS              Status;

    UINTN   Size = 0;
    UINT8   MinSMIPort = SecSMIflash_Load;    //0x1d
    //UINT8   MinSMIPort = SecSMIflash_GetPolicy; //0x1e;
    UINT8   MaxSMIPort = SecSMIflash_SetFlash; //0x1f;

//PI 1.1 ++
#if defined(PI_SPECIFICATION_VERSION)&&(PI_SPECIFICATION_VERSION>=0x0001000A)
    EFI_SMM_ACCESS2_PROTOCOL     *SmmAccess;
#else
    EFI_SMM_ACCESS_PROTOCOL      *SmmAccess;
#endif

    InitAmiSmmLib( ImageHandle, SystemTable );

    Status = pBS->LocateProtocol(&gAmiSmmDigitalSignatureProtocolGuid, NULL, &gAmiSig);
    ASSERT_EFI_ERROR (Status);
    if (EFI_ERROR(Status)) return Status;

// Test if Root Platform Key is available,else - don't install Flash Upd security measures.
    gpPubKeyHndl.Blob = NULL;
    gpPubKeyHndl.BlobSize = 0;
    Status = gAmiSig->GetKey(gAmiSig, &gpPubKeyHndl, &gPRKeyGuid, gpPubKeyHndl.BlobSize, 0);
//TRACE((TRACE_ALWAYS,"GetKey %r (%x, %d bytes)\n",Status, gpPubKeyHndl.Blob,gpPubKeyHndl.BlobSize));
    if (EFI_ERROR(Status) || gpPubKeyHndl.Blob == NULL) {
        if(Status == EFI_BUFFER_TOO_SMALL) 
            return EFI_SUCCESS;
        return Status;
    }
    //
    // Get SMRAM information
    //
//PI 1.1 ++
#if defined(PI_SPECIFICATION_VERSION)&&(PI_SPECIFICATION_VERSION>=0x0001000A)
    Status = pBS->LocateProtocol (&gEfiSmmAccess2ProtocolGuid, NULL, (VOID **)&SmmAccess);
    ASSERT_EFI_ERROR (Status);
    if (EFI_ERROR(Status)) return Status;
#else
    Status = pBS->LocateProtocol(&gEfiSmmAccessProtocolGuid, NULL, &SmmAccess);
    ASSERT_EFI_ERROR(Status);
    if (EFI_ERROR(Status)) return Status;
#endif
    Size = 0;
    Status = SmmAccess->GetCapabilities (SmmAccess, &Size, NULL);
    ASSERT (Status == EFI_BUFFER_TOO_SMALL);
    if (Size==0) return EFI_NOT_FOUND;
    Status = pSmst->SmmAllocatePool (EfiRuntimeServicesData,Size,(VOID **)&mSmramRanges);
    ASSERT_EFI_ERROR (Status);
    if (EFI_ERROR(Status)) return Status;
    Status = SmmAccess->GetCapabilities (SmmAccess, &Size, mSmramRanges);
    if (EFI_ERROR(Status)) return Status;
    mSmramRangeCount = Size / sizeof (EFI_SMRAM_DESCRIPTOR);
    //
    // Allocate scratch buffer to hold entire Signed BIOS image for Secure Capsule and Runtime Flash Updates
    // AFU would have to execute a sequence of SW SMI calls to push entire BIOS image to SMM
    //
    //NEW_BIOS_MEM_ALLOC == 2 AFU will allocate a buffer and provide pointer via SET_FLASH_METHOD API call. 
    //
#if NEW_BIOS_MEM_ALLOC == 0
    //
    // Alternatively the buffer may be reserved within the SMM TSEG memory 
    //
    Status = pSmmBase->SmmAllocatePool(pSmmBase, EfiRuntimeServicesData, gFwCapMaxSize, (void**)&pFwCapsuleLowMem);

//TRACE((TRACE_ALWAYS,"SecSmiFlash: Alloc 0x%X bytes in SMM, %r\n",gRomFileSize, Status));
#else
#if NEW_BIOS_MEM_ALLOC == 1
    //
    // The buffer allocated in OS reserved memory below 4GB
    //
//    Status = pST->BootServices->AllocatePool(EfiReservedMemoryType, gRomFileSize, &pFwCapsuleLowMem);
    pFwCapsuleLowMem = (UINT32*)0xFFFFFFFF;
    Status = pST->BootServices->AllocatePages(AllocateMaxAddress, EfiReservedMemoryType, 
             EFI_SIZE_TO_PAGES(gFwCapMaxSize), (EFI_PHYSICAL_ADDRESS*)&pFwCapsuleLowMem);
//TRACE((TRACE_ALWAYS,"SecSmiFlash: AllocatePages=%X,(0x%x) %r\n",pFwCapsuleLowMem,gRomFileSize,  Status));
#endif
#endif
    ASSERT_EFI_ERROR(Status);
    if (EFI_ERROR(Status)) return Status;
#if NEW_BIOS_MEM_ALLOC < 2
    MemSet((void*)pFwCapsuleLowMem, gFwCapMaxSize, 0 );
#endif
    //
    // Allocate space to hold a Hash table for all Flash blocks
    //
    Size = SEC_FLASH_HASH_TBL_SIZE;
    Status = pSmmBase->SmmAllocatePool(pSmmBase, EfiRuntimeServicesData, Size, (void**)&gHashTbl);
    if (EFI_ERROR(Status)) return Status;
    MemSet((void*)gHashTbl, Size, 0xdb );

#if FWCAPSULE_RECOVERY_SUPPORT == 0
    FlUpdatePolicy.FlashUpdate &=~FlCapsule;
    FlUpdatePolicy.BBUpdate &=~FlCapsule;
#else    
    //
    // Reserve pool in smm runtime memory for capsule's mailbox list
    //
    Size = 4*sizeof(EFI_CAPSULE_BLOCK_DESCRIPTOR) + sizeof(EFI_CAPSULE_HEADER); // (4*16)+28
    Status = pSmmBase->SmmAllocatePool(pSmmBase, EfiRuntimeServicesData, Size, (void**)&gpEfiCapsuleHdr);
//TRACE((TRACE_ALWAYS,"Mailbox: AllocatePages=%X,(0x%x) %r\n",gpEfiCapsuleHdr,Size,  Status));
    if (EFI_ERROR(Status)) return Status;
    MemSet((void*)gpEfiCapsuleHdr, Size, 0 );

    //
    // Install callback on S5 Sleep Type SMI. Needed to transition to S3 if Capsule's mailbox ie pending
    // Locate the Sx Dispatch Protocol
    //
    // gEfiSmmSxDispatch2ProtocolGuid
    Status = pBS->LocateProtocol (&gEfiSmmSxDispatchProtocolGuid,NULL,&SxDispatchProtocol);
    ASSERT_EFI_ERROR (Status);  
    if (EFI_ERROR(Status)) return Status;
    //
    // Register the callback for S5 entry
    //
    if (SxDispatchProtocol && SupportUpdateCapsuleReset()) {
      SxDispatchContext.Type  = SxS5;
      SxDispatchContext.Phase = SxEntry;
      Status = SxDispatchProtocol->Register (SxDispatchProtocol,SmiS5CapsuleCallback,&SxDispatchContext,&Handle);
      ASSERT_EFI_ERROR (Status);  
    }
    if (EFI_ERROR(Status)) goto Done;
#endif
#if RUNTIME_SECURE_UPDATE_FLOW == 1
/*
AFU For Rom Holes in Runtime/Capsule upd
    1. Read full ROM image to ROM buffer
    2. Merge Rom Hole from input file to ROM buffer
    3. call "LoadImage" for full BIOS
    3. call "SetFlash" with Runtime update (NVRAM block should be unsigned!!!)
    4. calls to upd  Rom hole -erase,write should pass
*/
    Status = GetRomLayout(SystemTable, pSmmBase, &RomLayout);
//TRACE((TRACE_ALWAYS,"SecSmiFlash: Get Rom Layout ptr=%X, %r\n",RomLayout, Status));
    // Rom Layout HOB may not be found in Recovery mode and if FW does not include built in FwCapsule Hdr file
//    if (EFI_ERROR(Status)) goto Done;
    //
    // Trap the original Flash Driver API calls to enforce 
    // Flash Write protection in SMM at the driver API level
    //
    Status = pBS->LocateProtocol(&gFlashSmmProtocolGuid, NULL, &Flash);
//TRACE((TRACE_ALWAYS,"SecSmiFlash: Flash Protocol Fixup %X->%X\n",Flash->Write,SecureFlashWrite));
    if (EFI_ERROR(Status)) goto Done;

    // preserve org Flash API
    pFlashWrite = Flash->Write; 
    pFlashErase = Flash->Erase;
    // replace with local functions 
    Flash->Erase = SecureFlashErase;
    Flash->Write = SecureFlashWrite;
    // Calculate the flash mapping start address. This is calculated
    // as follows:
    //  1. Find the total size of the flash (FLASH_BLOCK_SIZE * NUMBER_OF_BLOCKS)
    //  2. Subtract the total flash size from 4GB
    Flash4GBMapStart = 0xFFFFFFFF - (FLASH_BLOCK_SIZE * NUMBER_OF_BLOCKS);
    Flash4GBMapStart ++;    
#endif
    //
    // Install Secure SMI Flash Protocol 
    //
    SecSmiFlash.pFwCapsule = pFwCapsuleLowMem;
    SecSmiFlash.HashTbl = gHashTbl;
    SecSmiFlash.RomLayout = RomLayout;
//    SecSmiFlash.FSHandle = 0;
    Status = pBS->InstallMultipleProtocolInterfaces(
        &DummyHandle,
        &gSecureSMIFlashProtocolGuid,&SecSmiFlash,
        NULL
    );
    ASSERT_EFI_ERROR(Status);
    if (EFI_ERROR(Status)) return Status;

    //    
    // Install SW SMI callbacks for 3 SecSMI Flash functions
    // !!! do not install if OFBD SecFlash is installed 
    //
#if INSTALL_SECURE_FLASH_SW_SMI_HNDL == 1
    Status = pBS->LocateProtocol(&gEfiSmmSwDispatchProtocolGuid, NULL, &pSwDispatch);
    ASSERT_EFI_ERROR(Status);
    if (EFI_ERROR(Status)) return EFI_SUCCESS;

    for(Index=MinSMIPort;Index<=MaxSMIPort;Index++)
    {
        SwContext.SwSmiInputValue    = Index;
        Status    = pSwDispatch->Register(pSwDispatch, SecSMIFlashSMIHandler, &SwContext, &Handle);
        ASSERT_EFI_ERROR(Status);
        if (EFI_ERROR(Status)) break;
        //If any errors,unregister any registered SwSMI by this driver.
        //If error, and driver is unloaded, then a serious problem would exist.
    }
#endif
Done:
    return EFI_SUCCESS;
}

//<AMI_PHDR_START>
//----------------------------------------------------------------------
// Procedure:   SecSMIFlashDriverEntryPoint
//
// Description: Secure SMI Flash driver init 
//
// Input:   
//
// Output: 
//
// Returns: 
//
//----------------------------------------------------------------------
//<AMI_PHDR_END>
EFI_STATUS SecSMIFlashDriverEntryPoint(
    IN EFI_HANDLE        ImageHandle,
    IN EFI_SYSTEM_TABLE    *SystemTable
)
{
    InitAmiLib(ImageHandle, SystemTable);
    return InitSmmHandler(ImageHandle, SystemTable, InSmmFunction, NULL);    
}

//**********************************************************************
//**********************************************************************
//**                                                                  **
//**        (C)Copyright 1985-2014, American Megatrends, Inc.         **
//**                                                                  **
//**                       All Rights Reserved.                       **
//**                                                                  **
//**        5555 Oakbrook Pkwy, Suite 200, Norcross, GA 30093         **
//**                                                                  **
//**                       Phone: (770)-246-8600                      **
//**                                                                  **
//**********************************************************************
//**********************************************************************
