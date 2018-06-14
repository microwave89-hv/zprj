//*************************************************************************
//*************************************************************************
//**                                                                     **
//**        (C)Copyright 1985-2011, American Megatrends, Inc.            **
//**                                                                     **
//**                       All Rights Reserved.                          **
//**                                                                     **
//**      5555 Oakbrook Parkway, Suite 200, Norcross, GA 30093           **
//**                                                                     **
//**                       Phone: (770)-246-8600                         **
//**                                                                     **
//*************************************************************************
//*************************************************************************

//**********************************************************************
// $Header: /Alaska/Projects/Intel/Haswell/LynxPoint_SharkBay-DT_Crb_1AQQW/Core/EM/SMM/SmmInit.c 3     10/31/12 6:32a Wesleychen $
//
// $Revision: 3 $
//
// $Date: 10/31/12 6:32a $
//**********************************************************************
// Revision History
// ----------------
// $Log: /Alaska/Projects/Intel/Haswell/LynxPoint_SharkBay-DT_Crb_1AQQW/Core/EM/SMM/SmmInit.c $
// 
// 3     10/31/12 6:32a Wesleychen
// Move 'DisableSmmCallbacks' event from BDS_CONNECT_DRIVERS_PROTOCOL_GUID
// to BDS_ALL_DRIVERS_CONNECTED_PROTOCOL_GUID.
// 
// 8     1/05/12 1:54p Markw
// [TAG]  		EIP78457
// [Category]  	Bug Fix
// [Severity]  	Normal
// [Symptom]  	If BSP is switch, SMM may not bring all CPUs into SMM if
// not all CPUs are inside of SMM.
// [RootCause]  	During CPU initialization,  the sytem uses the actual BSP
// instead of BSP from the SMM HOB.
// This creates a inconsistentancy with the rest of the SMM numbering.
// [Solution]  	Use SMM HOB BSP value.
// [Files]  		SmmInit.c
// 
// 7     10/03/11 2:51p Markw
// Update StartupThisAP for PI 1.1.
// File: SmmInit.c
// 
// 6     6/22/11 11:55a Markw
// Separate DxeSmmReadyToLock from Protocol\SmmReadyToLock.h.
// 
// 
// 5     5/10/11 12:06p Markw
// [TAG]  		EIP60051
// [Category]  	Bug Fix
// [Severity]  	Critical
// [Symptom]  	With PI 1.1, BIOS may hang in DisableSmmCallbacks .
// [RootCause]  	DisableSmmCallbacks calls SmmDispatcher. This must be
// executed inside SMM.
// [Solution]  	Call SmmDispatcher inside SMM.
// [Files]  		SmmInit.c
// 
// 4     4/12/11 3:00p Markw
// [TAG]  		EIP57440
// [Category]  	New Feature
// [Description]  	PI Update allocated SMM BASE Protocol with boot
// services data. Change it to runtime services data.
// [Files]  		SmmInit.c
// 
// 3     4/01/11 10:07a Markw
// [TAG]  		EIP57440
// [Category]  	New Feature
// [Description]  	Add PI 1.1 SMM support for reading/writing floating
// point/smm save state.
// 
// [Files]  		CpuCspLib.h, CpuCspLib.c, SmmPiSmst.c,  SmmPrivateShared.h,
// SmmHdr.equ, SmmInit.c
// 
// 2     3/04/11 3:32p Markw
// Update headers.
// 
// 1     2/07/11 3:34p Markw
// [TAG]  		EIP53481
// [Category]  	New Feature
// [Description]  	Add PIWG 1.1 SMM support.
// Moved common initialization from SmmBase.c to SmmInit.c.
// [Files]  		Smm.sdl, SmmPrivateShared.h, SmmDispatcher.mak,
// SmmDispatcher.h, SmmDispatcher.c,
// Smst.c, SmmPiSmst.c, SmmInit.c, SmmBase.c, SmmBase2.c,
// SmmDriverDispatcher.c, Smm Framewwork Protocol files, SmmPi.h,
// Smm Pi Protocol files, SmmPciRbio files
// 
//**********************************************************************

//<AMI_FHDR_START>
//---------------------------------------------------------------------------
//
// Name:		SmmInit.c
//
// Description:	Dispatch SMM Drivers
//
//---------------------------------------------------------------------------
//<AMI_FHDR_END>

//This include should be first.
#include "SmmPrivateShared.h"
#include <AmiDxeLib.h>
#include "AmiCspLib.h"
#include <AmiSmm.h>
#include <AmiHobs.h>
#if USE_FV2
#include <Protocol\FirmwareVolume2.h>
#else
#include <Protocol\FirmwareVolume.h>
#endif
#include <Protocol\LoadPe32Image.h>
#include <Protocol\MpService.h>
#if SMM_THUNK_IN_CSM == 1
#include <Protocol\LegacyBiosExt.h>
#include <Protocol\LegacyBios.h>
#endif

#if SMM_USE_FRAMEWORK
#include <Protocol\SmmBase.h>
#endif

#if SMM_USE_PI
#include <Protocol\SmmBase2.h>
#include <Protocol\SmmReadyToLock.h>
#include <Protocol\DxeSmmReadyToLock.h>
#endif


#if SMM_USE_PI
#include <Protocol\SmmAccess2.h>
#include <Protocol\SmmControl2.h>
#else
#include <Protocol\SmmAccess.h>
#include <Protocol\SmmControl.h>
#endif

#include <Token.h>

// {3AA83745-9454-4f7a-A7C0-90DBD02FAB8E}
#define BDS_CONNECT_DRIVERS_PROTOCOL_GUID \
    { 0x3aa83745, 0x9454, 0x4f7a, { 0xa7, 0xc0, 0x90, 0xdb, 0xd0, 0x2f, 0xab, 0x8e } }
#define BDS_ALL_DRIVERS_CONNECTED_PROTOCOL_GUID \
    {0xdbc9fd21, 0xfad8, 0x45b0, 0x9e, 0x78, 0x27, 0x15, 0x88, 0x67, 0xcc, 0x93}

CPUINFO_HOB                     *gCpuinfoHob;
SMM_HOB                         *gSmmHob;
EFI_HOB_CPU                     *gCpuHob;
UINT32                          gBspSmmBase;
SMM_ENTRY_INIT_STRUCT           *gSmmEntryData;
SMM_BASE_PRIVATE_STRUCT         *gBasePrivate;
SMM_DISPATCHER_PRIVATE_STRUCT   *gDispatcherPrivate;
EFI_PE32_IMAGE_PROTOCOL         *gPe32Image;
EFI_MP_SERVICES_PROTOCOL        *gMpServices;


#if SMM_USE_FRAMEWORK
EFI_SMM_SYSTEM_TABLE            *gSmstTable;
#endif

#if SMM_USE_PI
EFI_SMM_SYSTEM_TABLE2           *gSmstTable2;
#endif

#if SMM_USE_PI
EFI_SMM_CONTROL2_PROTOCOL       *gSmmControl;
EFI_SMM_ACCESS2_PROTOCOL        *gSmmAccess;
#else
EFI_SMM_CONTROL_PROTOCOL        *gSmmControl;
EFI_SMM_ACCESS_PROTOCOL         *gSmmAccess;
#endif


#if SMM_THUNK_IN_CSM == 1
EFI_LEGACY_BIOS_PROTOCOL        *gLegacyBios;
EFI_LEGACY_BIOS_EXT_PROTOCOL    *gLegacyBiosExt;
#endif

EFI_HANDLE                      gThisImageHandle;

EFI_GUID gHobListGuid               = HOB_LIST_GUID;
EFI_GUID gSmmHobGuid                = SMM_HOB_GUID;
EFI_GUID gCpuinfoHobGuid            = AMI_CPUINFO_HOB_GUID;
EFI_GUID gEfiPe32ImageProtocolGuid  = PE32_IMAGE_PROTOCOL_GUID;
EFI_GUID gEfiMpServicesProtocolGuid = EFI_MP_SERVICES_PROTOCOL_GUID;
EFI_GUID gBdsConnectDriversProtocolGuid = BDS_CONNECT_DRIVERS_PROTOCOL_GUID;
EFI_GUID gBdsAllDriversConnectedProtocolGuid = BDS_ALL_DRIVERS_CONNECTED_PROTOCOL_GUID;
#if SMM_USE_PI
EFI_GUID gEfiEventDxeDispatchGuid   = EFI_EVENT_GROUP_DXE_DISPATCH;
//EFI_GUID gEfiDxeSmmReadyToLockProtocolGuid = EFI_DXE_SMM_READY_TO_LOCK_PROTOCOL_GUID;
#endif

#if USE_FV2
EFI_GUID gEfiFVProtocolGuid         = EFI_FIRMWARE_VOLUME2_PROTOCOL_GUID;
#else
EFI_GUID gEfiFVProtocolGuid         = EFI_FIRMWARE_VOLUME_PROTOCOL_GUID;
#endif

#if SMM_THUNK_IN_CSM == 1
EFI_GUID gEfiLegacyBiosProtocolGuid    = EFI_LEGACY_BIOS_PROTOCOL_GUID;
EFI_GUID gEfiLegacyBiosExtProtocolGuid = EFI_LEGACY_BIOS_EXT_PROTOCOL_GUID;
#endif

#if SMM_USE_FRAMEWORK
extern EFI_SMM_BASE_PROTOCOL gEfiSmmBase;
#endif

#if SMM_USE_PI
extern EFI_SMM_BASE2_PROTOCOL gEfiSmmBase2;
#endif

UINT32                  gBspSmmBase;
SMM_ENTRY_INIT_STRUCT   *gSmmEntryData;
UINTN gBsp;

EFI_GUID SmmEntryGuid = 
    {0xD2596F82,0xF0E1,0x49fa,0x95,0xBC,0x62,0x01,0x2C,0x79,0x57,0x28};
    //D2596F82-F0E1-49fa-95BC-62012C795728
EFI_GUID gEfiSmmCoreDispatcherGuid =
    {0x4A37320B,0x3FB3,0x4365,0x97,0x30,0x9e,0x89,0xC6,0x00,0x39,0x5D};
    //4A37320B-3FB3-4365-9730-9E89C600395D

VOID SmmDispatcher();
VOID SetDisallowRegistering();
VOID SmmDriverDispatchHandler();

extern UINT32 InSmmFuncLength;
extern UINT32 InSmmFuncOffset;

EFI_STATUS EfiSmmInSmm(
    IN EFI_SMM_BASE_PROTOCOL    *This,
    OUT BOOLEAN                 *InSmm
);

//
// This is the structure contains default values in Boot Services memory.
// This table will be updated and copied into Runtime memory.
//
SMM_BASE_PRIVATE_STRUCT gSmmBasePrivateStruct =
{
    0,      //*CallBackFunc
    FALSE,  //InSmm
    FALSE   //DisallowCallbacks
    //Additional members not specified.
};


//<AMI_PHDR_START>
//----------------------------------------------------------------------------
//
// Procedure: CallFuncInSmm
//
// Description:  Call function in SMM. If not in SMM, generate SW SMI, otherwise
//   call the function.
//
// Input: IN func -- Pointer to function
//
// Output: VOID
//
//----------------------------------------------------------------------------
//<AMI_PHDR_END>

VOID CallFuncInSmm(IN VOID func())
{
    if (!*gBasePrivate->InSmm) {
#if SMM_USE_PI
        UINT8   CommandPort = SMMBASE_CALLBACK;
#else
        UINT8   ArgBuffer = SMMBASE_CALLBACK;
        UINTN   ArgBufferSize = 1;
#endif
        gBasePrivate->CallBackFunc = func;

        //Generate SW SMI
#if SMM_USE_PI
        gSmmControl->Trigger(gSmmControl, &CommandPort, NULL, FALSE, 0);
#else
        gSmmControl->Trigger(gSmmControl, &ArgBuffer, &ArgBufferSize, FALSE, 0);
#endif
        //This is cleared inside of SMM.
    } else {
        func();
    }
}


//<AMI_PHDR_START>
//----------------------------------------------------------------------------
// Procedure: FindMatchingMtrr
//
// Description: Search MTRRs for a matching MTRR.
//
// Input:
//      IN UINT64 BASE
//      IN UINT64 Mask
//
// Output:
//      UINT32  -- MSR for matching MTTR.
//
//----------------------------------------------------------------------------
//<AMI_PHDR_END>

#if SMM_CACHE_SUPPORT == 1
#ifndef NEHALEM_CPU_MODULE
VOID InitSmmCacheData()
{
    UINT32  Msr;
    UINT32  i;
    UINT8   NumMtrrs = (UINT8)ReadMsr(0xfe);                //MSR_IA32_MTRR_CAP
    UINT32  RegEAX, RegEBX, RegECX, RegEDX;   
    UINT8   NumOfMemoryBits = 36;
    UINT64  MemoryMask;

    CPULib_CpuID(0x80000008, &RegEAX, &RegEBX, &RegECX, &RegEDX);
    //Check if CPU supports this CPUID.
    if (RegEAX != 0 && RegEAX != 0xffffffff)
        NumOfMemoryBits = (UINT8)RegEAX & 0xff;

    MemoryMask = Shl64(1, NumOfMemoryBits)- 1;

    gDispatcherPrivate->SmrrEnable  = FALSE;
    gDispatcherPrivate->SmrrMsr = GetSmrrBaseMsr();
    gDispatcherPrivate->TsegMsr = 0;
    gDispatcherPrivate->TsegMsrBase  = (UINT64)(UINTN)gSmmHob->Tseg;
    gDispatcherPrivate->TsegMsrMask  = (MemoryMask & (~(TSEG_SIZE - 1))) | (1 << 11);

    //MSRs will not be found if there is not enough MSRs for caching SMM.

    for(i = 0, Msr = 0x200; i < NumMtrrs; ++i, Msr+=2) {    //MTRR_PHYS_BASE_0
        if ((ReadMsr(Msr) & ~(UINT64)0xff) == gDispatcherPrivate->TsegMsrBase
            && ReadMsr(Msr+1) == gDispatcherPrivate->TsegMsrMask
        ) {
            gDispatcherPrivate->TsegMsr = Msr;            
        }
    }

  if (CPULib_IsSmrrEnabled()) gDispatcherPrivate->SmrrEnable = TRUE;
}
#endif
#endif

//<AMI_PHDR_START>
//----------------------------------------------------------------------------
//
// Procedure: LoadRealModeFile
//
// Description:	Load a real mode file into a buffer.
//
// Input: 
//	IN EFI_GUID *Guid
//	OUT VOID    **Buffer
//	OUT UINTN   *BufferSize
//
// Output: EFI_STATUS
//
//----------------------------------------------------------------------------
//<AMI_PHDR_END>

EFI_STATUS LoadRealModeFile(EFI_GUID *Guid, VOID **Buffer, UINTN *BufferSize)
{
#if USE_FV2
    EFI_FIRMWARE_VOLUME2_PROTOCOL   *Fv;
#else
    EFI_FIRMWARE_VOLUME_PROTOCOL    *Fv;
#endif
    UINT32      Authentication;
    EFI_STATUS  Status;
    UINTN       NumHandles;
    EFI_HANDLE  *HandleBuffer;
    UINTN       i;

    *Buffer=0;
    *BufferSize=0;

    Status = pBS->LocateHandleBuffer(ByProtocol,&gEfiFVProtocolGuid,NULL,&NumHandles,&HandleBuffer);
    if (EFI_ERROR(Status)) return Status;

    for (i = 0; i< NumHandles; ++i) {
        Status = pBS->HandleProtocol(HandleBuffer[i],&guidFV,&Fv);
        if (EFI_ERROR(Status)) continue;

        Status = Fv->ReadSection(Fv,
            Guid,
            EFI_SECTION_RAW,
            0,              //Instance
            Buffer,
            BufferSize,
            &Authentication);

        if (Status == EFI_SUCCESS) break;
    }

    pBS->FreePool(HandleBuffer);
    return Status;
}

//<AMI_PHDR_START>
//----------------------------------------------------------------------------
//
// Procedure: EarlyAllocSmmMemory
//
// Description:	Allocate SMM memory before SMM memory manager available.
//
// Input: 
//  IN UINT32   Size -- Memory size
//
// Output: VOID * -- ptr to allocated memory.
//
//----------------------------------------------------------------------------
//<AMI_PHDR_END>

VOID * EarlyAllocSmmMemory(IN UINT32 Size)
{
    UINT8 *AllocatedAddress;
    UINT32 AdjSize;

    AdjSize = (Size + 7) & ~7;  //Minimum 8 bytes.
    if (AdjSize > gBasePrivate->SmmAllocMemoryLength) return 0;

    AllocatedAddress = (UINT8*)gBasePrivate->SmmAllocMemoryStart;
    gBasePrivate->SmmAllocMemoryStart = AllocatedAddress + AdjSize;
    gBasePrivate->SmmAllocMemoryLength -= AdjSize;

    return AllocatedAddress;
}

//<AMI_PHDR_START>
//----------------------------------------------------------------------------
//
// Procedure: EarlyAllocSmmMemoryAlign
//
// Description:
//  Allocate SMM memory before SMM memory manager available with specified alignment.
//  Memory address returned will be the next aligned address available and the free memory
//  before the aligned address can not be allocated.
//
// Input: 
//	IN UINT32	Size -- Memory size.
//	IN UINT32   Align -- Alignment. Must be 2^n.
//
// Output: VOID * -- ptr to allocated memory.
//
//----------------------------------------------------------------------------
//<AMI_PHDR_END>

VOID * EarlyAllocSmmMemoryAlign(IN UINT32 Size, IN UINT32 Align)
{
    UINT8* AllocatedAddress;
    UINT8 *OrigAddress;
    UINT32 AdjSize;
    
    AdjSize = (Size + 7) & ~7;  //Minimum 8 bytes.
    if (AdjSize > gBasePrivate->SmmAllocMemoryLength) return 0;

    OrigAddress = (UINT8*)gBasePrivate->SmmAllocMemoryStart;
    AllocatedAddress = (UINT8*)(((UINT32)OrigAddress + (Align - 1)) & ~(Align - 1));
    
    gBasePrivate->SmmAllocMemoryStart = AllocatedAddress + AdjSize;
    gBasePrivate->SmmAllocMemoryLength -= (UINT32)(AllocatedAddress + AdjSize - OrigAddress);

    return AllocatedAddress;
}

//SMM thunk either requires AB Segment of CSM.
#if SMM_THUNK_NO_AB_SEG == 0 || SMM_THUNK_IN_CSM == 1


//<AMI_PHDR_START>
//----------------------------------------------------------------------------
//
// Procedure: CopySmmThunkAfterBspEntry
//
// Description:
//	Copy SMM Thunk to immediately after SMM BSP entry.
//
// Input: 
//  IN VOID       *SmmEntryBuffer -- pointer to SMM Entry file
//  IN UINTN      SmmEntryBufferSize -- Size of SMM Entry file
//
// Output: EFI_STATUS
//
//----------------------------------------------------------------------------
//<AMI_PHDR_END>

EFI_STATUS CopySmmThunkAfterBspEntry (
    IN VOID       *SmmEntryBuffer,
    IN UINTN      SmmEntryBufferSize
)
{
    UINT8       *SmmThunkStart = (UINT8*)gBspSmmBase + 0x8000 + gSmmEntryData->SmmThunkProcOffset;
    UINT16      AdrFixup;
    UINT16      SegFixup;

    *(UINT32*)(gBspSmmBase + 0x8000 + gSmmEntryData->LCodeSelBaseOffset) += (UINT32)SmmThunkStart;
    *(UINT32*)((UINT8*)SmmEntryBuffer + gSmmEntryData->LCodeSelBaseOffset) += (UINT32)SmmThunkStart;

    MemCpy(SmmThunkStart,
        (UINT8*)SmmEntryBuffer + gSmmEntryData->SmmThunkProcOffset,
        gSmmEntryData->SmmThunkLength
    );

    gDispatcherPrivate->SmmThunkProc = (VOID(*)())SmmThunkStart;

    gDispatcherPrivate->SmmThunkData = (SMM_THUNK_DATA*)
        (((UINTN)SmmThunkStart + gSmmEntryData->SmmThunkLength + 16) & ~0xf);
    
    ASSERT(((UINTN)gDispatcherPrivate->SmmThunkData & 0xf) == 0);

    //Update Thunk to set Smm Thunk Data.
    AdrFixup = *(UINT16*)(SmmThunkStart + 2);
    SegFixup = *(UINT16*)(SmmThunkStart + 4);
   
    *(UINT32*)(SmmThunkStart + AdrFixup) = (UINT32)gDispatcherPrivate->SmmThunkData;
    *(UINT16*)(SmmThunkStart + SegFixup) = (UINT16)((UINT32)gDispatcherPrivate->SmmThunkData >> 4);

    //Max 4k of stack.
        //In this case, code, data, and stack in this 4k block.
        //The ss=ds, and points to the end of the code,
        // so code will have to be subtracted from the 4k top,
        // so ss:sp = cs:1000h
    gDispatcherPrivate->SmmThunkData->Below1MStack = 
        0x1000
         - gSmmEntryData->SmmEntrySize
         - gSmmEntryData->SmmThunkLength
         - 0xf; //Could be up to 15 bytes skipped for alignment purposes;
    gDispatcherPrivate->SmmThunkData->Below1MStack &= ~1;  //Align on word bounary;

    gDispatcherPrivate->SmmThunkData->LegacyIdtDesc.Limit = 0x3ff;
    gDispatcherPrivate->SmmThunkData->LegacyIdtDesc.Base = 0;

    return EFI_SUCCESS;
}

//<AMI_PHDR_START>
//----------------------------------------------------------------------------
//
// Procedure: CopySmmThunkAtStartABSegment
//
// Description:
//	Copy SMM Thunk to start of AB Segment
//
// Input: 
//  IN VOID       *SmmEntryBuffer -- pointer to SMM Entry file
//  IN UINTN      SmmEntryBufferSize -- Size of SMM Entry file
//
// Output: EFI_STATUS
//
//----------------------------------------------------------------------------
//<AMI_PHDR_END>

EFI_STATUS CopySmmThunkAtStartABSegment(
    IN VOID  	*SmmEntryBuffer,
    IN UINTN  	SmmEntryBufferSize
)
{
    UINT8       *SmmThunkStart;
    UINT16      AdrFixup;
    UINT16      SegFixup;

#if SMM_EXCLUDE_A000 != 1
    SmmThunkStart = (UINT8*)0xa0000;
#else
    SmmThunkStart = (UINT8*)0xb0000;
#endif

   *(UINT32*)(gBspSmmBase + 0x8000 + gSmmEntryData->LCodeSelBaseOffset) += (UINT32)SmmThunkStart;

//TODO: remove and share GDT between all CPUs. CPU0 is already copied. CPUx will copy this buffer later.
    *(UINT32*)((UINT8*)SmmEntryBuffer + gSmmEntryData->LCodeSelBaseOffset) += (UINT32)SmmThunkStart;


    MemCpy(SmmThunkStart,
        (UINT8*)SmmEntryBuffer + gSmmEntryData->SmmThunkProcOffset,
        gSmmEntryData->SmmThunkLength
    );

    gDispatcherPrivate->SmmThunkProc = (VOID(*)())SmmThunkStart;

    //SmmThunkData must be aligned on 16 byte boundary.
    gDispatcherPrivate->SmmThunkData = (SMM_THUNK_DATA*)
        (((UINTN)SmmThunkStart + gSmmEntryData->SmmThunkLength + 16) & ~0xf);
    ASSERT(((UINTN)gDispatcherPrivate->SmmThunkData & 0xf) == 0);
   
    //Update Thunk to set Smm Thunk Data.
    AdrFixup = *(UINT16*)(SmmThunkStart + 2);
    SegFixup = *(UINT16*)(SmmThunkStart + 4);
   
    *(UINT32*)(SmmThunkStart + AdrFixup) = (UINT32)gDispatcherPrivate->SmmThunkData;
    *(UINT16*)(SmmThunkStart + SegFixup) = (UINT16)((UINT32)gDispatcherPrivate->SmmThunkData >> 4);

    //Max 4k of stack.
    //If in SMM, 1 block is reserved for stack and data.
    gDispatcherPrivate->SmmThunkData->Below1MStack = 
        0x1000
         - gSmmEntryData->SmmThunkLength
         - 0xf; //Could be up to 15 bytes skipped for alignment purposes;
    gDispatcherPrivate->SmmThunkData->Below1MStack &= ~1;  //Align on word boundary;

    gDispatcherPrivate->SmmThunkData->LegacyIdtDesc.Limit = 0x3ff;
    gDispatcherPrivate->SmmThunkData->LegacyIdtDesc.Base = 0;
    return EFI_SUCCESS;
}

#if SMM_THUNK_IN_CSM == 1
//<AMI_PHDR_START>
//----------------------------------------------------------------------------
//
// Procedure: CopySmmThunkInCsmEBDA
//
// Description:
//	Copy SMM Thunk to CSM. Data will be in EBDA.
//
// Input: 
//	IN VOID       *SmmEntryBuffer -- pointer to SMM Entry file
//	IN UINTN      SmmEntryBufferSize -- Size of SMM Entry file
//
// Output: EFI_STATUS
//
//----------------------------------------------------------------------------
//<AMI_PHDR_END>

EFI_STATUS CopySmmThunkInCsmEBDA (
    VOID        *SmmEntryBuffer,
    UINTN       SmmEntryBufferSize
)
{
    UINT8       *SmmThunkStart;
    UINT16      AdrFixup;
    UINT16      SegFixup;
    UINT32      EbdaStart;
    EFI_STATUS  Status;

    //Initialize this with the pointer to the Buffer in memory.
    //This will be update later to the newly allocated region.
    SmmThunkStart = (UINT8*)SmmEntryBuffer + gSmmEntryData->SmmThunkProcOffset;

    //In case this is 64-bits, initialize upper 32-bits to 0.
    //Allocate Ebda, updates only the lower 32-bits.
    gDispatcherPrivate->SmmThunkData = 0; 

    Status = gLegacyBiosExt->AllocateEbda(
        gLegacyBiosExt,
        4,
        (UINT32*)&gDispatcherPrivate->SmmThunkData,
        &gDispatcherPrivate->EbdaStartOffset
    );
    if (EFI_ERROR(Status)) return Status;

    EbdaStart = (*(UINT16*)(0x40e)) << 4;

    //Max 4k of stack.
    //If in SMM, 1 block is reserved for stack and data.
    gDispatcherPrivate->SmmThunkData->Below1MStack = 0x1000;

    gDispatcherPrivate->SmmThunkData->LegacyIdtDesc.Limit = 0x3ff;
    gDispatcherPrivate->SmmThunkData->LegacyIdtDesc.Base = 0;

    AdrFixup = *(UINT16*)(SmmThunkStart + 2);
    SegFixup = *(UINT16*)(SmmThunkStart + 4);
   
    *(UINT32*)(SmmThunkStart + AdrFixup) = (UINT32)gDispatcherPrivate->SmmThunkData - EbdaStart;
    *(UINT16*)(SmmThunkStart + SegFixup) = (UINT16)(((UINT32)gDispatcherPrivate->SmmThunkData - EbdaStart) >> 4);

    //Allocate CSM memory.
    Status = gLegacyBios->GetLegacyRegion(
        gLegacyBios,
        gSmmEntryData->SmmThunkLength,
        0, //In e_0000 - f_ffff.
        1, //Byte alignment
        &SmmThunkStart
    );
    if (EFI_ERROR(Status)) return Status;

   	*(UINT32*)(gBspSmmBase + 0x8000 + gSmmEntryData->LCodeSelBaseOffset) += (UINT32)SmmThunkStart;
  	*(UINT32*)((UINT8*)SmmEntryBuffer + gSmmEntryData->LCodeSelBaseOffset) += (UINT32)SmmThunkStart;

	//Copy to CSM memory.
    Status = gLegacyBios->CopyLegacyRegion(
                gLegacyBios,
                gSmmEntryData->SmmThunkLength,
                SmmThunkStart,
                (UINT8*)SmmEntryBuffer + gSmmEntryData->SmmThunkProcOffset
    );
    ASSERT_EFI_ERROR(Status);

    gDispatcherPrivate->SmmThunkProc = (VOID(*)())SmmThunkStart;

    ASSERT(((UINTN)gDispatcherPrivate->SmmThunkData & 0xf) == 0);

    //Max 4k of stack.
    gDispatcherPrivate->SmmThunkData->Below1MStack = 0x1000;

    gDispatcherPrivate->SmmThunkData->LegacyIdtDesc.Limit = 0x3ff;
    gDispatcherPrivate->SmmThunkData->LegacyIdtDesc.Base = 0;

    return EFI_SUCCESS;
}
#endif
#endif

//<AMI_PHDR_START>
//----------------------------------------------------------------------------
//
// Procedure: LoadAndInitDispatcherImages
//
// Description:	Load and initialize dispatcher images.
//
// Input: 
//	IN EFI_SYSTEM_TABLE SystemTable
//	IN UINT32           NumCpus
//
// Output: VOID
//
//----------------------------------------------------------------------------
//<AMI_PHDR_END>

VOID LoadAndInitDispatcherImages(
    IN EFI_SYSTEM_TABLE *SystemTable,
	IN UINT32           NumCpus
)
{
    EFI_STATUS	Status;
    VOID        *SmmEntryBuffer;
    UINTN       SmmEntryBufferSize;
    VOID        *SmmBaseSaveBuffer;
    VOID        *Buffer;
    UINTN       BufferSize;
    UINT32      AuthenticationStatus;
    UINT8       *SmmBase;
    UINT8       *ApStackTop;
    UINT16      Bsp = gSmmHob->Bsp;
    UINT32      i;
    UINT32      TssBaseAddress;

    SMM_ENTRY_INIT_STRUCT   *SmmApEntryInit;
    EFI_PHYSICAL_ADDRESS    EntryPoint;
    EFI_HANDLE ImageHandle;

    CPU_SmmMemoryInit(gSmmHob);

    //
    // Load BSP SMM real mode.
    // This must be done before loading protected mode dispatcher
    //  because the entry point of the protected mode dispatcher
    //  initializes some of SMM real mode variables.
    //

    Status = LoadRealModeFile(&SmmEntryGuid, &SmmEntryBuffer, &SmmEntryBufferSize);
    ASSERT_EFI_ERROR(Status);

    SmmBase = (UINT8*)gBspSmmBase;
    MemCpy(SmmBase+0x8000, SmmEntryBuffer, ((SMM_ENTRY_INIT_STRUCT*)((UINT8*)SmmEntryBuffer+4))->SmmEntrySize);

    gSmmEntryData->CpuNo         = 0;
    gSmmEntryData->SmmEntryStart = (VOID*)(SmmBase + 0x8000);
    gSmmEntryData->DispatcherPrivate    = gDispatcherPrivate;

    *(UINT32*)(SmmBase + 0x8000 + gSmmEntryData->GdtDescBaseOffset) += gBspSmmBase + 0x8000;

    TssBaseAddress=*(UINT16*)(SmmBase + 0x8000 + gSmmEntryData->TssSelBaseOffset) + gBspSmmBase + 0x8000;
    *(UINT16*)(SmmBase + 0x8000 + gSmmEntryData->TssSelBaseOffset)  = TssBaseAddress;
    *(UINT8*)(SmmBase + 0x8000 + gSmmEntryData->TssSelBaseOffset+2)  = TssBaseAddress>>16;
    *(UINT8*)(SmmBase + 0x8000 + gSmmEntryData->TssSelBaseOffset+5)  = TssBaseAddress>>24;


    gDispatcherPrivate->EbdaStartOffset = 0;    //CopySmmThunkInCsmEBDA will update this.
//SMM thunk either requires AB Segment of CSM.
#if SMM_THUNK_NO_AB_SEG == 0 || SMM_THUNK_IN_CSM == 1
#if SMM_THUNK_IN_CSM == 0
    if (gBspSmmBase < 0x100000)
        CopySmmThunkAfterBspEntry(SmmEntryBuffer, SmmEntryBufferSize);
    else 
        CopySmmThunkAtStartABSegment(SmmEntryBuffer, SmmEntryBufferSize);
#else
    CopySmmThunkInCsmEBDA(SmmEntryBuffer, SmmEntryBufferSize);
#endif
#endif

#ifdef EFIx64
    //Setup pages for virtual memory after Stack.

    //align page directories to 4k.
    {
        UINT8   *PageTable;
        UINT32  NumAddrLines = gCpuHob->SizeOfMemorySpace;

        if (NumAddrLines > SMM_PAGING_MAX_ADDRESS_LINES) NumAddrLines = SMM_PAGING_MAX_ADDRESS_LINES;

        PageTable = EarlyAllocSmmMemoryAlign(GetPageTableNumPages(NumAddrLines) * 4096, 4096);
        ASSERT(PageTable);
        FillPageTable(NumAddrLines, PageTable);
        gDispatcherPrivate->PageDirectories = PageTable;
    }
#endif

    //
    // Load and call entry of protected mode dispatcher.
    // This must be done before AP real mode entry point because
    //  the protected mode init provides a pointer for the AP real mode
    //  to call after switching to protected mode.

    Buffer = 0;
    Status = FvReadPe32Image(
        &gEfiSmmCoreDispatcherGuid,&Buffer,&BufferSize,
        &AuthenticationStatus);
    ASSERT_EFI_ERROR(Status);

    gBasePrivate->Pe32DispatcherImage  =
        (VOID*)(((UINTN)gBasePrivate->SmmAllocMemoryStart + 4095) & ~4095);
    gBasePrivate->Pe32DispatcherImageSize=EFI_SIZE_TO_PAGES(gSmmHob->ManagedMemSize);

    Status=gPe32Image->LoadPeImage(
        gPe32Image, gThisImageHandle,
        NULL,               //Either DevicePath or
        Buffer, BufferSize, //Buffer. This will be zero if DevicePath.
        (EFI_PHYSICAL_ADDRESS)gBasePrivate->Pe32DispatcherImage,
        &gBasePrivate->Pe32DispatcherImageSize, &ImageHandle,
        &EntryPoint, EFI_LOAD_PE_IMAGE_ATTRIBUTE_NONE
    );
    ASSERT_EFI_ERROR(Status);

    gBasePrivate->Pe32DispatcherImageSize=EFI_PAGES_TO_SIZE(gBasePrivate->Pe32DispatcherImageSize);

    pBS->FreePool(Buffer);
//
// Give control to protected mode dispatcher. The dispatcher is in SMM memory,
// however, the CPU is NOT in SMM mode. Currently SMM space is open.
//
    if (!EFI_ERROR(Status)) {
        TRACE((TRACE_ALWAYS,"SMM.SmmDispatcher.Entry(%lX)\n",EntryPoint));
        Status =  ((DISPATCHER_ENTRY_POINT)EntryPoint)(
                ImageHandle,
                SystemTable,
                gBasePrivate,
                gDispatcherPrivate,
#if SMM_USE_FRAMEWORK
                &gSmstTable,
#else
                NULL,
#endif
#if SMM_USE_PI
                &gSmstTable2
#else
                NULL
#endif
        );
    }
    ASSERT_EFI_ERROR(Status);

    gSmmEntryData->SmmStackTop = (VOID*)(gSmmHob->ManagedMemStart + BSP_SMM_STACK_SIZE);

    //Copy ApCode to SMM region.

    ApStackTop = gSmmEntryData->SmmStackTop + AP_SMM_STACK_SIZE;

    for (i = 0; i < NumCpus; ++i) {
        static UINT32 ApNum = 0; //BSP is given CPU #0, and APs 1,2...

        if (i == Bsp) continue;
        ++ApNum;
        SmmBase = (VOID*)gSmmHob->SmmBase[i];
        MemCpy(SmmBase + 0x8000, SmmEntryBuffer, SmmEntryBufferSize);
        SmmApEntryInit = (SMM_ENTRY_INIT_STRUCT*) (SmmBase + 0x8004);
        SmmApEntryInit->SmmEntryStart       = SmmBase + 0x8000;
        SmmApEntryInit->DispatcherEntry     = gSmmEntryData->DispatcherEntry;
        SmmApEntryInit->DispatcherPrivate   = gDispatcherPrivate;
        SmmApEntryInit->SmmStackTop         = ApStackTop;
        SmmApEntryInit->CpuNo               = ApNum;

        *(UINT32*)(SmmApEntryInit->GdtDescBaseOffset + SmmBase + 0x8000)
             += (UINT32)SmmBase + 0x8000;

        TssBaseAddress=(UINT32)((*(UINT16*)(SmmBase + 0x8000 + SmmApEntryInit->TssSelBaseOffset)) + (SmmBase + 0x8000));
        *(UINT16*)(SmmBase + 0x8000 + SmmApEntryInit->TssSelBaseOffset)  = TssBaseAddress;
        *(UINT8*)(SmmBase + 0x8000 + SmmApEntryInit->TssSelBaseOffset+2)  = (TssBaseAddress>>16);
        *(UINT8*)(SmmBase + 0x8000 + SmmApEntryInit->TssSelBaseOffset+5)  = (TssBaseAddress>>24);

        ApStackTop += AP_SMM_STACK_SIZE;
    }

    pBS->FreePool(SmmEntryBuffer);

    SmmBaseSaveBuffer = Malloc(SmmGetBaseSaveBufferSize());
    ASSERT(SmmBaseSaveBuffer);

    SmmSetupDefaultHandler(SmmBaseSaveBuffer, gSmmHob);

    for (i = 0; i < gSmmHob->NumCpus; ++i) {
        if (i == gBsp) {
            SmmBaseChangeOnCpu((VOID*)gSmmHob->SmmBase[i]);
            continue;
        }
    
        gMpServices->StartupThisAP(
            gMpServices,
            SmmBaseChangeOnCpu,
            i,  //Cpu
            NULL,
            0,
            (VOID*)gSmmHob->SmmBase[i]
#if !(PI_SPECIFICATION_VERSION < 0x0001000A || BACKWARD_COMPATIBLE_MODE && defined(NO_PI_MP_SERVICES_SUPPORT))
            , NULL
#endif
        );
    }

    SmmRemoveDefaultHandler(SmmBaseSaveBuffer);
    pBS->FreePool(SmmBaseSaveBuffer);
}

VOID InitgBasePrivate()
{
    UINT32 NumCpus =  gSmmHob->NumCpus;
    gBasePrivate->SmmHob = gSmmHob;
    gBasePrivate->CallBackFunc = 0;
    gBasePrivate->SmmAllocMemoryStart =
        (VOID*) (gSmmHob->ManagedMemStart + BSP_SMM_STACK_SIZE + AP_SMM_STACK_SIZE * (NumCpus - 1));
    gBasePrivate->SmmAllocMemoryLength = 
        gSmmHob->ManagedMemSize - BSP_SMM_STACK_SIZE - AP_SMM_STACK_SIZE * (NumCpus - 1);
}

VOID InitgDispatcherPrivate()
{
    UINT8  i;
    UINT32 SmmNum;
    UINT32 NumCpus = gSmmHob->NumCpus;
    UINT8  *XmmSaveBase;

    gDispatcherPrivate = EarlyAllocSmmMemory(sizeof(*gDispatcherPrivate));
    ASSERT(gDispatcherPrivate);
    
    gDispatcherPrivate->NumCpus = NumCpus;
    gDispatcherPrivate->NumCpusInSmm = 0;
    gDispatcherPrivate->HandlerListHead = NULL;
    gDispatcherPrivate->FloatingPointSave = FALSE;

    //Allocate a XMM Save Restore on a 16-byte boundary
    XmmSaveBase = EarlyAllocSmmMemoryAlign(NumCpus * 512, 16);
    gDispatcherPrivate->SmmXmmSave = EarlyAllocSmmMemory(NumCpus * sizeof(VOID*));
    for (i = 0; i < NumCpus; ++i) {
        gDispatcherPrivate->SmmXmmSave[i] = XmmSaveBase;
        XmmSaveBase += 512;
    }

    //Initialize SmmCpuInfo
    gDispatcherPrivate->SmmCpuInfo = EarlyAllocSmmMemory(sizeof(SMM_CPU_INFO) * NumCpus);
    ASSERT(gDispatcherPrivate->SmmCpuInfo);
    MemSet(gDispatcherPrivate->SmmCpuInfo, sizeof(SMM_CPU_INFO) * NumCpus, 0);

    gDispatcherPrivate->SmmCpuInfo[0].ApicId = gCpuinfoHob->Cpuinfo[gSmmHob->Bsp].ApicId;

    SmmNum = 1;
    for (i = 0; i < NumCpus; ++i) {
        if (i == gSmmHob->Bsp) continue;
        gDispatcherPrivate->SmmCpuInfo[SmmNum].ApicId = gCpuinfoHob->Cpuinfo[i].ApicId;
        ++SmmNum;
    }

	//Initialize AP control for multi-threaded SMM.
    gDispatcherPrivate->SmmApCpuControl = EarlyAllocSmmMemory(sizeof(SMM_AP_CPU_CONTROL) * NumCpus);
    ASSERT(gDispatcherPrivate->SmmApCpuControl);
    MemSet((VOID*)gDispatcherPrivate->SmmApCpuControl, sizeof(SMM_AP_CPU_CONTROL) * NumCpus, 0);

    gDispatcherPrivate->SmmControl = gSmmControl;
}

//<AMI_PHDR_START>
//----------------------------------------------------------------------------
//
// Procedure: CreateRuntimeInSmmFunction
//
// Description:
//  Create InSmm function in runtime.
//
// Input: VOID
//
// Output: VOID
//
//----------------------------------------------------------------------------
//<AMI_PHDR_END>

VOID *CreateRuntimeInSmmFunction()
{
    UINT8 *RuntimeInSmmFunc;
    EFI_STATUS Status;

    Status = pBS->AllocatePool(EfiRuntimeServicesCode, InSmmFuncLength, &RuntimeInSmmFunc);
    ASSERT_EFI_ERROR(Status);

    MemCpy(RuntimeInSmmFunc, EfiSmmInSmm, InSmmFuncLength);

    return RuntimeInSmmFunc;
}

//<AMI_PHDR_START>
//----------------------------------------------------------------------------
//
// Procedure: DisableSmmCallbacks
//
// Description:
//  This is signaled before booting or shell.
//  This makes the SMM Base protocol register/unregister unsupported.
//
// Input:
//  IN EFI_EVENT Event
//  IN VOID *Context
//
// Output:
//  VOID
//
//
//  NOTE: This routine could be called multiple times right before booting.
//----------------------------------------------------------------------------
//<AMI_PHDR_END>

VOID DisableSmmCallbacks(IN EFI_EVENT Event, IN VOID *Context)
{
#if SMM_USE_PI
    EFI_HANDLE Handle = NULL;
#endif
    //This should only run once, even if called by different events.
    static BOOLEAN HasRun = FALSE;
    if (HasRun) return;

    pBS->CloseEvent(Event);

    //If we are following PI1.1 model we should dispatch rest of SMM drivers whose DEPEX
    //was not TRUE at the time of the first pass.
#if SMM_USE_PI
    CallFuncInSmm(SmmDispatcher);

    pBS->InstallMultipleProtocolInterfaces (
        &Handle,
        &gEfiDxeSmmReadyToLockProtocolGuid, NULL,
        NULL
    );
#endif

    CallFuncInSmm(SetDisallowRegistering);
    HasRun = TRUE;
}

#if SMM_USE_PI
VOID SmmIplGuidedEventNotify (
    IN EFI_EVENT  Event,
    IN VOID       *Context)
{
    CallFuncInSmm(SmmDriverDispatchHandler);
}
#endif

//<AMI_PHDR_START>
//----------------------------------------------------------------------------
//
// Procedure: LocateProtocols
//
// Description:
//  Locate protocols needed for SMM Base.
//
// Input: VOID
//
// Output: VOID
//
//----------------------------------------------------------------------------
//<AMI_PHDR_END>

VOID LocateProtocols()
{
    EFI_STATUS Status;
#if SMM_USE_PI
    Status = pBS->LocateProtocol(&gEfiSmmAccess2ProtocolGuid, NULL, &gSmmAccess);
    ASSERT_EFI_ERROR(Status);

    Status = pBS->LocateProtocol(&gEfiSmmControl2ProtocolGuid, NULL, &gSmmControl);
    ASSERT_EFI_ERROR(Status);
#else
    Status = pBS->LocateProtocol(&gEfiSmmAccessProtocolGuid, NULL, &gSmmAccess);
    ASSERT_EFI_ERROR(Status);

    Status = pBS->LocateProtocol(&gEfiSmmControlProtocolGuid, NULL, &gSmmControl);
    ASSERT_EFI_ERROR(Status);
#endif

    Status = pBS->LocateProtocol(&gEfiPe32ImageProtocolGuid, NULL, &gPe32Image);
    ASSERT_EFI_ERROR(Status);

    Status = pBS->LocateProtocol(&gEfiMpServicesProtocolGuid, NULL, &gMpServices);
    ASSERT_EFI_ERROR(Status);

#if SMM_THUNK_IN_CSM == 1
    Status = pBS->LocateProtocol(&gEfiLegacyBiosProtocolGuid, NULL, &gLegacyBios);
    ASSERT_EFI_ERROR(Status);

    Status = pBS->LocateProtocol(&gEfiLegacyBiosExtProtocolGuid, NULL, &gLegacyBiosExt);
    ASSERT_EFI_ERROR(Status);
#endif
}

//<AMI_PHDR_START>
//----------------------------------------------------------------------------
//
// Procedure: FindHobs
//
// Description: Locate the HOBs needed.
//
// Input: VOID
//
// Output: VOID
//
//----------------------------------------------------------------------------
//<AMI_PHDR_END>

EFI_STATUS FindHobs()
{
    VOID *FirstHob;
    EFI_STATUS Status;

    //Parse hobs to get CPU Hob.
    //Find first Hob
    FirstHob =  GetEfiConfigurationTable(pST,&gHobListGuid);
    if (!FirstHob) {
        TRACE((TRACE_ALWAYS, "SmmBase.Entry()Error:Unable to find CPUInfo HOB\n"));
        return EFI_NOT_FOUND;
    }

    //Find SMM Hob.
    gSmmHob = (SMM_HOB*) FirstHob;
    while (!EFI_ERROR(Status = FindNextHobByType(EFI_HOB_TYPE_GUID_EXTENSION, &gSmmHob))) {
        if (guidcmp(&((EFI_HOB_GUID_TYPE*)gSmmHob)->Name, &gSmmHobGuid) == 0) {
            break;
        }
    }
    if (EFI_ERROR(Status)) return Status;

    //Find Cpu Info Hob.
    gCpuinfoHob = (CPUINFO_HOB*) FirstHob;
    while (!EFI_ERROR(Status = FindNextHobByType(EFI_HOB_TYPE_GUID_EXTENSION, &gCpuinfoHob))) {
        if (guidcmp(&((EFI_HOB_GUID_TYPE*)gCpuinfoHob)->Name, &gCpuinfoHobGuid) == 0) {
            break;
        }
    }
    if (EFI_ERROR(Status)) return Status;

    gCpuHob = (EFI_HOB_CPU*)FirstHob;
    Status = FindNextHobByType(EFI_HOB_TYPE_CPU, &gCpuHob);
    if (EFI_ERROR(Status)) return Status;
    return EFI_SUCCESS;
}

//<AMI_PHDR_START>
//----------------------------------------------------------------------------
//
// Procedure: SmmInitEntry
//
// Description: SMM Installer Entry Point.
//
// Input:
//  IN EFI_HANDLE       ImageHandle
//  IN EFI_SYSTEM_TABLE *SystemTable
//
// Output: EFI_STATUS
//
//----------------------------------------------------------------------------
//<AMI_PHDR_END>

EFI_STATUS SmmInitEntry(
    IN EFI_HANDLE       ImageHandle,
    IN EFI_SYSTEM_TABLE *SystemTable
)
{
    EFI_STATUS              Status;
    EFI_EVENT               BootEvent;
    EFI_EVENT               Event;
    VOID                    *Registration;
    VOID                    *RuntimeInSmmFunc;
#if SMM_USE_FRAMEWORK
    EFI_SMM_BASE_PROTOCOL   *RuntimeSmmBase;
#endif

    InitAmiLib(ImageHandle,SystemTable);

    gThisImageHandle = ImageHandle;

    LocateProtocols();

    Status = FindHobs();
    ASSERT_EFI_ERROR(Status);
    if (EFI_ERROR(Status)) return Status;


    Status = gMpServices->WhoAmI(gMpServices, &gBsp);
    ASSERT_EFI_ERROR(Status);

    gBspSmmBase = gSmmHob->SmmBase[gSmmHob->Bsp];
    gSmmEntryData = (SMM_ENTRY_INIT_STRUCT *) (gBspSmmBase + 0x8004);


    // Allocate space in runtime services for gPrivate.
    // This is needed because this pointer will be used by SMM during runtime.

    Status = pBS->AllocatePool(EfiRuntimeServicesData, sizeof(SMM_BASE_PRIVATE_STRUCT), &gBasePrivate);
    ASSERT_EFI_ERROR(Status);

    //  Copy the private structure. This does not copy the pointer. It copies the entire structure.
    *gBasePrivate = gSmmBasePrivateStruct;  //Make available during runtime.

    InitgBasePrivate();
    RuntimeInSmmFunc = CreateRuntimeInSmmFunction();

#if SMM_USE_FRAMEWORK
    gEfiSmmBase.InSmm = (EFI_SMM_INSIDE_OUT)RuntimeInSmmFunc;
#endif
#if SMM_USE_PI
    gEfiSmmBase2.InSmm = (EFI_SMM_INSIDE_OUT2)RuntimeInSmmFunc;
#endif
    gBasePrivate->InSmm = (UINT8*)RuntimeInSmmFunc + InSmmFuncOffset;

    Status = gSmmAccess->Open(gSmmAccess
#if SMM_USE_PI == 0
            ,0
#endif
    );
    ASSERT_EFI_ERROR(Status);

    InitgDispatcherPrivate();

#if SMM_CACHE_SUPPORT == 1
#ifndef NEHALEM_CPU_MODULE
    InitSmmCacheData();
#endif
#endif

    LoadAndInitDispatcherImages(pST, gSmmHob->NumCpus);

    gSmmAccess->Close(gSmmAccess
#if SMM_USE_PI == 0
            , 0
#endif
    );

    // locks SMM area so no one else can change it
    gSmmAccess->Lock(gSmmAccess
#if SMM_USE_PI == 0
            , 0
#endif
    );

    //For security reasons SMM should call from inside SMM to outside SMM before option ROMs are loaded.
    //The following callback is registered to disable this. When this is disabled, no new SMM drivers
    //can be registered.

    //This call back is only available since core 4.6.3.5.
    Status = RegisterProtocolCallback(
        &gBdsAllDriversConnectedProtocolGuid,
        DisableSmmCallbacks,
        NULL,
        &Event,
        &Registration
    );
    ASSERT_EFI_ERROR(Status);

    //In cases where core does not support a call back before option roms are executed.
    //The calling outside of SMM will be disabled before shell or a OS is loaded.
    Status = CreateReadyToBootEvent(
        TPL_CALLBACK,
        DisableSmmCallbacks,
        NULL,
        &BootEvent
    );
    ASSERT_EFI_ERROR(Status);

#if SMM_USE_PI
    //Setup Notification when BDS has finished 1st pass on loading drivers...
    Status = pBS->CreateEventEx (
             EVT_NOTIFY_SIGNAL,
             TPL_CALLBACK,
             SmmIplGuidedEventNotify,
             NULL,
             &gEfiEventDxeDispatchGuid,
             &Event
             );
    ASSERT_EFI_ERROR(Status);

#endif

#if SMM_USE_FRAMEWORK
	Status = pBS->AllocatePool(EfiRuntimeServicesData, sizeof(EFI_SMM_BASE_PROTOCOL), &RuntimeSmmBase);
	ASSERT_EFI_ERROR(Status);
    *RuntimeSmmBase = gEfiSmmBase;
#endif

    Status = pBS->InstallMultipleProtocolInterfaces(
        &ImageHandle,
#if SMM_USE_FRAMEWORK
        &gEfiSmmBaseProtocolGuid, RuntimeSmmBase,
#endif
#if SMM_USE_PI
        &gEfiSmmBase2ProtocolGuid, &gEfiSmmBase2,
#endif
        NULL);
    ASSERT_EFI_ERROR(Status);

    return Status;
}

//*************************************************************************
//*************************************************************************
//**                                                                     **
//**        (C)Copyright 1985-2011, American Megatrends, Inc.            **
//**                                                                     **
//**                       All Rights Reserved.                          **
//**                                                                     **
//**      5555 Oakbrook Parkway, Suite 200, Norcross, GA 30093           **
//**                                                                     **
//**                       Phone: (770)-246-8600                         **
//**                                                                     **
//*************************************************************************
//*************************************************************************
