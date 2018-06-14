//**********************************************************************
//**********************************************************************
//**                                                                  **
//**        (C)Copyright 1985-2009, American Megatrends, Inc.         **
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
// $Header: /Alaska/SOURCE/Modules/SMIFlash/SMIFlash.c 52    3/23/16 3:58a Calvinchen $
//
// $Revision: 52 $
//
// $Date: 3/23/16 3:58a $
//**********************************************************************
// Revision History
// ----------------
// $Log: /Alaska/SOURCE/Modules/SMIFlash/SMIFlash.c $
// 
// 52    3/23/16 3:58a Calvinchen
// [TAG]  		EIP262060
// [Category]  	Bug Fix
// [Severity]  	Important
// [Symptom]  	Buffer Overflow Vulnerability
// [RootCause]  	SmiFlash interface security vulnerability if the buffer
// address is starting before/less SMM Base and the buffer length is
// larger than SMM size.
// [Solution]  	Adapted the CheckAddressRange function as the
// "AmiValidateMemoryBuffer" function of the AptioV.
// [Files]  		SMIFlash.c
// 
// 51    1/08/16 3:59a Calvinchen
// [TAG]  		EIP249791
// [Category]  	Bug Fix
// [Severity]  	Important
// [Symptom]  	SMM Buffer Validation - additional vulnerability
// [RootCause]  	BufAddr is an embedded input pointer which has not been
// validated to be outside of SMRAM and is being used as a destination
// buffer for read/write operation from flash. 
// 
// [Solution]  	Validate BufAddr to must be outside of SMRAM. 
// [Files]  		SMIFlash.c
// SMIFlash.chm
// SMIFlash.cif
// 
// 50    6/21/13 4:32a Tristinchou
// [TAG]  		EIP125801
// [Category]  	Improvement
// [Description]  	SMI Flash handler could be used to set value in SMRAM.
// Check the adrress before use the function.
// [Files]  		SMIFlash.c
// 
// 49    11/02/12 7:13a Calvinchen
// [TAG]  		EIP64328
// [Category]  	Improvement
// [Description]  	Improvement: 
//  1. (EIP64328) Update modules to be compliant with PI 1.2 and UEFI
// 2.3.1 specifications. 
// BugFix: 
//  1. (EIP100950) Fix the attribute of Win8 Debug Variable been changed
// after restored. 
//  2. (EIP98199) The #### in Boot#### should be upper case. 
// [Files]  		SMIFlash.mak
// SMIFlash.dxs
// SMIFlash.c
// SMIFlash.chm
// SMIFlashLinks.c
// SMIFlashDxe.dxs
// SMIFlash.cif
// 
// 48    3/06/12 2:40a Klzhan
// NVRAM backup address will not updated.
// 
// 47    1/16/12 2:29a Calvinchen
// [TAG]  		EIPNone
// [Category]  	Improvement
// [Description]  	Updated for Secure Update.
// 
// 46    5/17/11 3:16a Klzhan
// Report BIOS project tag length to AFU.
// 
// 45    3/23/11 4:44a Calvinchen
// [TAG]  		EIP53067
// [Category]  	Improvement
// [Description]  	Modified for OEM Secure BIOS Update Requirements.
// [Files]  		SMIFlash.sdl
// SMIFlash.mak
// SMIFlash.dxs
// SMIFlash.c
// SMIFlash.chm
// SMIFlashLinks.c
// SMIFlash.cif
// 
// 44    1/21/11 4:48a Klzhan
// Improvement : Check CPU number in SMIHandler
// 
// 43    12/14/10 4:16a Klzhan
// Move Locate USB Protocol to SMIFlashLinks.c.
// 
// 42    12/14/10 1:13a Klzhan
// Improvement : Move ELinks to SMIFlashLinks.c.
// 
// 41    10/20/10 2:21a Klzhan
// Remove ASFU related codes, ASFU will implement with OFBD module.
// 
// 40    10/19/10 6:58a Klzhan
// Improvement : Support Secure Flash Update.
// EIP : 46069
// 
// 39    8/10/10 2:40a Klzhan
// Improvement : Replace Memory Read by SPIRead when checking flash data.
// 
// 38    6/15/10 3:12a Klzhan
// Improvement: Add Elink to modify GetFlashInfo.
// 
// 37    4/14/10 5:43a Klzhan
// BugFix : Fix compile error when FAULT_TOLERANT_NVRAM_UPDATE is off.
// 
// 36    4/13/10 4:26a Klzhan
// Improvement : Report NVRam backup as NVRam block.
// 
// 35    4/12/10 7:45a Klzhan
// Improvement : When FAULT_TOLERANT_NVRAM_UPDATE is on and System working
// at NVRam backup address, system works fine on next boot.
// 
// 34    4/12/10 3:37a Klzhan
// Improvement : Add E-Link to Enable/Disable USB KBD.
// BugFix : Correct USB driver verion control.
// 
// 33    4/08/10 2:22a Rameshr
// Usb changes added based on AMIUSB release version.
// 
// 32    4/07/10 1:53a Rameshr
// USB K/B and USB M/S should be stopped during flashing BIOS.
// EIP 37130
// 
// 31    3/26/10 5:25a Rameshr
// After flashupdate, Silent boot setup option is not restored to default
// value
// EIP 36617
// 
// 30    3/02/10 2:59a Klzhan
// Improvement : If Setup PassWord Length is changed, Password will not be
// restore when update NVRam region.
// 
// 29    3/02/10 12:43a Klzhan
// Improvement : Disable Power Button when flash ROM image.(EIP35662)
// 
// 28    2/26/10 2:31a Klzhan
// 1. Improvement : Restore "Windows Boot Manager" for EFI OS(EIP 32339)
// 
// 27    12/21/09 4:39a Klzhan
// Improvement : Updated for Aptio Source Enhancement.
//
// 26    11/26/09 6:03a Klzhan
// Improvement : Add Flash Chip info.EIP 30081
//
// 25    8/25/09 8:22a Klzhan
// Improvement: Support Flash ME FW.
//
// 24    5/22/09 8:19p Felixp
// SmiFlash module is updated to replace Flash library calls with the
// calls to new Core 4.6.3.6 Flash Protocol .
//
// 23    4/03/09 11:28a Fredericko
// Reverting changes for EIP 18818. causing Afu flash error.
//
// 22    3/05/09 1:17p Felixp
//  - Bug fix. EIP 17632.
//   Flash Blocks that do not belong to FV_BB, FV_MAIN, and FV_NVRAM
//   have been reported as boot block.
//   The SmiFlash.c is updated to report these blocks as non critical
// blocks.
//   The SmiFlash.h header is updated to define non critical block type
// (NC_BLOCK ).
//  - Headers updated.
//
// 21    2/02/09 6:46p Fredericko
// Changes for EIP 18819: Using FlashRead to read from flash part. Changed
// SMIFLASH_RRE_UPDATE_LIST to SMIFLASH_PRE_UPDATE_LIST
//
// 19    1/29/09 7:33p Fredericko
// Added code to account for functions (ELinked)  that need to run before
// we program flash and after we program flash. EIP 18819
//
// 18    1/13/09 4:36p Fredericko
// EIP18723: Increase the size of Index (to UINT16) variable for case
// where number of blocks is more than 255.
//
// 17    3/07/08 11:41a Rameshraju
// Readflash failed for 1.5Mb flash size
//
// 16    8/21/07 3:39p Pats
// Removed calculations for sizeof(AMITSESETUP)
//
// 15    8/17/07 4:37p Pats
// Fixed sizeof problem.
//
// 14    8/16/07 6:12p Pats
// Sizeof was returning wrong size for AMITSESETUP.
//
// 13    8/16/07 10:54a Pats
// Fixed problem with setvariable call in password preservation path.
//
// 12    8/15/07 7:06p Pats
// Modified to support preservation of passwords through flashing.
//
// 11    1/24/07 1:42p Felixp
// Erase/Programming code changed to use low level flash routines because
// AFU sends write requests, for a chunks of data smaller then the flash
// block.
//
// 10    12/29/06 3:04p Felixp
// 1. Updated to use new Flash Interface.
// 2. Embedded Controller support added.
//
// 9     3/24/06 7:57p Felixp
//
// 7     11/11/05 11:46a Markw
// Renamed IntallSmmHandler to InitSmmHandler because of build errors
// because another driver used InstallSmmHandler.
//
// 6     11/09/05 3:09p Yakovlevs
// InSmmFunction() "not all controls return a value"  compiler warning
// fixed
//
// 5     11/08/05 6:05p Markw
// Using libary function InstallSmiHandler.
//
// 4     7/12/05 11:19a Markw
// Add code to detect which CPU is executing.
//
// 3     5/02/05 6:42p Markw
// Added Eswar's updates.
//
// 2     5/02/05 6:25p Markw
//
// 1     4/05/05 3:47p Sivagarn
// Initial Checkin
//
//**********************************************************************
//<AMI_FHDR_START>
//
// Name:    SMIFlash.c
//
// Description: SMIFlash Driver.
//
//<AMI_FHDR_END>
//**********************************************************************
#include <AmiDxeLib.h>
#include <Token.h>
#include <Protocol\SmiFlash.h>
#if PI_SPECIFICATION_VERSION >= 0x1000A
#include <Protocol\SmmCpu.h>
#include <Protocol\SmmBase2.h>
#include <Protocol\SmmSwDispatch2.h>
#define RETURN(status) {return status;}
#else
#include <Protocol\SmmBase.h>
#include <Protocol\SmmSwDispatch.h>
#define RETURN(status) {return ;}
#endif
#include <Protocol\DevicePath.h>
#include <Protocol\LoadedImage.h>
#include <Protocol\FlashProtocol.h>
#include <Flash.h>
#include <AmiSmm.h>
#include <Setup.h>
#include <AmiHobs.h>
#if AMIUSB_SUPPORT == 1
#if (((USB_DRIVER_MAJOR_VER*100 ) + (USB_DRIVER_MINOR_VER*10) + (USB_DRIVER_BUILD_VER)) >= 891)
#include <Protocol\AmiUsbController.h>
#endif
#endif

//----------------------------------------------------------------------
// component MACROs
#define FLASH_EMPTY_BYTE (UINT8)(-FLASH_ERASE_POLARITY)
#define STR(a) CONVERT_TO_STRING(a)
//----------------------------------------------------------------------
// Module defined global variables

//----------------------------------------------------------------------
// Module specific global variable
EFI_GUID gSwSmiCpuTriggerGuid = SW_SMI_CPU_TRIGGER_GUID;
#if PI_SPECIFICATION_VERSION >= 0x1000A
EFI_GUID gEfiSmmSwDispatchProtocolGuid = EFI_SMM_SW_DISPATCH2_PROTOCOL_GUID;
EFI_GUID gEfiSmmBase2ProtocolGuid = EFI_SMM_BASE2_PROTOCOL_GUID;
EFI_GUID gEfiSmmCpuProtocolGuid = EFI_SMM_CPU_PROTOCOL_GUID;
EFI_SMM_BASE2_PROTOCOL          *gSmmBase2;
EFI_SMM_CPU_PROTOCOL            *gSmmCpu;
#else
EFI_GUID gEfiSmmSwDispatchProtocolGuid = EFI_SMM_SW_DISPATCH_PROTOCOL_GUID;
#endif
EFI_GUID gEfiSmiFlashProtocolGuid = EFI_SMI_FLASH_GUID;


// oem flash write enable/disable list creation code must be in this order
typedef VOID (SMIFLASH_UPDATE) (VOID);
extern SMIFLASH_UPDATE SMIFLASH_PRE_UPDATE_LIST EndOfSMIFlashList;
extern SMIFLASH_UPDATE SMIFLASH_END_UPDATE_LIST EndOfSMIFlashList;
SMIFLASH_UPDATE* SMIFlashPreUpdate[] = {SMIFLASH_PRE_UPDATE_LIST NULL};
SMIFLASH_UPDATE* SMIFlashEndUpdate[] = {SMIFLASH_END_UPDATE_LIST NULL};
typedef VOID (SMIFLASH_PRE_HANDLER) (UINT8 Date, UINT64 pInfoBlock);
typedef VOID (SMIFLASH_END_HANDLER) (UINT8 Date, UINT64 pInfoBlock);
extern SMIFLASH_PRE_HANDLER SMIFLASH_PRE_HANDLER_LIST EndOfPreHandlerList;
extern SMIFLASH_END_HANDLER SMIFLASH_END_HANDLER_LIST EndOfEndHandlerList;
SMIFLASH_PRE_HANDLER* SMIFlashPreHandler[] = {SMIFLASH_PRE_HANDLER_LIST NULL};
SMIFLASH_END_HANDLER* SMIFlashEndHandler[] = {SMIFLASH_END_HANDLER_LIST NULL};

typedef VOID (SMIFLASH_FUNCTION) (VOID);
extern SMIFLASH_FUNCTION SMIFLASH_IN_SMM_LIST EndOfInSmmList;
SMIFLASH_FUNCTION* SMIFlashInSmm[] = {SMIFLASH_IN_SMM_LIST NULL};
extern SMIFLASH_FUNCTION SMIFLASH_NOT_IN_SMM_LIST EndOfNotInSmmList;
SMIFLASH_FUNCTION* SMIFlashNotInSmm[] = {SMIFLASH_NOT_IN_SMM_LIST NULL};

FLASH_PROTOCOL *Flash = NULL;
SMM_HOB        gSmmHob;
#ifdef FLASH_PART_STRING_LENGTH
VOID GetFlashPartInfomation(UINT8 *pBlockAddress, UINT8 *Buffer);
#endif
//----------------------------------------------------------------------
// externally defined variables

//----------------------------------------------------------------------
// Function definitions
EFI_STATUS
GetFlashInfo(
    IN OUT INFO_BLOCK   *pInfoBlock
);
EFI_STATUS EnableFlashWrite(
    IN OUT FUNC_BLOCK   *pFuncBlock
);
EFI_STATUS DisableFlashWrite(
    IN OUT FUNC_BLOCK   *pFuncBlock
);
EFI_STATUS ReadFlash(
    IN OUT FUNC_BLOCK   *pFuncBlock
);
EFI_STATUS WriteFlash(
    IN OUT FUNC_BLOCK   *pFuncBlock
);
EFI_STATUS EraseFlash(
    IN OUT FUNC_BLOCK   *pFuncBlock
);
EFI_SMI_FLASH_PROTOCOL  SmiFlash = {
    GetFlashInfo,
    EnableFlashWrite,
    DisableFlashWrite,
    ReadFlash,
    WriteFlash,
    EraseFlash,
    FLASH_SIZE
};
//<AMI_PHDR_START>
//---------------------------------------------------------------------------
//
// Procedure: CheckAddressRange
//
// Description: Check address range to avoid TSEG area.
//
// Input: 
//  Address - starting address
//  Range   - length of the area
//
// Output: 
//  EFI_SUCCESS         - Access granted
//  EFI_ACCESS_DENIED   - Access denied!
//
//---------------------------------------------------------------------------
//<AMI_PHDR_END>

EFI_STATUS CheckAddressRange( IN UINT8 *Address, IN UINTN Range )
{
    // Check the size and range
	if (((EFI_PHYSICAL_ADDRESS)Address + Range) < (EFI_PHYSICAL_ADDRESS)Address) 
	    return EFI_INVALID_PARAMETER;   // overflow
	    
    if (((EFI_PHYSICAL_ADDRESS)Address >= gSmmHob.Tseg) && \
        ((EFI_PHYSICAL_ADDRESS)Address < (gSmmHob.Tseg + gSmmHob.TsegLength)))
        return EFI_ACCESS_DENIED;       // Buffer starts in SMRAM

    if (((EFI_PHYSICAL_ADDRESS)Address < gSmmHob.Tseg) && \
        (((EFI_PHYSICAL_ADDRESS)Address + Range) > gSmmHob.Tseg)) 
        return EFI_ACCESS_DENIED;       // Buffer overlaps with SMRAM

    return EFI_SUCCESS;
}
//<AMI_PHDR_START>
//----------------------------------------------------------------------
// Procedure:   GetFlashInfo
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
EFI_STATUS
GetFlashInfo(
    IN OUT INFO_BLOCK   *pInfoBlock
)
{
    EFI_STATUS      Status = EFI_SUCCESS;
    UINT32          BuffLen = 0;
    UINT64          BlkOff;
    BLOCK_DESC      *pBlock;
    UINT16          Index;
    UINT32          Add;
    UINT32          Flash4GBMapStart;
    UINT16          NumBlocks, MainStart, MainEnd,
                    NVStart, NVEnd, BBStart, BBEnd;
    UINT16          LastNcb = 0xFFFF;
    UINT8           NcbType = NC_BLOCK;
#if EC_FIRMWARE_UPDATE_INTERFACE_SUPPORT && SMI_FLASH_INTERFACE_VERSION > 10
    UINT16          ECStart, ECEnd;
#endif
#ifdef FAULT_TOLERANT_NVRAM_UPDATE
#if FAULT_TOLERANT_NVRAM_UPDATE
    UINT16          NVBackupStart, NVBackupEnd;
#endif
#endif

    BuffLen = pInfoBlock->Length;       // Total buffer length
    pInfoBlock->Version = SMI_FLASH_INTERFACE_VERSION;
    pInfoBlock->Implemented = 0;
#if SMI_FLASH_INTERFACE_VERSION > 10
#if EC_FIRMWARE_UPDATE_INTERFACE_SUPPORT
    pInfoBlock->ECVersionOffset = EC_VERSION_OFFSET;
    pInfoBlock->ECVersionMask = EC_VERSION_MASK;
#else
    pInfoBlock->ECVersionOffset = 0;
    pInfoBlock->ECVersionMask = 0;
#endif
#endif
    
    // Reduce number of bytes used for header information
    BuffLen -= EFI_FIELD_OFFSET( INFO_BLOCK, Blocks);
    
    // Get the total block count
    pInfoBlock->TotalBlocks = NumBlocks = NUMBER_OF_BLOCKS;
    
    // Calculate the flash mapping start address. This is calculated
    // as follows:
    //  1. Find the total size of the flash (FLASH_BLOCK_SIZE *
    //      pInfoBlock->TotalBlocks)
    //  2. Subtract the total flash size from 4GB
    Flash4GBMapStart = 0xFFFFFFFF - (FLASH_BLOCK_SIZE * NumBlocks);
    Flash4GBMapStart ++;
    
    // Fill the flash region start & end values
    BBStart = (FV_BB_BASE - Flash4GBMapStart) / FLASH_BLOCK_SIZE;
    BBEnd = BBStart + FV_BB_BLOCKS - 1;
    
    MainStart = (FV_MAIN_BASE - Flash4GBMapStart) / FLASH_BLOCK_SIZE;
    MainEnd = MainStart + FV_MAIN_BLOCKS - 1;
    
    NVStart = (NVRAM_ADDRESS - Flash4GBMapStart) / FLASH_BLOCK_SIZE;
    NVEnd = NVStart + NVRAM_BLOCKS - 1;

#ifdef FAULT_TOLERANT_NVRAM_UPDATE
#if FAULT_TOLERANT_NVRAM_UPDATE
    NVBackupStart = (NVRAM_BACKUP_ADDRESS - Flash4GBMapStart) / FLASH_BLOCK_SIZE;
    NVBackupEnd = NVBackupStart + NVRAM_BLOCKS - 1;
#endif
#endif

#if EC_FIRMWARE_UPDATE_INTERFACE_SUPPORT && SMI_FLASH_INTERFACE_VERSION > 10
    ECStart = (EC_BASE - Flash4GBMapStart) / FLASH_BLOCK_SIZE;
    ECEnd = ECStart + EC_BLOCKS - 1;
#endif
    
    BlkOff = (UINT64)&pInfoBlock->Blocks;
    
    // Chek whether we have enough buffer space
    if (BuffLen < (sizeof (BLOCK_DESC) * NumBlocks)) {
        pInfoBlock->Implemented = 1;
        return Status;
    }
    
    for (Index = 0; Index < NumBlocks; Index++) {
    
        pBlock = (BLOCK_DESC *)BlkOff;
        Add = Index * FLASH_BLOCK_SIZE;
        
        pBlock->StartAddress = Add;
        Add |= Flash4GBMapStart;
        pBlock->BlockSize = FLASH_BLOCK_SIZE;
        
        if ((Index >= MainStart) && (Index <= MainEnd))
            pBlock->Type = MAIN_BLOCK;
        else if ((Index >= NVStart) && (Index <= NVEnd))
            pBlock->Type = NV_BLOCK;
        else if ((Index >= BBStart) && (Index <= BBEnd))
            pBlock->Type = BOOT_BLOCK;
#ifdef FAULT_TOLERANT_NVRAM_UPDATE
#if FAULT_TOLERANT_NVRAM_UPDATE
        else if ((Index >= NVBackupStart) && (Index <= NVBackupEnd))
        {
            pBlock->Type = NVB_BLOCK;
        }
#endif
#endif
#if EC_FIRMWARE_UPDATE_INTERFACE_SUPPORT && SMI_FLASH_INTERFACE_VERSION > 10
        else if ((Index >= ECStart) && (Index <= ECEnd))
            pBlock->Type = EC_BLOCK;
#endif
        else {
            if (LastNcb+1 != Index) NcbType++;
            
            pBlock->Type = NcbType;
            LastNcb=Index;
        }
        BlkOff += sizeof (BLOCK_DESC);
    }

    // Info AFU Project Tag length.
    if (((UINT64)pInfoBlock + pInfoBlock->Length) > (BlkOff + 5))
    {
        CHAR8*    ProjectTag = STR(PROJECT_TAG);
        UINTN     TagLength;
        UINT8     ProjectTagSign[4] = {'$','B','P','T'};

        TagLength = Strlen(ProjectTag);

        MemCpy ( (UINT8*)BlkOff, ProjectTagSign, 4 );
        BlkOff += sizeof (UINT32);
        *(UINT8*)BlkOff = (UINT8)TagLength;
        BlkOff += 1;
    }

#ifdef FLASH_PART_STRING_LENGTH
    if (((UINT64)pInfoBlock + pInfoBlock->Length) > \
            (BlkOff + FLASH_PART_STRING_LENGTH + 8))
        GetFlashPartInfomation ( (UINT8*)Flash4GBMapStart, (UINT8*)BlkOff );
#endif
    return EFI_SUCCESS;
}

//<AMI_PHDR_START>
//----------------------------------------------------------------------
// Procedure:   EnableFlashWrite
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
EFI_STATUS EnableFlashWrite(
    IN OUT FUNC_BLOCK    *pFuncBlock
)
{
    return Flash->DeviceWriteEnable();
}


//<AMI_PHDR_START>
//----------------------------------------------------------------------
// Procedure:   DisableFlashWrite
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
EFI_STATUS DisableFlashWrite(
    IN OUT FUNC_BLOCK    *pFuncBlock
)
{
    return Flash->DeviceWriteDisable();
}

//<AMI_PHDR_START>
//----------------------------------------------------------------------
// Procedure:   EraseFlash
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
EFI_STATUS EraseFlash(
    IN OUT FUNC_BLOCK   *pFuncBlock
)
{
    EFI_STATUS    Status;
    UINT8         *BlockAddress;
    BlockAddress = (UINT8*)(UINTN)(pFuncBlock->BlockAddr + \
                                (0xFFFFFFFF - SmiFlash.FlashCapacity + 1));
    (UINT32)BlockAddress &= (0xFFFFFFFF - FLASH_BLOCK_SIZE + 1);
    if (EFI_ERROR(CheckAddressRange (BlockAddress, \
                                FlashBlockSize))) return EFI_ACCESS_DENIED;
    Status = Flash->Erase(BlockAddress, FlashBlockSize);
    pFuncBlock->ErrorCode = EFI_ERROR(Status) != 0;
    return Status;
}

//<AMI_PHDR_START>
//----------------------------------------------------------------------
// Procedure:   ReadFlash
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
EFI_STATUS ReadFlash(
    IN OUT FUNC_BLOCK   *pFuncBlock
)
{
    UINT32        Flash4GBMapStart;
    EFI_STATUS    Status;
    
    Flash4GBMapStart = 0xFFFFFFFF - (FLASH_BLOCK_SIZE * NUMBER_OF_BLOCKS);
    Flash4GBMapStart += (pFuncBlock->BlockAddr + 1);
    if (EFI_ERROR(CheckAddressRange ((UINT8*)Flash4GBMapStart, \
                                pFuncBlock->BlockSize))) return EFI_ACCESS_DENIED;
    if (EFI_ERROR(CheckAddressRange ((UINT8*)pFuncBlock->BufAddr, \
                                pFuncBlock->BlockSize))) return EFI_ACCESS_DENIED;
    Status = Flash->Read((UINT8*)Flash4GBMapStart, \
                                pFuncBlock->BlockSize, (UINT8*)pFuncBlock->BufAddr);
    pFuncBlock->ErrorCode = EFI_ERROR(Status) != 0;
    return Status;
}

//<AMI_PHDR_START>
//----------------------------------------------------------------------
// Procedure:   WriteFlash
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
EFI_STATUS WriteFlash(
    IN OUT FUNC_BLOCK   *pFuncBlock
)
{
    EFI_STATUS      Status;
    UINT8           *FlashAddress;
    
    FlashAddress = (UINT8*)(UINTN)(pFuncBlock->BlockAddr + \
                            (0xFFFFFFFF - SmiFlash.FlashCapacity + 1));
    if (EFI_ERROR(CheckAddressRange (FlashAddress, \
                            pFuncBlock->BlockSize))) return EFI_ACCESS_DENIED;
    if (EFI_ERROR(CheckAddressRange ((UINT8*)pFuncBlock->BufAddr, \
                            pFuncBlock->BlockSize))) return EFI_ACCESS_DENIED;
    Status = Flash->Write(FlashAddress, \
                            pFuncBlock->BlockSize, (UINT8*)pFuncBlock->BufAddr);
    pFuncBlock->ErrorCode = EFI_ERROR(Status) != 0;
    return Status;
}

//<AMI_PHDR_START>
//----------------------------------------------------------------------
// Procedure:   SMIFlashSMIHandler
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
#if PI_SPECIFICATION_VERSION >= 0x1000A
EFI_STATUS 
SMIFlashSMIHandler (
    IN  EFI_HANDLE                  DispatchHandle,
	IN CONST VOID                   *Context OPTIONAL,
	IN OUT VOID                     *CommBuffer OPTIONAL,
	IN OUT UINTN                    *CommBufferSize OPTIONAL
)
#else
VOID SMIFlashSMIHandler (
    IN  EFI_HANDLE                  DispatchHandle,
    IN  EFI_SMM_SW_DISPATCH_CONTEXT *DispatchContext
)
#endif
{
    EFI_SMM_CPU_SAVE_STATE  *pCpuSaveState = NULL;
    EFI_STATUS  Status = EFI_SUCCESS;
    UINT8       Data;
    UINT64      pCommBuff;
    UINT32      HighBufferAddress = 0;
    UINT32      LowBufferAddress = 0;
    UINTN       Cpu = (UINTN)-1, i = 0;

#if PI_SPECIFICATION_VERSION >= 0x1000A    
    if (CommBuffer != NULL && CommBufferSize != NULL) {
        Cpu = ((EFI_SMM_SW_CONTEXT*)CommBuffer)->SwSmiCpuIndex;
        Data = ((EFI_SMM_SW_CONTEXT*)CommBuffer)->CommandPort;
    }
    
    //
    // Found Invalid CPU number, return 
    //
    if(Cpu == (UINTN)-1) RETURN(Status);

    Status = gSmmCpu->ReadSaveState ( gSmmCpu, \
                                      4, \
                                      EFI_SMM_SAVE_STATE_REGISTER_RBX, \
                                      Cpu, \
                                      &LowBufferAddress );
    Status = gSmmCpu->ReadSaveState ( gSmmCpu, \
                                      4, \
                                      EFI_SMM_SAVE_STATE_REGISTER_RCX, \
                                      Cpu, \
                                      &HighBufferAddress );
#else // PI_SPECIFICATION_VERSION < 0x1000A
    SW_SMI_CPU_TRIGGER      *SwSmiCpuTrigger;

    for (i = 0; i < pSmst->NumberOfTableEntries; ++i) {
        if (guidcmp(&pSmst->SmmConfigurationTable[i].VendorGuid,
                                    &gSwSmiCpuTriggerGuid) == 0) {
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
    if(Cpu == (UINTN) -1) RETURN(Status);

    Data    = (UINT8)DispatchContext->SwSmiInputValue;
    
    pCpuSaveState       = pSmst->CpuSaveState;
    HighBufferAddress   = pCpuSaveState[Cpu].Ia32SaveState.ECX;
    LowBufferAddress    = pCpuSaveState[Cpu].Ia32SaveState.EBX;

#endif    

    pCommBuff           = HighBufferAddress;
    pCommBuff           = Shl64(pCommBuff, 32);
    pCommBuff           += LowBufferAddress;
    
    if(Data == SMIFLASH_GET_FLASH_INFO)
        Status = CheckAddressRange( (UINT8*)pCommBuff, sizeof(INFO_BLOCK) );
    else
        Status = CheckAddressRange( (UINT8*)pCommBuff, sizeof(FUNC_BLOCK) );
    if(EFI_ERROR(Status)) RETURN(Status);
   
    if (Data != SMIFLASH_GET_FLASH_INFO) 
        ((FUNC_BLOCK*)pCommBuff)->ErrorCode = 0;
    for (i = 0; SMIFlashPreHandler[i] != NULL; i++) 
        SMIFlashPreHandler[i](Data, pCommBuff);
    if ((Data == SMIFLASH_GET_FLASH_INFO) || \
        (((FUNC_BLOCK*)pCommBuff)->ErrorCode == 0)) {
        switch (Data) {
        case 0x20:      // Enable Flash
            for (i = 0; SMIFlashPreUpdate[i] != NULL; i++) 
                SMIFlashPreUpdate[i]();
            EnableFlashWrite((FUNC_BLOCK *)pCommBuff);
            break;

        case 0x24:      // Disable Flash
            for (i = 0; SMIFlashEndUpdate[i] != NULL; i++) 
                SMIFlashEndUpdate[i]();

            DisableFlashWrite((FUNC_BLOCK *)pCommBuff);
            break;
            
        case 0x22:      // Erase Flash

            EraseFlash((FUNC_BLOCK *)pCommBuff);

            break;
            
        case 0x21:      // Read Flash
            ReadFlash((FUNC_BLOCK *)pCommBuff);
            break;
            
        case 0x23:      // Write Flash

            WriteFlash((FUNC_BLOCK *)pCommBuff);
            break;
            
        case 0x25:      // Get Flash Info
            GetFlashInfo((INFO_BLOCK *)pCommBuff);
        }

    }
    for (i = 0; SMIFlashEndHandler[i] != NULL; i++)
        SMIFlashEndHandler[i](Data, pCommBuff);
    RETURN(Status);
}

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
EFI_STATUS InSmmFunction(
    IN EFI_HANDLE          ImageHandle,
    IN EFI_SYSTEM_TABLE    *SystemTable
)
{
    EFI_HANDLE  Handle;
    UINTN       Index;
    EFI_HANDLE  DummyHandle = NULL;
    EFI_STATUS  Status;
    SMM_HOB     *SmmHob;
    EFI_GUID    SmmHobGuid = SMM_HOB_GUID;
    EFI_GUID    HobListGuid = HOB_LIST_GUID;
#if PI_SPECIFICATION_VERSION >= 0x1000A
    EFI_SMM_SW_DISPATCH2_PROTOCOL    *pSwDispatch;
    EFI_SMM_SW_REGISTER_CONTEXT      SwContext;
#else
    EFI_SMM_SW_DISPATCH_PROTOCOL    *pSwDispatch;
    EFI_SMM_SW_DISPATCH_CONTEXT     SwContext;
#endif
    
#if PI_SPECIFICATION_VERSION >= 0x1000A
    Status = InitAmiSmmLib( ImageHandle, SystemTable );
    Status = pBS->LocateProtocol(&gEfiSmmBase2ProtocolGuid, NULL, &gSmmBase2);
    if (EFI_ERROR(Status)) return EFI_SUCCESS;

    Status = pSmmBase->GetSmstLocation (gSmmBase2, &pSmst);
    if (EFI_ERROR(Status)) return EFI_SUCCESS;

    Status = pSmst->SmmLocateProtocol( \
                        &gEfiSmmSwDispatch2ProtocolGuid, NULL, &pSwDispatch);
    if (EFI_ERROR(Status)) return EFI_SUCCESS;

    Status = pSmst->SmmLocateProtocol(&gEfiSmmCpuProtocolGuid, NULL, &gSmmCpu);
    if (EFI_ERROR(Status)) return EFI_SUCCESS;
#else
    VERIFY_EFI_ERROR(pBS->LocateProtocol(
                          &gEfiSmmSwDispatchProtocolGuid, NULL, &pSwDispatch));
#endif
    VERIFY_EFI_ERROR(pBS->LocateProtocol(&gFlashSmmProtocolGuid,
                                                         NULL, &Flash));
    TRACE((TRACE_ALWAYS,"SmiFlash: Flash Protocol %X\n",Flash));

    SmmHob = (SMM_HOB*)GetEfiConfigurationTable(pST, &HobListGuid);
    if (SmmHob == NULL) return EFI_NOT_FOUND;
    Status = FindNextHobByGuid(&SmmHobGuid,(VOID**)&SmmHob);
    if (EFI_ERROR(Status)) return Status;
    gSmmHob = *SmmHob;

    for (Index = 0x20; Index < 0x26; Index++) {
        SwContext.SwSmiInputValue = Index;
        Status  = pSwDispatch->Register(pSwDispatch, SMIFlashSMIHandler,
                                                      &SwContext, &Handle);
        ASSERT_EFI_ERROR(Status);
        
        if (EFI_ERROR(Status)) return EFI_SUCCESS;
        
        //TODO: If any errors, unregister any registered SwSMI by this driver.
        //If error, and driver is unloaded, then a serious problem would exist.
    }
    
#if PI_SPECIFICATION_VERSION >= 0x1000A
    Status = pSmst->SmmInstallProtocolInterface(
                 &DummyHandle,
                 &gEfiSmiFlashProtocolGuid,
                 EFI_NATIVE_INTERFACE,
                 &SmiFlash
             );
#endif
    // If PI 1.2, install this protocol for backward compatible. 
    DummyHandle = NULL;
    Status = pBS->InstallMultipleProtocolInterfaces(
                 &DummyHandle,
                 &gEfiSmiFlashProtocolGuid,&SmiFlash,
                 NULL
             );
    ASSERT_EFI_ERROR(Status);

    for (Index = 0; SMIFlashInSmm[Index] != NULL; Index++) {
        SMIFlashInSmm[Index]();
    }    
    return EFI_SUCCESS;
}
//<AMI_PHDR_START>
//----------------------------------------------------------------------
// Procedure:   NonSmmElinkFunctions
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
EFI_STATUS
NonSmmElinkFunctions(
    IN EFI_HANDLE          ImageHandle,
    IN EFI_SYSTEM_TABLE    *SystemTable
)
{
    UINT8  i;

    for (i = 0; SMIFlashNotInSmm[i] != NULL; i++) 
        SMIFlashNotInSmm[i]();

    return EFI_SUCCESS;
}
//<AMI_PHDR_START>
//----------------------------------------------------------------------
// Procedure:   SMIFlashDriverEntryPoint
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
EFI_STATUS SMIFlashDriverEntryPoint(
    IN EFI_HANDLE       ImageHandle,
    IN EFI_SYSTEM_TABLE *SystemTable
)
{
    InitAmiLib(ImageHandle, SystemTable);
    return InitSmmHandler (ImageHandle, \
                            SystemTable, InSmmFunction, NonSmmElinkFunctions);
}

//**********************************************************************
//**********************************************************************
//**                                                                  **
//**        (C)Copyright 1985-2009, American Megatrends, Inc.         **
//**                                                                  **
//**                       All Rights Reserved.                       **
//**                                                                  **
//**      5555 Oakbrook Parkway, Suite 200, Norcross, GA 30093        **
//**                                                                  **
//**                       Phone: (770)-246-8600                      **
//**                                                                  **
//**********************************************************************
//**********************************************************************
