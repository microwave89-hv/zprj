//*************************************************************************
//*************************************************************************
//**                                                                     **
//**        (C)Copyright 1987-2013, American Megatrends, Inc.            **
//**                                                                     **
//**                       All Rights Reserved.                          **
//**                                                                     **
//**      5555 Oakbrook Parkway, Suite 200, Norcross, GA 30093           **
//**                                                                     **
//**                       Phone: (770)-246-8600                         **
//**                                                                     **
//*************************************************************************
//*************************************************************************

//****************************************************************************
// $Header: /Alaska/SOURCE/Modules/SharkBayRefCodes/Haswell/AMI Cpu PKG/CPU Core/MicrocodeUpdate/MicrocodeUpdate.c 4     4/14/15 2:48a Crystallee $
//
// $Revision: 4 $
//
// $Date: 4/14/15 2:48a $
//
//****************************************************************************
// Revision History
// ----------------
// $Log: /Alaska/SOURCE/Modules/SharkBayRefCodes/Haswell/AMI Cpu PKG/CPU Core/MicrocodeUpdate/MicrocodeUpdate.c $
// 
// 4     4/14/15 2:48a Crystallee
// 
// 3     5/15/14 2:32a Crystallee
// [TAG]  		EIP169079
// [Category]  	Improvement
// [Description]  	Security Enhancement for SMIHandler in Microcode update
// SWSMI.
// 
// 2     10/28/12 11:23p Davidhsieh
// [TAG]  		EIP104874
// [Category]  	Improvement
// [Description]  	Add signature check before search microcode ffs 
// 
// 1     2/07/12 3:59a Davidhsieh
// 
// 
//****************************************************************************

//<AMI_FHDR_START>
//----------------------------------------------------------------------------
//
// Name:		MicrocodeUpdate.c
//
// Description: Microcode Update SMI handler.
//    This file contains code for processing Interrupt 15 function
//    D042h, and for registering the callback that does the processing.
//
//----------------------------------------------------------------------------
//<AMI_FHDR_END>

#include <Protocol\SmmBase.h>
#include <Protocol\SmmSwDispatch.h>
#include <token.h>
#include <AmiDxeLib.h>
#include <Ffs.h>
#include <AmiCspLibInc.h>
#include "MicrocodeUpdate.h"
#include <AmiSmm.h>
#include <AmiHobs.h>

#ifndef INT15_D042_SWSMI
#define INT15_D042_SWSMI 0x44
#endif

#pragma optimize("", off)

EFI_GUID gMcodeFfsguid =
    {0x17088572, 0x377F, 0x44ef, 0x8F,0x4E,0xB0,0x9F,0xFF,0x46,0xA0,0x70};

EFI_GUID gSwSmiCpuTriggerGuid = SW_SMI_CPU_TRIGGER_GUID;

#if MICROCODE_SPLIT_BB_UPDATE
UINT8 *gMcodeFlashStartFixed = 0;
UINT32 gMcodeFlashSizeFixed = 0;
#endif

UINT8 *gMcodeFlashStartUpdate = 0;
UINT32 gMcodeFlashSizeUpdate = 0; 

typedef enum {
    MCODE_BLK_EMPTY = 0,
    MCODE_BLK_START,
    MCODE_BLK_CONT
} MCODE_BLK_TYPE;

typedef struct {
    UINT8           *Addr; 
    UINT32          Size;   //0 if less than 64k
    MCODE_BLK_TYPE  Type;    
} MCODE_BLK_MAP;

UINT16 gNumMcodeBlks = 0;
UINT16 gFirstEmptyBlk = 0xffff;
MCODE_BLK_MAP *gMcodeBlkMap = NULL;

UINT32 gCpuSignature;
UINT8  gCpuFlag;
UINT32 gUcRevision;

SMM_HOB gSmmHob;

#define MAX_MICROCODE_UPDATE_FUNCTIONS 4
VOID(*MicrocodeUpdate[4])(SMI_UC_DWORD_REGS *) = {
    PresenceTest, WriteUpdateData, UpdateControl, ReadUpdateData
};

#define MICROCODE_SIZE(Hdr) \
    (((MICROCODE_HEADER*)(Hdr))->TotalSize ? ((MICROCODE_HEADER*)Hdr)->TotalSize : 2048)

#if PACK_MICROCODE
#define MICROCODE_ALIGN_SIZE(Hdr) \
    ((MICROCODE_SIZE(Hdr) + 16 - 1) & ~(16 - 1))
#else
#define MICROCODE_ALIGN_SIZE(Hdr) \
    ((MICROCODE_SIZE(Hdr) + MICROCODE_BLOCK_SIZE - 1) & ~(MICROCODE_BLOCK_SIZE - 1))
#endif

#if PACK_MICROCODE
#define MICROCODE_BLOCKS(Hdr) \
    ((((MICROCODE_SIZE(Hdr) + MICROCODE_BLOCK_SIZE - 1) & ~(MICROCODE_BLOCK_SIZE - 1)))/MICROCODE_BLOCK_SIZE)
#else
    #define MICROCODE_BLOCKS(Hdr) (MICROCODE_ALIGN_SIZE(Hdr)/MICROCODE_BLOCK_SIZE)
#endif

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
    if ( ((EFI_PHYSICAL_ADDRESS)Address >= gSmmHob.Tseg) && 
         ((EFI_PHYSICAL_ADDRESS)Address <= (gSmmHob.Tseg + gSmmHob.TsegLength)) )
        return EFI_ACCESS_DENIED;

    if ( (((EFI_PHYSICAL_ADDRESS)Address + Range) >= gSmmHob.Tseg) && 
         (((EFI_PHYSICAL_ADDRESS)Address + Range) <= (gSmmHob.Tseg + gSmmHob.TsegLength)) )
        return EFI_ACCESS_DENIED;

    return EFI_SUCCESS;
}

//<AMI_PHDR_START>
//----------------------------------------------------------------------------
// Procedure: IsValidHeader
//
// Description: Check if the header is valid.
//
// Input: MICROCODE_HEADER *uHeader -- Address of Microcode Header.
//
// Output: BOOLEAN -- TRUE if microcode header is valid.
//
//----------------------------------------------------------------------------
//<AMI_PHDR_END>

BOOLEAN IsValidHeader(MICROCODE_HEADER *uHeader)
{
    if (uHeader->HeaderVersion != UC_HEADER_VERSION) return FALSE;
    if (uHeader->LoaderRevison != UC_LOADER_REVISION) return FALSE;
    return TRUE;
}

//<AMI_PHDR_START>
//----------------------------------------------------------------------------
// Procedure: IsValidChecksum
//
// Description: Validate the checksum.
//
// Input:
//      VOID *Microcode - Address of Microcode Header.
//      UINT32 Size     - Microcode Size.
//
// Output: BOOLEAN -- TRUE if checksum is valid.
//
//----------------------------------------------------------------------------
//<AMI_PHDR_END>

BOOLEAN IsValidChecksum(VOID *Mcode, UINT32 Size)
{
    UINT32  NumDwords = Size >> 2;
    UINT32 *p32 = (UINT32*)Mcode;
    UINT32 Checksum = 0;   
    UINT32 i;

    for(i = 0; i < NumDwords; ++i) Checksum += p32[i];      //Checksum is the summation dwords.

    return Checksum == 0 ? TRUE : FALSE;
}


//<AMI_PHDR_START>
//----------------------------------------------------------------------------
// Procedure: GetInstalledMicrocodeRevision
//
// Description: Get the installed microcode revision on the cpu.
//
// Input: VOID
//
// Output: UINT32 - Revision of microcode currently installed on CPU.
//
//----------------------------------------------------------------------------
//<AMI_PHDR_END>

UINT32 GetInstalledMicrocodeRevision()
{
    UINT32 RegEax, RegEbx, RegEcx, RegEdx;

    //Clear IA32_BIOS_SIGN_ID of microcode loaded.
    WriteMsr(0x8b, 0); //IA32_BIOS_SIGN_ID

    //Reading CPU ID 1, updates the MSR to the microcode revision.
    CPULib_CpuID(1, &RegEax, &RegEbx, &RegEcx, &RegEdx);
    return (UINT32) Shr64(ReadMsr(0x8b), 32);
}


//<AMI_PHDR_START>
//----------------------------------------------------------------------------
// Procedure: CountBlks
//
// Description: Count blocks taken by microcode in FFS.
//
// Input:
//  IN UINT8 *McodeStart - Start of microcode in FFS.
//  IN UINT32 McodeSize - Size of microcode and empty space in FFS.
//  IN BOOLEAN CountEmpty - TRUE if calculate blocks for empty space.
//
// Output: UINT16 - Number of blocks needed.
//
//----------------------------------------------------------------------------
//<AMI_PHDR_END>

UINT16 CountBlks(IN UINT8 *McodeStart, IN UINT32 McodeSize, IN BOOLEAN CountEmpty)
{
    UINT8 *p = McodeStart;
    UINT8 *EndOfMcode = p + McodeSize;
    UINT16 TotBlks = 0;

    while(p < EndOfMcode) {
        if (*(UINT32*)p != 0xffffffff && *(UINT32*)p != 0) {            
            TotBlks += MICROCODE_BLOCKS(p);
            p += MICROCODE_ALIGN_SIZE(p);
        } else if (CountEmpty) {
            TotBlks += (UINT16)((EndOfMcode - p) / MICROCODE_BLOCK_SIZE);
            break;
        }
        else break;
    }

    return TotBlks;
}


//<AMI_PHDR_START>
//----------------------------------------------------------------------------
// Procedure: FillMicrocodeBlkMap
//
// Description: Update gMcodeBlkMap with data for microcode.
//
// Input:
//  IN OUT   *BlkStart - On Input: Start update with this block. Output: Next call use this value.
//  IN UINT8 *McodeStart - Start of microcode in FFS.
//  IN UINT32 McodeSize - Size of microcode and empty space in FFS.
//  IN BOOLEAN CountEmpty - TRUE if update blocks for empty space.
//
// Output: VOID
//
//----------------------------------------------------------------------------
//<AMI_PHDR_END>

VOID FillMicrocodeBlkMap(IN OUT UINT16 *BlkStart, IN UINT8 *McodeStart, IN UINT32 McodeSize, IN BOOLEAN CountEmpty)
{
    UINT8 *p = McodeStart;
    UINT8 *EndOfMcode = p + McodeSize;
    UINT16 BlkIndex = *BlkStart;

    while(p < EndOfMcode) {
        if (*(UINT32*)p != 0xffffffff && *(UINT32*)p != 0) {            
            UINT16 NumBlks = MICROCODE_BLOCKS(p);
            UINT32 McodeSize = MICROCODE_SIZE(p);
#if PACK_MICROCODE == 0
            UINT32 PackDiff = MICROCODE_ALIGN_SIZE(p) - McodeSize;
#endif

            gMcodeBlkMap[BlkIndex].Addr = p;
            gMcodeBlkMap[BlkIndex].Size =  MICROCODE_BLOCK_SIZE;
            gMcodeBlkMap[BlkIndex].Type = MCODE_BLK_START;
            if (NumBlks <= 1 && McodeSize < MICROCODE_BLOCK_SIZE) {
                gMcodeBlkMap[BlkIndex].Size =  McodeSize;
            }
            p += gMcodeBlkMap[BlkIndex].Size;
            McodeSize -= gMcodeBlkMap[BlkIndex].Size;
            ++BlkIndex;
            while(--NumBlks) {
                gMcodeBlkMap[BlkIndex].Addr = p;
                gMcodeBlkMap[BlkIndex].Size = MICROCODE_BLOCK_SIZE;
                gMcodeBlkMap[BlkIndex].Type = MCODE_BLK_CONT;
                if (NumBlks == 1 && McodeSize < MICROCODE_BLOCK_SIZE) {
                    gMcodeBlkMap[BlkIndex].Size =  McodeSize;
                }
                p += gMcodeBlkMap[BlkIndex].Size;
                McodeSize -= gMcodeBlkMap[BlkIndex].Size;
                ++BlkIndex;
            }
#if PACK_MICROCODE == 0
            p += PackDiff;
#endif
        } else if (CountEmpty) {
            gFirstEmptyBlk = BlkIndex;
            while (BlkIndex < gNumMcodeBlks) {
                gMcodeBlkMap[BlkIndex].Addr = p;
                gMcodeBlkMap[BlkIndex].Size = MICROCODE_BLOCK_SIZE;
                gMcodeBlkMap[BlkIndex].Type = MCODE_BLK_EMPTY;
                BlkIndex++;
            }
            break;
        } else break;
    }
    *BlkStart = BlkIndex;
}

//<AMI_PHDR_START>
//----------------------------------------------------------------------------
// Procedure: InitMcodeBlkMap
//
// Description: Initialize gMcodeBlkMap and related globals for all microcode FFS.
//
// Input: VOID
//
// Output:  VOID
//
//----------------------------------------------------------------------------
//<AMI_PHDR_END>

VOID InitMcodeBlkMap()
{
    UINT16 BlkStart = 0;

    if (gMcodeBlkMap != NULL) pSmst->SmmFreePool(gMcodeBlkMap);
    gNumMcodeBlks = 0;
#if MICROCODE_SPLIT_BB_UPDATE
    gNumMcodeBlks += CountBlks(gMcodeFlashStartFixed, gMcodeFlashSizeFixed, FALSE);
#endif
    gNumMcodeBlks += CountBlks(gMcodeFlashStartUpdate, gMcodeFlashSizeUpdate, TRUE);

    pSmst->SmmAllocatePool(0, gNumMcodeBlks * sizeof(MCODE_BLK_MAP), &gMcodeBlkMap);

    gFirstEmptyBlk = 0xffff;
#if MICROCODE_SPLIT_BB_UPDATE
    FillMicrocodeBlkMap(&BlkStart, gMcodeFlashStartFixed, gMcodeFlashSizeFixed, FALSE);
#endif
    FillMicrocodeBlkMap(&BlkStart, gMcodeFlashStartUpdate, gMcodeFlashSizeUpdate, TRUE);
}

//<AMI_PHDR_START>
//----------------------------------------------------------------------------
// Procedure: FindMicrocodeFfs
//
// Description: Find Micorode FFS in FV.
//
// Input: IN EFI_FIRMWARE_VOLUME_HEADER *FvHdr - Firmware volume to search
//
// Output:  UINT8 * - Return FFS.
//
//----------------------------------------------------------------------------
//<AMI_PHDR_END>

UINT8 *FindMicrocodeFfs(IN EFI_FIRMWARE_VOLUME_HEADER *FvHdr)
{
    UINT8 *FvPtr = (UINT8*)FvHdr + FvHdr->HeaderLength;
    UINT8 *EndOfFv = (UINT8*)FvHdr + FvHdr->FvLength;

    //Check for corrupt firmware volume.
    if (FvHdr->Signature != 'HVF_') return NULL;
    //Search the FV_MAIN firmware volume for the microcode file.
    while (FvPtr < EndOfFv && *FvPtr != -1) {
        if (guidcmp(&gMcodeFfsguid, &((EFI_FFS_FILE_HEADER*)FvPtr)->Name)==0)
            return FvPtr;

        FvPtr += *(UINT32*)&((EFI_FFS_FILE_HEADER*)FvPtr)->Size & 0xffffff;
        FvPtr = (UINT8*)(((UINTN)FvPtr + 7) & ~7);   //8 byte alignment
    }
    return NULL;
}

//<AMI_PHDR_START>
//----------------------------------------------------------------------------
// Procedure: InitMicrocodeVariables
//
// Description: Initialize global variables used by the driver.
//
// Input: VOID
//
// Output:  VOID
//
//----------------------------------------------------------------------------
//<AMI_PHDR_END>

BOOLEAN InitMicrocodeVariables()
{
    UINT8 *FfsPtr;
    UINT32 McodeFfsSize;
    UINT64 MsrValue;
    UINT32 RegEbx, RegEcx, RegEdx;
#if MICROCODE_SPLIT_BB_UPDATE
    UINT16 MPDTLengthFixed;
#endif
    UINT16 MPDTLengthUpdate;

#if MICROCODE_SPLIT_BB_UPDATE
    FfsPtr = FindMicrocodeFfs((EFI_FIRMWARE_VOLUME_HEADER*)(UINTN)FV_MICROCODE_BASE);
    if (FfsPtr == NULL) return FALSE;

    gMcodeFlashStartFixed = FfsPtr + sizeof(EFI_FFS_FILE_HEADER);
    McodeFfsSize = ((*(UINT32*)((EFI_FFS_FILE_HEADER*)FfsPtr)->Size) & 0xffffff);
#if MPDTable_CREATED
    MPDTLengthFixed = *(UINT16*)(FfsPtr + McodeFfsSize - 2); //Last 2 bytes is table size.
#else 
    MPDTLengthFixed = 0;
#endif
    gMcodeFlashSizeFixed = McodeFfsSize - sizeof(EFI_FFS_FILE_HEADER) - MPDTLengthFixed;
#endif

#if MICROCODE_SPLIT_BB_UPDATE
    FfsPtr = FindMicrocodeFfs((EFI_FIRMWARE_VOLUME_HEADER*)(UINTN)FV_MICROCODE_UPDATE_BASE);
#else
    FfsPtr = FindMicrocodeFfs((EFI_FIRMWARE_VOLUME_HEADER*)(UINTN)FV_MICROCODE_BASE);
#endif
    if (FfsPtr == NULL) return FALSE;

    gMcodeFlashStartUpdate = FfsPtr + sizeof(EFI_FFS_FILE_HEADER);
    McodeFfsSize = ((*(UINT32*)((EFI_FFS_FILE_HEADER*)FfsPtr)->Size) & 0xffffff);
#if MPDTable_CREATED
    MPDTLengthUpdate = *(UINT16*)(FfsPtr + McodeFfsSize - 2); //Last 2 bytes is table size.
#else
    MPDTLengthUpdate = 0;
#endif
    gMcodeFlashSizeUpdate = McodeFfsSize - sizeof(EFI_FFS_FILE_HEADER) - MPDTLengthUpdate;

    InitMcodeBlkMap();

    //Clear revision value. CPUID of 1 will update this revision value.
    WriteMsr(0x8b, 0); //IA32_BIOS_SIGN_ID

    CPULib_CpuID(1, &gCpuSignature, &RegEbx, &RegEcx, &RegEdx);
    gCpuSignature &= 0x00ffffff;
    MsrValue = ReadMsr(0x17); 
    gCpuFlag = (UINT8)(Shr64(MsrValue, 50) & 7);            //Get the CPU flags.
    gUcRevision = (UINT32) Shr64(ReadMsr(0x8b), 32);        //Get the current microcode revision loaded.

    return TRUE;
}

//<AMI_PHDR_START>
//----------------------------------------------------------------------------
// Procedure: FindMicrocodeOfStepping
//
// Description: Search the microcode in the firmware for the cpu signature
//                  or earlier steping.
//
// Input:
//      UINT8 *Mcode - Address of Mcode Header.
//      UINT8 *End       - Mcode End.
//      UINT32 CpuSignature - Signature of CPU to find.
//
// Output:  VOID
//
//----------------------------------------------------------------------------
//<AMI_PHDR_END>

VOID *FindMicrocodeOfStepping(UINT8 *Mcode, UINT8 *End, UINT32 CpuSignature)
{
    UINT8 *ptr;
     for(ptr = Mcode; ptr < End; ptr += MICROCODE_ALIGN_SIZE(ptr)) {
        MICROCODE_HEADER* uC = (MICROCODE_HEADER*)ptr;

        if (*(UINT32*)ptr == 0xffffffff || *(UINT32*)ptr == 0) return 0;
        if (uC->CpuSignature == CpuSignature) return ptr;

        if (uC->TotalSize > (uC->DataSize + 48)) {        //Extended signature count.
            MICROCODE_EXT_PROC_SIG_TABLE *SigTable = (MICROCODE_EXT_PROC_SIG_TABLE*)(ptr + uC->DataSize + 48);
            UINT32 ExtSigCount = SigTable->Count;
            UINT8 i;

            for (i = 0; i < ExtSigCount; ++i) {
                if (SigTable->ProcSig[i].CpuSignature == CpuSignature) return ptr;
            }
        } 
    }
    return 0;
}

//<AMI_PHDR_START>
//----------------------------------------------------------------------------
// Procedure: LoadMicrocode
//
// Description: Load the microcode onto the CPU.
//
// Input:
//      VOID *Mcode - Address of Microcode Header.
//
// Output:  VOID
//
//----------------------------------------------------------------------------
//<AMI_PHDR_END>

VOID LoadMicrocode(IN VOID *Mcode)
{
    WriteMsr(0x79, (UINT64)(UINTN)Mcode + 48); //IA32_BIOS_UPDT_TRIG
}

//<AMI_PHDR_START>
//----------------------------------------------------------------------------
// Procedure: LoadMicrocodeEachCpu
//
// Description: Load the microcode on each CPU.
//
// Input:   EFI_SMI_CPU_SAVE_STATE *CpuSaveState
//
// Output:  VOID
//
//----------------------------------------------------------------------------
//<AMI_PHDR_END>

VOID LoadMicrocodeEachCpu(IN VOID *Mcode)
{
    UINT8 i;
    //In for loop, BSP CPU will return error and continue for all APs.
    for (i = 0; i < pSmst->NumberOfCpus; ++i) {
        pSmst->SmmStartupThisAp(LoadMicrocode, i, Mcode);
    }
    LoadMicrocode(Mcode);
}

//<AMI_PHDR_START>
//----------------------------------------------------------------------------
// Procedure: PresenceTest
//
// Description: Execute the presence test function for int 15h.
//
// Input:   SMI_UC_DWORD_REGS *Regs
//
// Output:  VOID
//
// Notes:
//
//      Input:
//          AX - D042h
//          BL - 00h i.e., PRESCENCE_TEST
//
//      Output:
//          CF  NC - All return values are valid
//          CY - Failure, AH contains status.
//
//          AH  Return code
//          AL  Additional OEM information
//          EBX Part one of the signature 'INTE'.
//          ECX Part two of the signature 'LPEP'.
//          EDX Version number of the BIOS update loader
//          SI  Number of update blocks system can record in NVRAM (1 based).
//
//----------------------------------------------------------------------------
//<AMI_PHDR_END>

VOID PresenceTest(SMI_UC_DWORD_REGS *Regs)
{
    Regs->EBX = 'INTE';     //Part 1 of the Signature
    Regs->ECX = 'LPEP';     //Part 2 of the Signature.
    Regs->EDX = UC_LOADER_VERSION;
    
    *(UINT16*)&Regs->ESI = gNumMcodeBlks;    //Number of blocks.
}

//<AMI_PHDR_START>
//----------------------------------------------------------------------------
// Procedure: UpdateControl
//
// Description: Execute the update control for int 15h.
//
// Input:   SMI_UC_DWORD_REGS *Regs
//
// Output:  VOID
//
// Notes:
//  Input:
//      AX - D042h
//      BL - 02h i.e., UPDATE_CONTROL
//      BH - Task
//      1 - Enable the update loading at initialization time.
//      2 - Determine the current state of the update control without changing its status.
// 
//  Output:
//      AH  Return code
//      AL  Additional OEM information
//      BL  Update status Disable or Enable.
//
//----------------------------------------------------------------------------
//<AMI_PHDR_END>

VOID UpdateControl(SMI_UC_DWORD_REGS *Regs)
{

    //This is checking for a task of 0 or > 2. This is not in the specification, but in Intel code.
    if ((Regs->EBX & 0xff00) == 0 || (Regs->EBX & 0x0ff00) > 0x200) {   //Check BH
        // Indicate we cannot determinate the Enable/Disable status via CMOS
        Regs->EFLAGS |= CARRY_FLAG;
        *(UINT16*)&Regs->EAX = UC_READ_FAILURE;  
    }

    Regs->EBX = (Regs->EBX & 0xffffff00) | UC_INT15_ENABLE;    // Always enabled.
}

//<AMI_PHDR_START>
//----------------------------------------------------------------------------
// Procedure: ReadUpdateData
//
// Description: Read microcode using int15h.
//
// Input:   SMI_UC_DWORD_REGS *Regs
//
// Output:  VOID
//
// Notes:
//
//  Input:
//      AX  - D042h
//      BL  - 03h i.e., READ_UPDATE_DATA
//      ES:DI - Real Mode Pointer to the Intel Update structure.
//      SS:SP - Stack pointer (32K minimum)
//      SI    - Update number, the index number of the update block to be read.
//              This number is zero based and must be less than the update
//              count returned from the prescence test function.
//
// Output:
//      AH  Return code
//      AL  Additional OEM information
//      BL  Update status Disable or Enable.
//
//----------------------------------------------------------------------------
//<AMI_PHDR_END>

VOID ReadUpdateData(SMI_UC_DWORD_REGS *Regs)
{
	EFI_STATUS Status;
    UINT16 Index = (UINT16)Regs->ESI;
    UINT8   *UpdateBuffer;
    MICROCODE_HEADER *Header;

    if (Index >= gNumMcodeBlks) {
      Regs->EFLAGS |= CARRY_FLAG;
      *(UINT16*)&Regs->EAX = UC_UPDATE_NUM_INVALID;
      return;
    }

    if (gMcodeBlkMap[Index].Type == MCODE_BLK_CONT) {
        Regs->EFLAGS |= CARRY_FLAG;
        *(UINT16*)&Regs->EAX = UC_NOT_EMPTY;
        return;
    }        

    UpdateBuffer = (UINT8*)(UINTN)(((UINT16)Regs->ES << 4) + (UINT16)Regs->EDI);
	
	Status = CheckAddressRange (UpdateBuffer, MICROCODE_BLOCK_SIZE);
    if(EFI_ERROR(Status)) return;

    if (gMcodeBlkMap[Index].Type == MCODE_BLK_EMPTY) {
        MemSet(UpdateBuffer, MICROCODE_BLOCK_SIZE, 0xff);
        return;
    }        

    Header = (MICROCODE_HEADER *)gMcodeBlkMap[Index].Addr;

    MemCpy(UpdateBuffer, Header, MICROCODE_SIZE(Header));
}


///////////////////////////////////////////////////////////////////////////////////

static UINT8 *gFlashBlk;          //Pointer to current flash block to write.
static UINT8 *gFlashBuffer;         //Pointer to beginning of buffer.
static UINT8 *gFlashBufferPos;      //Pointer to current posisiton.
static UINT32 gFlashBufferUsed;     //Number of bytes used in the buffer.


//<AMI_PHDR_START>
//----------------------------------------------------------------------------
// Procedure: FlushBufferToFlash
//
// Description: Helper function to write the buffer to the flash and reset the buffer.
//
// Input: VOID
//
// Output:  VOID
//
//----------------------------------------------------------------------------
//<AMI_PHDR_END>

VOID FlushBufferToFlash()
{
    FwhErase((UINTN)gFlashBlk, FLASH_BLOCK_SIZE);
    FwhWrite(gFlashBuffer, (UINTN)gFlashBlk, FLASH_BLOCK_SIZE);
    gFlashBlk += FLASH_BLOCK_SIZE;
    gFlashBufferPos = gFlashBuffer;
    gFlashBufferUsed = 0;

}

//<AMI_PHDR_START>
//----------------------------------------------------------------------------
// Procedure: InitializeFlashBuffer
//
// Description: Initialize the flash buffer before using.
//
// Input:
//  IN UINT8* FirstFlashBlk - Address of first block to flash.
//  IN UINT8* FlashBuffer - Flash Buffer.
//
// Output:  VOID
//
//----------------------------------------------------------------------------
//<AMI_PHDR_END>

VOID InitializeFlashBuffer(IN UINT8* FirstFlashBlk, IN UINT8 *FlashBuffer)
{
    gFlashBlk = FirstFlashBlk;
    gFlashBuffer = FlashBuffer;
    gFlashBufferPos = gFlashBuffer;
    gFlashBufferUsed = 0;
}

//<AMI_PHDR_START>
//----------------------------------------------------------------------------
// Procedure: CopyToFlashBuffer
//
// Description: Copy data to the buffer. When the buffer is full, write to the flash,
//  and continues to copy data.
//
// Input:
//  IN UINT8 Data - Start of data to write.
//  IN UINT32 Size - Amount to Write.
//
// Output:  VOID
//
//----------------------------------------------------------------------------
//<AMI_PHDR_END>

VOID CopyToFlashBuffer(IN UINT8 *Data, IN UINT32 Size)
{
    while (Size) {
        if (gFlashBufferUsed + Size <= FLASH_BLOCK_SIZE) {
            MemCpy(gFlashBufferPos, Data, Size);

            gFlashBufferPos += Size;
            gFlashBufferUsed += Size;

            if (gFlashBufferUsed == FLASH_BLOCK_SIZE) FlushBufferToFlash();
            return;
        }
		
		MemCpy(gFlashBufferPos, Data, FLASH_BLOCK_SIZE - gFlashBufferUsed);
        Data += FLASH_BLOCK_SIZE - gFlashBufferUsed;
		Size -= FLASH_BLOCK_SIZE - gFlashBufferUsed;
        FlushBufferToFlash();
    }
}

//<AMI_PHDR_START>
//----------------------------------------------------------------------------
// Procedure: WriteValueToFlashBuffer
//
// Description: Fill part of the buffer with a value. When the buffer is full, write to the flash,
//  and continue to update the beginning of the buffer with a value.
//
// Input:
//  IN UINT8 Value - Value to write.
//  IN UINT32 Size - Amount to Write.
//
// Output:  VOID
//
//----------------------------------------------------------------------------
//<AMI_PHDR_END>

VOID WriteValueToFlashBuffer(IN UINT8 Value, IN UINT32 Size)
{

    while (Size) {
        if (gFlashBufferUsed + Size <= FLASH_BLOCK_SIZE) {
            MemSet(gFlashBufferPos, Size, Value);

            gFlashBufferPos += Size;
            gFlashBufferUsed += Size;

            if (gFlashBufferUsed == FLASH_BLOCK_SIZE) FlushBufferToFlash();
            return;
        }
		
        MemSet(gFlashBufferPos, FLASH_BLOCK_SIZE - gFlashBufferUsed, Value);
		Size -= FLASH_BLOCK_SIZE - gFlashBufferUsed;
        FlushBufferToFlash();
    }
}

//<AMI_PHDR_START>
//----------------------------------------------------------------------------
// Procedure: FillBufferAndFlush
//
// Description: Fill the rest of the buffer of a size of the flash block, then update the flash.
//
// Input:   IN UINT8 *Data - Pointer to starting of data to write to the flash.
//
// Output:  VOID
//
//----------------------------------------------------------------------------
//<AMI_PHDR_END>

VOID FillFlashBufferAndFlush(IN UINT8 *Data)
{
    if (gFlashBufferUsed != 0) {
        MemCpy(gFlashBufferPos, Data, FLASH_BLOCK_SIZE - gFlashBufferUsed);
        FwhErase((UINTN)gFlashBlk, FLASH_BLOCK_SIZE);
        FwhWrite(gFlashBuffer, (UINTN)gFlashBlk, FLASH_BLOCK_SIZE);
    }
}

//<AMI_PHDR_START>
//----------------------------------------------------------------------------
// Procedure: SMI_UC_DWORD_REGS
//
// Description: Write microcode to flash and load microcode into each CPU.
//
// Input: EFI_SMI_CPU_SAVE_STATE *Regs
//
// Output: VOID
//
//  Input:
//      AX    - D042h
//      BL    - 01h i.e., WRITE_UPDATE_DATA
//      ES:DI - Real Mode Pointer to the Intel Update structure.
//      CX    - Scratch Pad1 (Real Mode Scratch segment 64K in length)
//      DX    - Scratch Pad2 (Real Mode Scratch segment 64K in length)
//      SI    - Scratch Pad3 (Real Mode Scratch segment 64K in length)
//      SS:SP - Stack pointer (32K minimum)
//
//  Output:
//      CF  NC - All return values are valid
//          CY - Failure, AH contains status.
//
//      AH  Return code
//      AL  Additional OEM information
//
//----------------------------------------------------------------------------
//<AMI_PHDR_END>

VOID WriteUpdateData(SMI_UC_DWORD_REGS *Regs)
{
	EFI_STATUS Status;
    UINT8 *NewMcode = (UINT8*)(UINTN)((Regs->ES << 4) + (Regs->EDI & 0xFFFF));
    MICROCODE_HEADER *Header = (MICROCODE_HEADER*)NewMcode;
    INT32  NewMcodeAlignSize = MICROCODE_ALIGN_SIZE(NewMcode);
    INT32  NewMcodeSize = MICROCODE_SIZE(NewMcode);
    BOOLEAN Compact = FALSE;

    UINT8  *OldMcode;
    INT32  OldMcodeAlignSize;
    UINT8  *BlkStart;
    UINT8  *McodeUpdateStart;
    UINT8  *Buffer;
	
	Status = CheckAddressRange(NewMcode, NewMcodeAlignSize);
    if(EFI_ERROR(Status)) return;

    if (!IsValidHeader(Header)) {
        Regs->EFLAGS |= CARRY_FLAG;
        *(UINT16*)&Regs->EAX = UC_INVALID_HEADER;
        return;
    }

    if (!IsValidChecksum(NewMcode, NewMcodeSize)) {
        Regs->EFLAGS |= CARRY_FLAG;
        *(UINT16*)&Regs->EAX = UC_INVALID_HEADER_CS;
        return;
    }

    //Only update if microcode is for the installed CPU.
    if (Header->CpuSignature != gCpuSignature || !(Header->Flags & (1<<gCpuFlag))) {
        Regs->EFLAGS |= CARRY_FLAG;
        *(UINT16*)&Regs->EAX = UC_CPU_NOT_PRESENT;
        return;
    }

    //Only update a different revision.
    if (Header->UpdateRevision == gUcRevision) {
        Regs->EFLAGS |= CARRY_FLAG;
        *(UINT16*)&Regs->EAX = UC_INVALID_REVISION;
        return;
    }

    //If no microcode installed, then the revision is 0.
    if (gUcRevision != 0) { //Quick check.
        if(FindMicrocodeOfStepping(gMcodeFlashStartUpdate,
             gMcodeFlashStartUpdate + gMcodeFlashSizeUpdate,
             gCpuSignature
           ) != NULL) {
            Compact = TRUE;     //Remove old version.
        }
    }
    if (gFirstEmptyBlk == 0xffff || NewMcodeAlignSize > 
        (gMcodeFlashStartUpdate + gMcodeFlashSizeUpdate - gMcodeBlkMap[gFirstEmptyBlk].Addr)
    ) Compact = TRUE; //Volume is full.

    if (!Compact) {
        //Append blocks.
        UINT8  *pEmptyBlk = gMcodeBlkMap[gFirstEmptyBlk].Addr;
        LoadMicrocodeEachCpu(NewMcode);                //Install new microcode.

        //Check to see if new microcode is installed.
        if (Header->UpdateRevision != GetInstalledMicrocodeRevision()) {
            Regs->EFLAGS |= CARRY_FLAG;
            *(UINT16*)&Regs->EAX = UC_SECURITY_FAILURE;
            return;
        }

        FwhWrite(NewMcode, (UINTN)pEmptyBlk, NewMcodeSize);    //Currently ignoring status

        InitMcodeBlkMap();
        return;
    }

    //***Compact Flash Part***

    //Currently restrict FLASH_BLOCK_SIZE to 64k or smaller
    if (FLASH_BLOCK_SIZE > 64 * 1024) {
        Regs->EFLAGS |= CARRY_FLAG;
        *(UINT16*)&Regs->EAX = UC_NOT_IMPLEMENTED;
    }

    //Set up Buffer.
    Buffer = (UINT8*)(UINTN)((UINT16)Regs->ECX << 4);
	
	Status = CheckAddressRange(Buffer, FLASH_BLOCK_SIZE);
    if(EFI_ERROR(Status)) return;

    //Find existing microcode of same revision.
    McodeUpdateStart = gFirstEmptyBlk == 0xffff ? 
        gMcodeFlashStartUpdate + gMcodeFlashSizeUpdate : gMcodeBlkMap[gFirstEmptyBlk].Addr;

    OldMcode = FindMicrocodeOfStepping(
        gMcodeFlashStartUpdate,
        McodeUpdateStart,
        gCpuSignature
    );

    //Old Microcode not available to remove?
	if (!OldMcode) {
        Regs->EFLAGS |= CARRY_FLAG;
        *(UINT16*)&Regs->EAX = UC_STORAGE_FULL;
        return;
    }
    OldMcodeAlignSize = MICROCODE_ALIGN_SIZE(OldMcode);;

    //Check to see if space big enough for new microcode.
    if ((gMcodeFlashStartUpdate + gMcodeFlashSizeUpdate - McodeUpdateStart + OldMcodeAlignSize) <  NewMcodeAlignSize) {
        Regs->EFLAGS |= CARRY_FLAG;
        *(UINT16*)&Regs->EAX = UC_STORAGE_FULL;
        return;
    }

    //Load new microcode, if can't load exit.
    LoadMicrocodeEachCpu(NewMcode);    //Install new microcode.
    if (Header->UpdateRevision != GetInstalledMicrocodeRevision()) {
        Regs->EFLAGS |= CARRY_FLAG;
        *(UINT16*)&Regs->EAX = UC_SECURITY_FAILURE;
        return;
    }
    
    //Start compacting at block with Old Microcode to remove.
    BlkStart = (UINT8*)((UINTN)OldMcode & ~(FLASH_BLOCK_SIZE - 1)); //Must start at block boundary.

    //Note: When Buffer is full, it will flush to flash.
    InitializeFlashBuffer(BlkStart, Buffer);
    CopyToFlashBuffer(BlkStart, (UINT32)(OldMcode - BlkStart)); //Copy before old microcode.

	CopyToFlashBuffer(OldMcode + OldMcodeAlignSize, (UINT32)(McodeUpdateStart - (OldMcode + OldMcodeAlignSize)));  //Copy after old microcode.

	CopyToFlashBuffer(NewMcode, NewMcodeSize);     //Copy new microcode.

	WriteValueToFlashBuffer(0xff, NewMcodeAlignSize - NewMcodeSize);	//Fill block space after microcode.

	if (NewMcodeAlignSize < OldMcodeAlignSize) {
        WriteValueToFlashBuffer(0xff, OldMcodeAlignSize - NewMcodeAlignSize);   //Write 0xff over reclaimed space. Polarity?
	} else {
		McodeUpdateStart += NewMcodeAlignSize - OldMcodeAlignSize;
	}
	FillFlashBufferAndFlush(McodeUpdateStart);
        
    InitMcodeBlkMap();
}

//<AMI_PHDR_START>
//----------------------------------------------------------------------------
// Procedure:	MicrocodeUpdateCallback
//
// Description:	This notification function is called when an SMM Mode 
//              is invoked through SMI. This may happen during RT, 
//              so it must be RT safe.
//              Interrupt 15h, function D042h is processed here.
//
// Input:	    DispatchHandle  - EFI Handle
//              DispatchContext - Pointer to the EFI_SMM_SW_DISPATCH_CONTEXT
//
// Output:      Status code returned to function D042h caller.
//
//----------------------------------------------------------------------------
//<AMI_PHDR_END>

VOID MicrocodeUpdateCallback (
  IN  EFI_HANDLE                    DispatchHandle,
  IN  EFI_SMM_SW_DISPATCH_CONTEXT   *DispatchContext
  )
{
	EFI_STATUS  		Status;
    SMI_UC_DWORD_REGS   *Regs;
    SW_SMI_CPU_TRIGGER  *SwSmiCpuTrigger;
    UINTN   Cpu = pSmst->CurrentlyExecutingCpu - 1;
    UINT8   Function;
    UINTN   i;

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
    Regs = (SMI_UC_DWORD_REGS*)(UINTN)(pSmst->CpuSaveState[Cpu].Ia32SaveState.ESI);
	
	Status = CheckAddressRange((UINT8*)Regs, sizeof(SMI_UC_DWORD_REGS));
    if(EFI_ERROR(Status)) return;

    if ((UINT16)Regs->EAX != 0xD042) return;

    Function = (UINT8)Regs->EBX; //BL

    //Initialize return as successful.
    Regs->EFLAGS &= ~CARRY_FLAG;
    Regs->EAX &= 0xffff0000;

    if (Function >= MAX_MICROCODE_UPDATE_FUNCTIONS) {
        Regs->EFLAGS |= CARRY_FLAG;
        *(UINT16*)&Regs->EAX = UC_NOT_IMPLEMENTED;
        return;
    }

    MicrocodeUpdate[Function](Regs);
}

//<AMI_PHDR_START>
//----------------------------------------------------------------------------
// Procedure: InSmmFunction
//
// Description: This function is called from the InitSmmHandler if driver is in SMM.
//
// Input:   ImageHandle   - Pointer to the loaded image protocol for this driver
//          SystemTable   - Pointer to the EFI System Table     
//
// Output:  EFI_STATUS
//
//----------------------------------------------------------------------------
//<AMI_PHDR_END>

EFI_STATUS InSmmFunction(EFI_HANDLE ImageHandle, EFI_SYSTEM_TABLE *SystemTable)
{
	EFI_SMM_SW_DISPATCH_PROTOCOL	*pSwDispatch;
	EFI_SMM_SW_DISPATCH_CONTEXT		SwContext;
    EFI_STATUS  Status;
    EFI_HANDLE  Handle;
	SMM_HOB     *SmmHob;
    EFI_GUID    SmmHobGuid = SMM_HOB_GUID;
    EFI_GUID    HobListGuid = HOB_LIST_GUID;

    BOOLEAN IsInit = InitMicrocodeVariables();
    if (!IsInit) return EFI_UNSUPPORTED;

	Status	= pBS->LocateProtocol(&gEfiSmmSwDispatchProtocolGuid, NULL, &pSwDispatch);
	ASSERT_EFI_ERROR(Status);
	
	SmmHob = (SMM_HOB*)GetEfiConfigurationTable(pST, &HobListGuid);
    if (SmmHob == NULL) return EFI_NOT_FOUND;
	
    Status = FindNextHobByGuid(&SmmHobGuid,(VOID**)&SmmHob);
    if (EFI_ERROR(Status)) return Status;
	
    gSmmHob = *SmmHob;

    SwContext.SwSmiInputValue = INT15_D042_SWSMI;

	Status	= pSwDispatch->Register(pSwDispatch, MicrocodeUpdateCallback, &SwContext, &Handle);
	ASSERT_EFI_ERROR(Status);

    return EFI_SUCCESS;    
}

//<AMI_PHDR_START>
//----------------------------------------------------------------------------
// Procedure:	InitializeMicrocodeSmm
//
// Description: This function registers the INT15 D042 SW SMI handler
//              This is the driver entry pOoint.
//
// Input:       ImageHandle   - Pointer to the loaded image protocol for this driver
//              SystemTable   - Pointer to the EFI System Table     
//
// Output:      EFI_STATUS
//
//----------------------------------------------------------------------------
//<AMI_PHDR_END>

EFI_STATUS InitializeMicrocodeSmm(
	IN EFI_HANDLE           ImageHandle,
	IN EFI_SYSTEM_TABLE     *SystemTable
	)

{
	InitAmiLib(ImageHandle, SystemTable);
	return InitSmmHandler(ImageHandle, SystemTable, InSmmFunction, NULL);	
}

//*************************************************************************
//*************************************************************************
//**                                                                     **
//**        (C)Copyright 1987-2011, American Megatrends, Inc.            **
//**                                                                     **
//**                       All Rights Reserved.                          **
//**                                                                     **
//**      5555 Oakbrook Parkway, Suite 200, Norcross, GA 30093           **
//**                                                                     **
//**                       Phone: (770)-246-8600                         **
//**                                                                     **
//*************************************************************************
//*************************************************************************
