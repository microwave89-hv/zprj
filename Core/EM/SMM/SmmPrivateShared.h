//*************************************************************************
//*************************************************************************
//**                                                                     **
//**        (C)Copyright 1985-2009, American Megatrends, Inc.            **
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
// $Header: /Alaska/SOURCE/Modules/SMM/SmmPrivateShared.h 36    4/01/11 10:08a Markw $
//
// $Revision: 36 $
//
// $Date: 4/01/11 10:08a $
//**********************************************************************
// Revision History
// ----------------
// $Log: /Alaska/SOURCE/Modules/SMM/SmmPrivateShared.h $
// 
// 36    4/01/11 10:08a Markw
// [TAG]  		EIP57440
// [Category]  	New Feature
// [Description]  	Add PI 1.1 SMM support for reading/writing floating
// point/smm save state.
// 
// [Files]  		CpuCspLib.h, CpuCspLib.c, SmmPiSmst.c,  SmmPrivateShared.h,
// SmmHdr.equ, SmmInit.c
// 
// 
// 35    2/07/11 4:07p Markw
// [TAG]  		EIP53481
// [Category]  	New Feature
// [Description]  	Add PIWG 1.1 SMM support
// [Files]  		Smm.sdl, SmmPrivateShared.h, SmmDispatcher.mak,
// SmmDispatcher.h, SmmDispatcher.c,
// Smst.c, SmmPiSmst.c, SmmInit.c, SmmBase.c, SmmBase2.c,
// SmmDriverDispatcher.c, Smm Framewwork Protocol files, SmmPi.h,
// Smm Pi Protocol files, SmmPciRbio files
// 
// 34    8/11/09 11:46a Markw
// Removed Legacy registration. This is removed from latest PI and not
// used by projects.
// 
// 33    7/08/09 8:04p Markw
// Update headers.
// 
// 32    1/22/09 12:59p Markw
// EIP #18671 (OPEN) Clear SW SMI status and set EOS inside SMM. Add
// SmmControl to private structure.
// 
// 31    12/24/08 10:53a Markw
// EIP #18423: Adjust EBDA location as more EBDA data is allocated.
// 
// 30    12/23/08 2:15p Markw
// EIP #17900  Set up TSS. Borland C in DOS hangs otherwise.
// 
// 29    11/21/08 4:56p Markw
// Add SmmInit to SMM_ENTRY_STRUCT for SMM init for first normal/S3 boot.
// 32-bit CPU count.
// 
// 28    9/26/08 4:52p Markw
// The Private InSmm is now a pointer.
// 
// 27    9/09/08 3:05p Markw
// Add in SMM_BASE_PRIVATE_STRUCT, Dispatcher pe32 Image Start.
// 
// 26    9/07/08 12:41a Markw
// Separate SMM Private structure into inside SMM and outside SMM
// structure.
// 
// 25    8/28/08 3:51p Markw
// Added support for saving/restoring chipset context.
// 
// 24    6/09/08 5:57p Markw
// Add SMM_CPU_INFO for Cpu specific information in the Private structure.
// 
// 23    5/23/08 11:18a Markw
// Add member for disallowing callbacks.
// 
// 22    4/04/08 6:21p Markw
// Add Smrr MSR to SMM_BASE_PRIVATE_STRUCT.
// 
// 21    3/03/08 6:35p Markw
// Added 32-bit register for smm thunk.
// 
// 20    11/14/07 2:03p Markw
// Added SMRR support and updated SMM Cache for non-SMRR.
// 
// 19    10/29/07 10:58a Markw
// Smm Thunk:
// * Code and data different segments.
// * Code position independent.
// * Switch for CSM for code and EBDA for data.
// 
// 18    10/24/07 12:00p Markw
// SMM Thunk code position independent. Data in a separate segment than
// code in Smm Thunk.
// 
// 17    9/10/07 1:38p Markw
// Add IDT entry.
// 
// 16    6/08/07 6:51p Markw
// Save/Restore XMM.
// 
// 15    1/11/07 12:28p Markw
// Adjusted location of fields in structure for removal of legacy.
// 
// 14    1/09/07 6:40p Markw
// Update BSP Entry Structure to remove dependencies on SMM_BSP_BASE.
// 
// 13    12/29/06 4:44p Markw
// Add Smm Cache Support and update CPU syncronization.
// 
// 12    12/21/06 5:19p Markw
// Remove old unused SmmStackSize from Private structure.
// 
// 11    11/13/06 11:24a Markw
// Updated structure for Ap Entry.
// 
// 10    9/18/06 11:47a Markw
// Add a check to guarentee that BSP and Ap can't get out of sync.
// 
// 9     8/24/06 3:27p Felixp
// Preliminary x64 support (work in progress)
// 
// 8     5/08/06 6:47p Markw
// Use Hob for initalizing SMM.
// 
// 7     2/03/06 10:26a Markw
// Moved Smm Base change to PEI CPU.
// 
// 6     1/13/06 11:27a Markw
// Added SMM Thunk support.
// 
// 5     1/10/06 2:56p Markw
// Add support for multi-threadding and sync all CPUs during entry/exit of
// SMM.
// 
// 4     8/10/05 5:01p Markw
// Added ChangeBaseInfo Structure for changing bases and passing
// information to a runtime function.
// 
// 3     7/12/05 11:08a Markw
// Added TSEG start to private structure.
// 
// 2     7/11/05 1:05p Markw
// Removed isCallback from structure. Chaged Io Port from UINT8 to UINT16.
// 
// 1     1/28/05 4:29p Sivagarn
// Generic SMM module - Intial Check in
//
//
//**********************************************************************

//<AMI_FHDR_START>
//---------------------------------------------------------------------------
//
// Name:		SMMPrivateShared.h
//
// Description:	Header file for the SMM shared equates and structures
//
//---------------------------------------------------------------------------
//<AMI_FHDR_END>

#ifndef __SMM_PRIVATE_SHARED__H__
#define __SMM_PRIVATE_SHARED__H__

#include <efi.h>
#include <Protocol\SmmThunk.h>

#if defined(PI_SPECIFICATION_VERSION)&&(PI_SPECIFICATION_VERSION>=0x00010000)
#define USE_FV2 1
#else
#define USE_FV2 0
#endif

#define SMM_USE_FRAMEWORK 1

#if defined(PI_SPECIFICATION_VERSION)&&(PI_SPECIFICATION_VERSION>=0x0001000A)
#define SMM_USE_PI 1
#else
#define SMM_USE_PI 0
#endif

#include <AmiHobs.h>
#include <Token.h>

#ifdef __cplusplus
extern "C" {
#endif

#define SMMBASE_CALLBACK 0xf0
typedef struct _SMM_ENTRY_INIT_STRUCT SMM_ENTRY_INIT_STRUCT;
typedef struct _SMM_THUNK_DATA SMM_THUNK_DATA;

typedef VOID (*SMM_AP_PROCEDURE) (
    IN VOID                     *Buffer
);

typedef struct {
    SMM_AP_PROCEDURE	Procedure;
	VOID				*ProcArguments;
} SMM_AP_CPU_CONTROL;


typedef struct _HANDLER_LIST HANDLER_LIST;
struct _HANDLER_LIST
{
    EFI_GUID        HandlerType;            //Only filled if non-root.
    VOID  	        *EntryPoint;
	EFI_HANDLE		SmmImageHandle;
    VOID            *Context;
    VOID            *CommunicationBuffer;   //Framework only
    UINTN           *SourceSize;            //Framework only

    BOOLEAN         IsRoot;
    BOOLEAN         IsPi;
    HANDLER_LIST    *Link;
};

typedef struct {
	EFI_DEVICE_PATH_PROTOCOL	*FilePath;
	VOID						*SourceBuffer;
	UINTN						SourceSize;
	EFI_HANDLE					*ImageHandle;
	BOOLEAN						LegacyIA32Binary;
} REGISTER_HANDLER_CALLBACK;

typedef struct {
	EFI_HANDLE					ImageHandle;
} UNREGISTER_HANDLER_CALLBACK;

typedef struct {
	EFI_HANDLE					ImageHandle;
	VOID						*CommunicationBuffer;
	UINTN						*SourceSize;
} COMMUNICATE_CALLBACK;

typedef struct {
	UINTN						Size;
	VOID						**Buffer;
} ALLOCATE_POOL_CALLBACK;

typedef struct {
	VOID						*Buffer;
} FREE_POOL_CALLBACK;


typedef union {
	REGISTER_HANDLER_CALLBACK		RegisterHandler;
	UNREGISTER_HANDLER_CALLBACK		UnregisterHandler;
	COMMUNICATE_CALLBACK			Communicate;
	ALLOCATE_POOL_CALLBACK			AllocatePool;
	FREE_POOL_CALLBACK				FreePool;
} CALLBACKS;

#pragma pack (1)
typedef struct {
	UINT16	Limit;
	UINTN   Base;       //This shared between 32 bit and 64 bit.
} DESCRIPTOR_TABLE;
#pragma pack()

typedef struct {
    BOOLEAN     InSmm;
    UINT32      ApicId;
} SMM_CPU_INFO;

typedef struct {
	VOID        (*CallBackFunc)();
	BOOLEAN     *InSmm;
    BOOLEAN     DisallowCallbacks;
	EFI_STATUS  CallbackStatus;
    VOID        *Pe32DispatcherImage;
	UINTN       Pe32DispatcherImageSize;

	CALLBACKS   CallbackParameters;
    SMM_HOB     *SmmHob;
  	VOID        *SmmAllocMemoryStart;	//Area to allocate memory
	UINT32      SmmAllocMemoryLength;
} SMM_BASE_PRIVATE_STRUCT;

typedef struct {
    VOID                        *PageDirectories;
    VOID                        **SmmXmmSave;
    BOOLEAN                     SmrrEnable;
    UINT32                      SmrrMsr;
    UINT32                      TsegMsr;
    UINT64                      TsegMsrBase;
    UINT64                      TsegMsrMask;
    DESCRIPTOR_TABLE            Idt;
    SMM_CPU_INFO                *SmmCpuInfo;

	VOID                        (*SmmThunkProc)();
    SMM_THUNK_DATA              *SmmThunkData;
    UINT32                      EbdaStartOffset;
	UINT32                      NumCpus;
	UINT32                      NumCpusInSmm;

	HANDLER_LIST                *HandlerListHead;
	BOOLEAN                     FloatingPointSave;

	volatile SMM_AP_CPU_CONTROL	*SmmApCpuControl;
    UINT32                      SmmBspNumber;           //This can change each SMM entry.
	VOID	                    *SmmControl;
} SMM_DISPATCHER_PRIVATE_STRUCT;


#pragma pack(1)
typedef struct {
	UINT16	Offset;
	UINT16	Segment;
} FAR_CALL_PTR_16;

typedef struct {
	UINT32 	Stack;
	UINT32	StackSize;
} STACK;

typedef struct {
    UINT16  Limit;
    UINT32  Base;
    UINT16  Rsv;    //For alignment
} SMM_DESC;

#pragma pack()

struct _SMM_ENTRY_INIT_STRUCT {
    UINT32                  SmmInit;        //This must be first.
	UINT32					SmmEntrySize;
    UINT32                  GdtDescBaseOffset;
    UINT32                  LCodeSelBaseOffset;
    UINT32                  TssSelBaseOffset;
	UINT32					SmmThunkProcOffset;
    UINT32                  SmmThunkLength;
    UINT32                  HtCpu;
	VOID					*SmmEntryStart;
	VOID					(*DispatcherEntry)(SMM_ENTRY_INIT_STRUCT *);
	SMM_DISPATCHER_PRIVATE_STRUCT	*DispatcherPrivate;
	UINT8					*SmmStackTop;
    UINT32                  CpuNo;
};

struct _SMM_THUNK_DATA {
	FAR_CALL_PTR_16 		        FarCall;
	SMM_THUNK_IA32_REGISTER_SET_EX  Regs;
	STACK					        Stack;
    UINT32                          StackSave;
    SMM_DESC                        GdtSave;
    SMM_DESC                        IdtSave;
    SMM_DESC                        LegacyIdtDesc;
    UINT16                          Below1MStack;
};

typedef EFI_STATUS (*DISPATCHER_ENTRY_POINT)(
	IN EFI_HANDLE				        ImageHandle,
    IN EFI_SYSTEM_TABLE	                *SystemTable,
	IN SMM_BASE_PRIVATE_STRUCT	        *BasePrivate,
    IN SMM_DISPATCHER_PRIVATE_STRUCT    *DispatcherPrivate,
    OUT VOID                            **SmstTable,
    OUT VOID                            **SmstTable2
);
    

typedef VOID (*EFI_SMM_SAVE_RESTORE_FUNCTION)(BOOLEAN Save);


/****** DO NOT WRITE BELOW THIS LINE *******/
#ifdef __cplusplus
}
#endif
#endif

//*************************************************************************
//*************************************************************************
//**                                                                     **
//**        (C)Copyright 1985-2009, American Megatrends, Inc.            **
//**                                                                     **
//**                       All Rights Reserved.                          **
//**                                                                     **
//**      5555 Oakbrook Parkway, Suite 200, Norcross, GA 30093           **
//**                                                                     **
//**                       Phone: (770)-246-8600                         **
//**                                                                     **
//*************************************************************************
//*************************************************************************
