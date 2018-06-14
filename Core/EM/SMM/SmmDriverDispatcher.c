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

/** SmmDriverDispatcher.c - Modified from Intel's SMM source.

  Copyright (c) 2009, Intel Corporation
  All rights reserved. This program and the accompanying materials
  are licensed and made available under the terms and conditions of the BSD License
  which accompanies this distribution.  The full text of the license may be found at
  http://opensource.org/licenses/bsd-license.php

  THE PROGRAM IS DISTRIBUTED UNDER THE BSD LICENSE ON AN "AS IS" BASIS,
  WITHOUT WARRANTIES OR REPRESENTATIONS OF ANY KIND, EITHER EXPRESS OR IMPLIED.

**/

//**********************************************************************
// $Header: /Alaska/SOURCE/Modules/SMM/SMMBase/SmmDriverDispatcher.c 6     2/13/12 4:42p Markw $
//
// $Revision: 6 $
//
// $Date: 2/13/12 4:42p $
//**********************************************************************
// Revision History
// ----------------
// $Log: /Alaska/SOURCE/Modules/SMM/SMMBase/SmmDriverDispatcher.c $
// 
// 6     2/13/12 4:42p Markw
// [TAG]  		EIP83005
// [Category]  	Improvement
// [Description]  	Some framework based SMM libraries expect a DXE image
// handle on input. However, PI 1.1 SMM drivers expect a SMM handle on
// input.
// Update code to provide proper EFI_HANDLE when calling SMM functions.
// 
// [Files]  		SmmBase.c, SmmDriverDispatcher.c
// 
// 5     1/10/12 12:58p Markw
// [TAG]  		EIP78978
// [Category]  	Improvement
// [Description]  	Cleanup of SmmLoadImage function - removing unused and
// removing unneeded variable initialization.
// [Files]  		SmmDriverDispatcher.c
// 
// 4     1/09/12 3:06p Markw
// [TAG]  		EIP78978
// [Category]  	Bug Fix
// [Severity]  	Normal
// [Symptom]  	SMM driver will authentication failed.
// [RootCause]  	Incorrect device path as input parameter when checking
// authentication.
// 
// [Solution]  	Authentication is done twice. Remove redundant code.
// Second authentication check is using the correct original device path.
// 
// [Files]  		SmmDriverDispatcher.c
// 
// 3     3/15/11 2:37p Markw
// Copyright header update.
// 
// 2     3/08/11 4:57p Markw
// Header and spacing updates.
// 
// 1     2/07/11 3:34p Markw
// [TAG]  		EIP53481
// [Category]  	New Feature
// [Description]  	Add PIWG 1.1 SMM support
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
// Name:		SmmDriverDispatcher.c
//
// Description:	Dispatch SMM Drivers
//
//---------------------------------------------------------------------------
//<AMI_FHDR_END>

//This include should come first.
#include "SmmPrivateShared.h"
#if SMM_USE_PI
#include <SmmPi.h>
#include <Protocol\DevicePath.h>
#include <Protocol\Security.h>
#include <Dxe.h>
#include <Protocol\FirmwareVolume2.h>
#include <Protocol\LoadedImage.h>
#include <AmiDxeLib.h>
#include <AmiLib.h>

extern EFI_SMM_SYSTEM_TABLE2    *gSmstTable2;
extern SMM_BASE_PRIVATE_STRUCT  *gBasePrivate;
extern BOOLEAN gRegisterForPi;

//
//  CONTAINING_RECORD - returns a pointer to the structure
//      from one of it's elements.
//
#ifndef _CR
#define _CR(Record, TYPE, Field)  ((TYPE *) ((CHAR8 *) (Record) - (CHAR8 *) &(((TYPE *) 0)->Field)))
#endif

#ifndef CR
#define CR(record, TYPE, field, signature) _CR(record, TYPE, field)
#endif


//
// Define macros to build data structure signatures from characters.
//
#define SIGNATURE_16(A, B)        ((A) | (B << 8))
#define SIGNATURE_32(A, B, C, D)  (SIGNATURE_16 (A, B) | (SIGNATURE_16 (C, D) << 16))
#define SIGNATURE_64(A, B, C, D, E, F, G, H) \
   (SIGNATURE_32 (A, B, C, D) | ((UINT64) (SIGNATURE_32 (E, F, G, H)) << 32))
//---- Added from Core\Tiano.h


// EFI_DEP_REPLACE_TRUE - Used to dynamically patch the dependency expression
//                        to save time.  A EFI_DEP_PUSH is evaluated one an
//                        replaced with EFI_DEP_REPLACE_TRUE. If PI spec's Vol 2
//                        Driver Execution Environment Core Interface use 0xff
//                        as new DEPEX opcode. EFI_DEP_REPLACE_TRUE should be
//                        defined to a new value that is not conflicting with PI spec.
//
#define EFI_DEP_REPLACE_TRUE  0xff

/// Define the initial size of the dependency expression evaluation stack
#define DEPEX_STACK_SIZE_INCREMENT  0x1000

//
//
// EFI_DEP_BEFORE       - If present, it must be the first and only opcode
// EFI_DEP_AFTER        - If present, it must be the first and only opcode
// EFI_DEP_SOR          - If present, it must be the first opcode
// EFI_DEP_REPLACE_TRUE - Used to dynamically patch the dependency expression
//                        to save time.  A EFI_DEP_PUSH is evaluated one an
//                        replaced with EFI_DEP_REPLACE_TRUE
//
#define EFI_DEP_BEFORE        0x00
#define EFI_DEP_AFTER         0x01
#define EFI_DEP_PUSH          0x02
#define EFI_DEP_AND           0x03
#define EFI_DEP_OR            0x04
#define EFI_DEP_NOT           0x05
#define EFI_DEP_TRUE          0x06
#define EFI_DEP_FALSE         0x07
#define EFI_DEP_END           0x08
#define EFI_DEP_SOR           0x09
#define EFI_DEP_REPLACE_TRUE  0xff


// Global stack used to evaluate dependency expressions
BOOLEAN  *mDepexEvaluationStack        = NULL;
BOOLEAN  *mDepexEvaluationStackEnd     = NULL;
BOOLEAN  *mDepexEvaluationStackPointer = NULL;

#define LIST_ENTRY EFI_LIST_ENTRY

//
// The Driver List contains one copy of every driver that has been discovered.
// Items are never removed from the driver list. List of EFI_SMM_DRIVER_ENTRY
//
LIST_ENTRY  mDiscoveredList = INITIALIZE_LIST_HEAD_VARIABLE (mDiscoveredList);

//
// Queue of drivers that are ready to dispatch. This queue is a subset of the
// mDiscoveredList.list of EFI_SMM_DRIVER_ENTRY.
//
LIST_ENTRY  mScheduledQueue = INITIALIZE_LIST_HEAD_VARIABLE (mScheduledQueue);

//
// List of handles who's Fv's have been parsed and added to the mFwDriverList.
//
LIST_ENTRY  mFvHandleList = INITIALIZE_LIST_HEAD_VARIABLE (mFvHandleList);

//
// Flag for the SMM Dispacher.  TRUE if dispatcher is executing.
//
BOOLEAN  gDispatcherRunning = FALSE;

//
// Flag for the SMM Dispacher.  TRUE if there is one or more SMM drivers ready to be dispatched
//
BOOLEAN  gRequestDispatch = FALSE;

//
// List of file types supported by dispatcher
//
EFI_FV_FILETYPE mSmmFileTypes[] = {
    EFI_FV_FILETYPE_SMM,
    EFI_FV_FILETYPE_COMBINED_SMM_DXE
    //
    // Note: DXE core will process the FV image file, so skip it in SMM core
    // EFI_FV_FILETYPE_FIRMWARE_VOLUME_IMAGE
    //
};

typedef struct {
    MEDIA_FW_VOL_FILEPATH_DEVICE_PATH  File;
    EFI_DEVICE_PATH_PROTOCOL           End;
} FV_FILEPATH_DEVICE_PATH;

FV_FILEPATH_DEVICE_PATH  mFvDevicePath;

//
// DXE Architecture Protocols
//
EFI_SECURITY_ARCH_PROTOCOL  *mSecurity = NULL;

//
// SMM Dispatcher Data structures
//
#define KNOWN_HANDLE_SIGNATURE  SIGNATURE_32('k','n','o','w')
typedef struct {
    UINTN           Signature;
    LIST_ENTRY      Link;         // mFvHandleList
    EFI_HANDLE      Handle;
} KNOWN_HANDLE;

//
// Structure for recording the state of an SMM Driver
//
#define EFI_SMM_DRIVER_ENTRY_SIGNATURE SIGNATURE_32('s', 'd','r','v')

#define LIST_ENTRY EFI_LIST_ENTRY

typedef struct {
    UINTN                           Signature;
    LIST_ENTRY                      Link;             // mDriverList

    LIST_ENTRY                      ScheduledLink;    // mScheduledQueue

    EFI_HANDLE                      FvHandle;
    EFI_GUID                        FileName;
    EFI_DEVICE_PATH_PROTOCOL        *FvFileDevicePath;
    EFI_FIRMWARE_VOLUME2_PROTOCOL   *Fv;

    VOID                            *Depex;
    UINTN                           DepexSize;

    BOOLEAN                         Before;
    BOOLEAN                         After;
    EFI_GUID                        BeforeAfterGuid;

    BOOLEAN                         Dependent;
    BOOLEAN                         Unrequested;
    BOOLEAN                         Scheduled;
    BOOLEAN                         Untrusted;
    BOOLEAN                         Initialized;
    BOOLEAN                         DepexProtocolError;

    EFI_HANDLE                      ImageHandle;
    EFI_LOADED_IMAGE_PROTOCOL       *LoadedImage;
    //
    // Image EntryPoint in SMRAM
    //
    EFI_PHYSICAL_ADDRESS            ImageEntryPoint;
    //
    // Image Buffer in SMRAM
    //
    EFI_PHYSICAL_ADDRESS            ImageBuffer;
    //
    // Image Page Number
    //
    UINTN                           NumberOfPage;
} EFI_SMM_DRIVER_ENTRY;

EFI_GUID                            gAprioriGuid=EFI_APRIORI_GUID;

EFI_STATUS SmmDispatcher();

EFI_HANDLE                          gThisImageHandle;

EFI_STATUS EfiSmmRegister(
    IN VOID	                    *This,
    IN EFI_DEVICE_PATH_PROTOCOL *FilePath,
    IN VOID                     *SourceBuffer OPTIONAL,
    IN UINTN                    SourceSize,
    OUT EFI_HANDLE              *ImageHandle,
    IN BOOLEAN                  LegacyIA32Binary OPTIONAL
);

//////////////////////////////////////////////////////////////////////
// ----- PI 1.1 --------------------------------------------- START //
//////////////////////////////////////////////////////////////////////

#define SetDevicePathNodeLength(a,l) {                           \
          (a)->Length[0] = (UINT8) (l);                          \
          (a)->Length[1] = (UINT8) ((l) >> 8);                   \
          }

#define SetDevicePathEndNode(a)  {                               \
          (a)->Type = END_DEVICE_PATH;                           \
          (a)->SubType = END_ENTIRE_SUBTYPE;         \
          (a)->Length[0] = sizeof(EFI_DEVICE_PATH_PROTOCOL);     \
          (a)->Length[1] = 0;                                    \
          }

//<AMI_PHDR_START>
//---------------------------------------------------------------------------
//
// Procedure: AllocatePool
//
// Description: Allocate memory.
//
// Input:
//  IN UINTN Size
//
// Output: VOID * - Address
//---------------------------------------------------------------------------
//<AMI_PHDR_END>

VOID *AllocatePool(UINTN Size){
    return Malloc(Size);
}

//<AMI_PHDR_START>
//---------------------------------------------------------------------------
//
// Procedure: GrowDepexStack
//
// Description: Increase Depex Stack..
//
// Input: VOID
//
// Output: EFI_STATUS
//---------------------------------------------------------------------------
//<AMI_PHDR_END>

EFI_STATUS GrowDepexStack(VOID)
{
    BOOLEAN     *NewStack;
    UINTN       Size;

    Size = DEPEX_STACK_SIZE_INCREMENT;
    if (mDepexEvaluationStack != NULL) {
        Size = Size + (mDepexEvaluationStackEnd - mDepexEvaluationStack);
    }

    NewStack = AllocatePool (Size * sizeof(BOOLEAN));
        if (NewStack == NULL) {
        return EFI_OUT_OF_RESOURCES;
    }

    if (mDepexEvaluationStack != NULL) {
        //
        // Copy to Old Stack to the New Stack
        //

        MemCpy(
            NewStack,
            mDepexEvaluationStack,
            (mDepexEvaluationStackEnd - mDepexEvaluationStack) * sizeof (BOOLEAN)
        );

        //
        // Free The Old Stack
        //
        pBS->FreePool (mDepexEvaluationStack);
    }

    //
    // Make the Stack pointer point to the old data in the new stack
    //
    mDepexEvaluationStackPointer = NewStack + (mDepexEvaluationStackPointer - mDepexEvaluationStack);
    mDepexEvaluationStack        = NewStack;
    mDepexEvaluationStackEnd     = NewStack + Size;

    return EFI_SUCCESS;
}

//<AMI_PHDR_START>
//---------------------------------------------------------------------------
//
// Procedure: PushBool
//
// Description: Push boolean value to stack.
//
// Input: IN BOOLEAN Value
//
// Output: EFI_STATUS
//---------------------------------------------------------------------------
//<AMI_PHDR_END>

EFI_STATUS PushBool(IN BOOLEAN Value)
{
    EFI_STATUS  Status;

    //
    // Check for a stack overflow condition
    //
    if (mDepexEvaluationStackPointer == mDepexEvaluationStackEnd) {
        //
        // Grow the stack
        //
        Status = GrowDepexStack ();
        if (EFI_ERROR (Status)) {
            return Status;
        }
    }

    //
    // Push the item onto the stack
    //
    *mDepexEvaluationStackPointer = Value;
    mDepexEvaluationStackPointer++;

    return EFI_SUCCESS;
}

//<AMI_PHDR_START>
//---------------------------------------------------------------------------
//
// Procedure: PopBool
//
// Description: Pop boolean value to stack.
//
// Input: OUT BOOLEAN *Value
//
// Output: EFI_STATUS
//---------------------------------------------------------------------------
//<AMI_PHDR_END>

EFI_STATUS PopBool(OUT BOOLEAN *Value)
{
    //
    // Check for a stack underflow condition
    //
    if (mDepexEvaluationStackPointer == mDepexEvaluationStack) {
        return EFI_ACCESS_DENIED;
    }

    //
    // Pop the item off the stack
    //
    mDepexEvaluationStackPointer--;
    *Value = *mDepexEvaluationStackPointer;
    return EFI_SUCCESS;
}

//<AMI_PHDR_START>
//---------------------------------------------------------------------------
//
// Procedure: SmmIsSchedulable
//
// Description: Check if driver meets dependencies.
//
// Input: IN EFI_SMM_DRIVER_ENTRY *DriverEntry
//
// Output: BOOLEAN
//---------------------------------------------------------------------------
//<AMI_PHDR_END>

BOOLEAN SmmIsSchedulable (IN  EFI_SMM_DRIVER_ENTRY *DriverEntry)
{
    EFI_STATUS  Status;
    UINT8       *Iterator;
    BOOLEAN     Operator;
    BOOLEAN     Operator2;
    EFI_GUID    DriverGuid;
    VOID        *Interface;

    Operator = FALSE;
    Operator2 = FALSE;

    if (DriverEntry->After || DriverEntry->Before) {
        //
        // If Before or After Depex skip as SmmInsertOnScheduledQueueWhileProcessingBeforeAndAfter ()
        // processes them.
        //
        return FALSE;
    }

    if (DriverEntry->Depex == NULL) {
        //
        // A NULL Depex means that the SMM driver is schedulable.
        //
        //ASSERT (FALSE);
        return TRUE;
    }

    //
    // Clean out memory leaks in Depex Boolean stack. Leaks are only caused by
    // incorrectly formed DEPEX expressions
    //
    mDepexEvaluationStackPointer = mDepexEvaluationStack;

    Iterator = DriverEntry->Depex;

    while (TRUE) {
        //
        // Check to see if we are attempting to fetch dependency expression instructions
        // past the end of the dependency expression.
        //
        if (((UINTN)Iterator - (UINTN)DriverEntry->Depex) >= DriverEntry->DepexSize) {
            return FALSE;
        }

        //
        // Look at the opcode of the dependency expression instruction.
        //
        switch (*Iterator) {
        case EFI_DEP_BEFORE:
        case EFI_DEP_AFTER:
        //
        // For a well-formed Dependency Expression, the code should never get here.
        // The BEFORE and AFTER are processed prior to this routine's invocation.
        // If the code flow arrives at this point, there was a BEFORE or AFTER
        // that were not the first opcodes.
        //
            ASSERT (FALSE);
        case EFI_DEP_SOR:
            //
            // These opcodes can only appear once as the first opcode.  If it is found
            // at any other location, then the dependency expression evaluates to FALSE
            //
            if (Iterator != DriverEntry->Depex) {
                return FALSE;
            }
            //
            // Otherwise, it is the first opcode and should be treated as a NOP.
            //
            break;
        case EFI_DEP_PUSH:
            //
            // Push operator is followed by a GUID. Test to see if the GUID protocol
            // is installed and push the boolean result on the stack.
            //

            MemCpy (&DriverGuid, Iterator + 1, sizeof (EFI_GUID));

            Status = gSmstTable2->SmmLocateProtocol (&DriverGuid, NULL, &Interface);
            if (EFI_ERROR (Status)) {
                //
                // For SMM Driver, it may depend on uefi protocols
                //
                Status = pBS->LocateProtocol (&DriverGuid, NULL, &Interface);
            }

            if (EFI_ERROR (Status)) {
                Status = PushBool (FALSE);
            } else {
                *Iterator = EFI_DEP_REPLACE_TRUE;
                Status = PushBool (TRUE);
            }
            if (EFI_ERROR (Status)) {
                return FALSE;
            }

            Iterator += sizeof (EFI_GUID);
            break;
        case EFI_DEP_AND:
            Status = PopBool (&Operator);
            if (EFI_ERROR (Status)) {
                return FALSE;
            }

            Status = PopBool (&Operator2);
            if (EFI_ERROR (Status)) {
                return FALSE;
            }

            Status = PushBool ((BOOLEAN)(Operator && Operator2));
            if (EFI_ERROR (Status)) {
                return FALSE;
            }
            break;
        case EFI_DEP_OR:
            Status = PopBool (&Operator);
            if (EFI_ERROR (Status)) {
                return FALSE;
            }

            Status = PopBool (&Operator2);
            if (EFI_ERROR (Status)) {
                return FALSE;
            }

            Status = PushBool ((BOOLEAN)(Operator || Operator2));
            if (EFI_ERROR (Status)) {
                return FALSE;
            }
            break;
        case EFI_DEP_NOT:
            Status = PopBool (&Operator);
            if (EFI_ERROR (Status)) {
                return FALSE;
            }

            Status = PushBool ((BOOLEAN)(!Operator));
            if (EFI_ERROR (Status)) {
                return FALSE;
            }
            break;
        case EFI_DEP_TRUE:
            Status = PushBool (TRUE);
            if (EFI_ERROR (Status)) {
                return FALSE;
            }
            break;
        case EFI_DEP_FALSE:
            Status = PushBool (FALSE);
            if (EFI_ERROR (Status)) {
                return FALSE;
            }
            break;
        case EFI_DEP_END:
            Status = PopBool (&Operator);
            if (EFI_ERROR (Status)) {
                return FALSE;
            }
            return Operator;
        case EFI_DEP_REPLACE_TRUE:
            Status = PushBool (TRUE);
            if (EFI_ERROR (Status)) {
                return FALSE;
            }

            Iterator += sizeof (EFI_GUID);
            break;
        default:
            goto Done;
        }

        //
        // Skip over the Dependency Op Code we just processed in the switch.
        // The math is done out of order, but it should not matter. That is
        // we may add in the sizeof (EFI_GUID) before we account for the OP Code.
        // This is not an issue, since we just need the correct end result. You
        // need to be careful using Iterator in the loop as it's intermediate value
        // may be strange.
        //
        Iterator++;
    }

    Done:
    return FALSE;
}

//<AMI_PHDR_START>
//---------------------------------------------------------------------------
//
// Procedure: EfiInitializeFwVolDevicepathNode
//
// Description: Create Firmware volume device path.
//
// Input:
//  IN OUT MEDIA_FW_VOL_FILEPATH_DEVICE_PATH     *FvDevicePathNode,
//  IN     EFI_GUID                              *NameGuid

//
// Output: VOID
//---------------------------------------------------------------------------
//<AMI_PHDR_END>

VOID EFIAPI EfiInitializeFwVolDevicepathNode (
    IN OUT MEDIA_FW_VOL_FILEPATH_DEVICE_PATH     *FvDevicePathNode,
    IN     EFI_GUID                              *NameGuid
)
{
    //
    // EFI Specification extension on Media Device Path. MEDIA_FW_VOL_FILEPATH_DEVICE_PATH is adopted by UEFI later and added in UEFI2.10.
    // In EdkCompatibility Package, we only support MEDIA_FW_VOL_FILEPATH_DEVICE_PATH that complies with
    // EFI 1.10 and UEFI 2.10.
    //

    FvDevicePathNode->Header.Type     = MEDIA_DEVICE_PATH;
    FvDevicePathNode->Header.SubType  = MEDIA_FV_FILEPATH_DP;
    SetDevicePathNodeLength (&FvDevicePathNode->Header, sizeof (MEDIA_FW_VOL_FILEPATH_DEVICE_PATH));

    MemCpy (&FvDevicePathNode->NameGuid, NameGuid, sizeof(EFI_GUID));
}

//<AMI_PHDR_START>
//---------------------------------------------------------------------------
//
// Procedure: SmmDisplayDiscoveredNotDispatched
//
// Description: Display to debug output drivers discovered, but not loaded.
//
// Input: VOID
//
// Output: VOID
//---------------------------------------------------------------------------
//<AMI_PHDR_END>

VOID SmmDisplayDiscoveredNotDispatched(VOID)
{
    LIST_ENTRY                   *Link;
    EFI_SMM_DRIVER_ENTRY         *DriverEntry;

    for (Link = mDiscoveredList.ForwardLink;Link !=&mDiscoveredList; Link = Link->ForwardLink) {
        DriverEntry = CR(Link, EFI_SMM_DRIVER_ENTRY, Link, EFI_SMM_DRIVER_ENTRY_SIGNATURE);
        if (DriverEntry->Dependent) {
            TRACE ((-1, "SMM Driver %g was discovered but not loaded!!\n", &DriverEntry->FileName));
        }
    }
}

//<AMI_PHDR_START>
//---------------------------------------------------------------------------
//
// Procedure: FvHasBeenProcessed
//
// Description:
//
// Input:
//
// Output:
//---------------------------------------------------------------------------
//<AMI_PHDR_END>

BOOLEAN FvHasBeenProcessed (IN EFI_HANDLE  FvHandle)
{
    LIST_ENTRY    *Link;
    KNOWN_HANDLE  *KnownHandle;

    for (Link = mFvHandleList.ForwardLink; Link != &mFvHandleList; Link = Link->ForwardLink) {
        KnownHandle = CR(Link, KNOWN_HANDLE, Link, KNOWN_HANDLE_SIGNATURE);
        if (KnownHandle->Handle == FvHandle) {
            return TRUE;
        }
    }
    return FALSE;
}

//<AMI_PHDR_START>
//---------------------------------------------------------------------------
//
// Procedure: FvIsBeingProcesssed
//
// Description: This firmware volume is marked as being processed.
//
// Input: IN EFI_HANDLE  FvHandle
//
// Output: VOID
//---------------------------------------------------------------------------
//<AMI_PHDR_END>

VOID FvIsBeingProcesssed(IN EFI_HANDLE  FvHandle)
{
    KNOWN_HANDLE  *KnownHandle;

    KnownHandle = AllocatePool (sizeof (KNOWN_HANDLE));
    ASSERT (KnownHandle != NULL);

    KnownHandle->Signature = KNOWN_HANDLE_SIGNATURE;
    KnownHandle->Handle = FvHandle;
    InsertTailList (&mFvHandleList, &KnownHandle->Link);
}

//<AMI_PHDR_START>
//---------------------------------------------------------------------------
//
// Procedure: SmmFvToDevicePath
//
// Description: Create device path for Driver.
//
// Input:
//  IN EFI_FIRMWARE_VOLUME2_PROTOCOL   *Fv
//  IN EFI_HANDLE                      FvHandle
//  IN EFI_GUID                        *DriverName
//
// Output: EFI_DEVICE_PATH_PROTOCOL *
//---------------------------------------------------------------------------
//<AMI_PHDR_END>

EFI_DEVICE_PATH_PROTOCOL * SmmFvToDevicePath (
    IN EFI_FIRMWARE_VOLUME2_PROTOCOL   *Fv,
    IN EFI_HANDLE                      FvHandle,
    IN EFI_GUID                        *DriverName
)
{
    EFI_STATUS                          Status;
    EFI_DEVICE_PATH_PROTOCOL            *FvDevicePath;
    EFI_DEVICE_PATH_PROTOCOL            *FileNameDevicePath;

    //
    // Remember the device path of the FV
    //
    Status = pBS->HandleProtocol(FvHandle, &gEfiDevicePathProtocolGuid, (VOID **)&FvDevicePath);
    if (EFI_ERROR (Status)) {
        FileNameDevicePath = NULL;
    } else {
        //
        // Build a device path to the file in the FV to pass into gBS->LoadImage
        //
        EfiInitializeFwVolDevicepathNode (&mFvDevicePath.File, DriverName);
        SetDevicePathEndNode (&mFvDevicePath.End);

        //
        // Note: FileNameDevicePath is in DXE memory
        //
        FileNameDevicePath = DPAdd (
            FvDevicePath,
            (EFI_DEVICE_PATH_PROTOCOL *)&mFvDevicePath
        );
    }
    return FileNameDevicePath;
}

//<AMI_PHDR_START>
//---------------------------------------------------------------------------
//
// Procedure: SmmPreProcessDepex
//
// Description: Check driver dependencies for SOR, BEFORE, or AFTER, and update DriverEntry.
//
// Input: IN OUT EFI_SMM_DRIVER_ENTRY  *DriverEntry
//
// Output: EFI_STATUS
//---------------------------------------------------------------------------
//<AMI_PHDR_END>

EFI_STATUS SmmPreProcessDepex (
    IN OUT EFI_SMM_DRIVER_ENTRY  *DriverEntry
)
{
    UINT8  *Iterator;

    Iterator = DriverEntry->Depex;
    if (*Iterator == EFI_DEP_SOR) {
        DriverEntry->Unrequested = TRUE;
    } else {
        DriverEntry->Dependent = TRUE;
    }

    if (*Iterator == EFI_DEP_BEFORE) {
        DriverEntry->Before = TRUE;
    } else if (*Iterator == EFI_DEP_AFTER) {
        DriverEntry->After = TRUE;
    }

    if (DriverEntry->Before || DriverEntry->After) {
        MemCpy (&DriverEntry->BeforeAfterGuid, Iterator + 1, sizeof (EFI_GUID));
    }

    return EFI_SUCCESS;
}

//<AMI_PHDR_START>
//---------------------------------------------------------------------------
//
// Procedure: SmmGetDepexSectionAndPreProccess
//
// Description: Get driver depex section.
//
// Input: IN OUT EFI_SMM_DRIVER_ENTRY  *DriverEntry
//
// Output: EFI_STATUS
//---------------------------------------------------------------------------
//<AMI_PHDR_END>

EFI_STATUS SmmGetDepexSectionAndPreProccess (
     IN OUT EFI_SMM_DRIVER_ENTRY  *DriverEntry
)
{
    EFI_STATUS                     Status;
    EFI_SECTION_TYPE               SectionType;
    UINT32                         AuthenticationStatus;
    EFI_FIRMWARE_VOLUME2_PROTOCOL  *Fv;

    Fv = DriverEntry->Fv;

    //
    // Grab Depex info, it will never be free'ed.
    // (Note: DriverEntry->Depex is in DXE memory)
    //
    SectionType = EFI_SECTION_SMM_DEPEX;
    Status = Fv->ReadSection (
        DriverEntry->Fv,
        &DriverEntry->FileName,
        SectionType,
        0,
        &DriverEntry->Depex,
        (UINTN *)&DriverEntry->DepexSize,
        &AuthenticationStatus
    );
    if (EFI_ERROR (Status)) {
        if (Status == EFI_PROTOCOL_ERROR) {
            //
            // The section extraction protocol failed so set protocol error flag
            //
            DriverEntry->DepexProtocolError = TRUE;
        } else {
            //
            // If no Depex assume depend on all architectural protocols
            //
            DriverEntry->Depex = NULL;
            DriverEntry->Dependent = TRUE;
            DriverEntry->DepexProtocolError = FALSE;
        }
    } else {
        //
        // Set Before, After, and Unrequested state information based on Depex
        // Driver will be put in Dependent or Unrequested state
        //
        SmmPreProcessDepex (DriverEntry);
        DriverEntry->DepexProtocolError = FALSE;
    }
    return Status;
}

//<AMI_PHDR_START>
//---------------------------------------------------------------------------
//
// Procedure: SmmAddToDriverList
//
// Description: Add Driver to database for processing.
//
// Input:
//  IN EFI_FIRMWARE_VOLUME2_PROTOCOL  *Fv
//  IN EFI_HANDLE                     FvHandle
//  IN EFI_GUID                       *DriverName
//
// Output: EFI_STATUS
//---------------------------------------------------------------------------
//<AMI_PHDR_END>

EFI_STATUS SmmAddToDriverList (
    IN EFI_FIRMWARE_VOLUME2_PROTOCOL  *Fv,
    IN EFI_HANDLE                     FvHandle,
    IN EFI_GUID                       *DriverName
)
{
    EFI_SMM_DRIVER_ENTRY  *DriverEntry;

    //
    // Create the Driver Entry for the list. ZeroPool initializes lots of variables to
    // NULL or FALSE.
    //
    DriverEntry = MallocZ(sizeof (EFI_SMM_DRIVER_ENTRY));
    ASSERT (DriverEntry != NULL);

    DriverEntry->Signature        = EFI_SMM_DRIVER_ENTRY_SIGNATURE;
    MemCpy(&DriverEntry->FileName, DriverName, sizeof(EFI_GUID));
    DriverEntry->FvHandle         = FvHandle;
    DriverEntry->Fv               = Fv;
    DriverEntry->FvFileDevicePath = SmmFvToDevicePath (Fv, FvHandle, DriverName);

    SmmGetDepexSectionAndPreProccess (DriverEntry);

    InsertTailList (&mDiscoveredList, &DriverEntry->Link);
    gRequestDispatch = TRUE;

    return EFI_SUCCESS;
}

//<AMI_PHDR_START>
//---------------------------------------------------------------------------
//
// Procedure: SmmLoadImage
//
// Description: Load driver into memory and give control.
//
// Input: IN OUT EFI_SMM_DRIVER_ENTRY  *DriverEntry
//
// Output: EFI_STATUS
//---------------------------------------------------------------------------
//<AMI_PHDR_END>

EFI_STATUS EFIAPI SmmLoadImage (
    IN OUT EFI_SMM_DRIVER_ENTRY  *DriverEntry
)
{
    UINT32                         AuthenticationStatus;
    VOID                           *Buffer;
    UINTN                          Size;
    //UINTN                          PageCount;
    EFI_GUID                       *NameGuid;
    EFI_STATUS                     Status;
    //EFI_HANDLE                     DeviceHandle;
    //EFI_PHYSICAL_ADDRESS           DstBuffer;
    EFI_DEVICE_PATH_PROTOCOL       *FilePath;
    EFI_FIRMWARE_VOLUME2_PROTOCOL  *Fv;
    //PE_COFF_LOADER_IMAGE_CONTEXT   ImageContext;

    Buffer               = NULL;
    Size                 = 0;
    Fv                   = DriverEntry->Fv;
    NameGuid             = &DriverEntry->FileName;
    FilePath             = DriverEntry->FvFileDevicePath;

    AuthenticationStatus = 0;

    //
    // Try reading PE32 section firstly
    //
    Status = Fv->ReadSection (
        Fv,
        NameGuid,
        EFI_SECTION_PE32,
        0,
        &Buffer,
        &Size,
        &AuthenticationStatus
    );

/*
    if (EFI_ERROR (Status)) {
        //
        // Try reading TE section secondly
        //
        Buffer = NULL;
        Size   = 0;
        Status = Fv->ReadSection (
            Fv,
            NameGuid,
            EFI_SECTION_TE,
            0,
            &Buffer,
            &Size,
            &AuthenticationStatus
        );
    }
*/

  if (EFI_ERROR (Status)) {
    if (Buffer != NULL) {
      Status = pBS->FreePool (Buffer);
    }
    return Status;
  }

    gRegisterForPi = TRUE;
    Status=EfiSmmRegister(NULL, FilePath, Buffer, Size, 
                            &DriverEntry->ImageHandle, FALSE);
    gRegisterForPi = FALSE;
/*
    //
    // Initialize ImageContext
    //
    ImageContext.Handle = Buffer;
    ImageContext.ImageRead = PeCoffLoaderImageReadFromMemory;

    //
    // Get information about the image being loaded
    //
    Status = PeCoffLoaderGetImageInfo (&ImageContext);
    if (EFI_ERROR (Status)) {
        if (Buffer != NULL) {
            Status = gBS->FreePool (Buffer);
        }
        return Status;
    }
    //
    // if Loading module at Fixed Address feature is enabled, then  cut out a memory range started from TESG BASE
    // to hold the Smm driver code
    //
    if (PcdGet64(PcdLoadModuleAtFixAddressEnable) != 0) {
        //
        // Get the fixed loading address assigned by Build tool
        //
        Status = GetPeCoffImageFixLoadingAssignedAddress (&ImageContext);
        if (!EFI_ERROR (Status)) {
            //
            // Since the memory range to load Smm core alreay been cut out, so no need to allocate and free this range
            // following statements is to bypass SmmFreePages
            //
            PageCount = 0;
            DstBuffer = (UINTN)gLoadModuleAtFixAddressSmramBase;
        } else {
            DEBUG ((EFI_D_INFO|EFI_D_LOAD, "LOADING MODULE FIXED ERROR: Failed to load module at fixed address. \n"));
            //
            // allocate the memory to load the SMM driver
            //
            PageCount = (UINTN)EFI_SIZE_TO_PAGES(ImageContext.ImageSize + ImageContext.SectionAlignment);
            DstBuffer = (UINTN)(-1);

            Status = SmmAllocatePages (
               AllocateMaxAddress,
               EfiRuntimeServicesCode,
               PageCount,
               &DstBuffer
               );
            if (EFI_ERROR (Status)) {
                if (Buffer != NULL) {
                    Status = gBS->FreePool (Buffer);
                }
                return Status;
            }
            ImageContext.ImageAddress = (EFI_PHYSICAL_ADDRESS)DstBuffer;
        }
    } else {
        PageCount = (UINTN)EFI_SIZE_TO_PAGES(ImageContext.ImageSize + ImageContext.SectionAlignment);
        DstBuffer = (UINTN)(-1);

        Status = SmmAllocatePages (
            AllocateMaxAddress,
            EfiRuntimeServicesCode,
            PageCount,
            &DstBuffer
            );
        if (EFI_ERROR (Status)) {
            if (Buffer != NULL) {
                Status = gBS->FreePool (Buffer);
            }
            return Status;
        }

        ImageContext.ImageAddress = (EFI_PHYSICAL_ADDRESS)DstBuffer;
    }
    //
    // Align buffer on section boundary
    //
    ImageContext.ImageAddress += ImageContext.SectionAlignment - 1;
    ImageContext.ImageAddress &= ~(ImageContext.SectionAlignment - 1);

    //
    // Load the image to our new buffer
    //
    Status = PeCoffLoaderLoadImage (&ImageContext);
    if (EFI_ERROR (Status)) {
        if (Buffer != NULL) {
            Status = gBS->FreePool (Buffer);
        }
        SmmFreePages (DstBuffer, PageCount);
        return Status;
    }

    //
    // Relocate the image in our new buffer
    //
    Status = PeCoffLoaderRelocateImage (&ImageContext);
    if (EFI_ERROR (Status)) {
        if (Buffer != NULL) {
            Status = gBS->FreePool (Buffer);
        }
        SmmFreePages (DstBuffer, PageCount);
        return Status;
    }

    //
    // Flush the instruction cache so the image data are written before we execute it
    //
    InvalidateInstructionCacheRange ((VOID *)(UINTN) ImageContext.ImageAddress, (UINTN) ImageContext.ImageSize);

    //
    // Save Image EntryPoint in DriverEntry
    //
    DriverEntry->ImageEntryPoint  = ImageContext.EntryPoint;
    DriverEntry->ImageBuffer      = DstBuffer;
    DriverEntry->NumberOfPage     = PageCount;

    //
    // Allocate a Loaded Image Protocol in EfiBootServicesData
    //
    Status = gBS->AllocatePool (EfiBootServicesData, sizeof (EFI_LOADED_IMAGE_PROTOCOL), (VOID **)&DriverEntry->LoadedImage);
    if (EFI_ERROR (Status)) {
        if (Buffer != NULL) {
            Status = gBS->FreePool (Buffer);
        }
        SmmFreePages (DstBuffer, PageCount);
        return Status;
    }

    //
    // Fill in the remaining fields of the Loaded Image Protocol instance.
    // Note: ImageBase is an SMRAM address that can not be accessed outside of SMRAM if SMRAM window is closed.
    //
    DriverEntry->LoadedImage->Revision      = EFI_LOADED_IMAGE_PROTOCOL_REVISION;
    DriverEntry->LoadedImage->ParentHandle  = gThisImageHandle;
    DriverEntry->LoadedImage->SystemTable   = pST;
    DriverEntry->LoadedImage->DeviceHandle  = DeviceHandle;

    //
    // Make an EfiBootServicesData buffer copy of FilePath
    //
    Status = gBS->AllocatePool (EfiBootServicesData, GetDevicePathSize (FilePath), (VOID **)&DriverEntry->LoadedImage->FilePath);
    if (EFI_ERROR (Status)) {
        if (Buffer != NULL) {
            Status = gBS->FreePool (Buffer);
        }
        SmmFreePages (DstBuffer, PageCount);
        return Status;
    }
    CopyMem (DriverEntry->LoadedImage->FilePath, FilePath, GetDevicePathSize (FilePath));

    DriverEntry->LoadedImage->ImageBase     = (VOID *)(UINTN)DriverEntry->ImageBuffer;
    DriverEntry->LoadedImage->ImageSize     = ImageContext.ImageSize;
    DriverEntry->LoadedImage->ImageCodeType = EfiRuntimeServicesCode;
    DriverEntry->LoadedImage->ImageDataType = EfiRuntimeServicesData;

    //
    // Create a new image handle in the UEFI handle database for the SMM Driver
    //
    DriverEntry->ImageHandle = NULL;
    Status = gBS->InstallMultipleProtocolInterfaces (
        &DriverEntry->ImageHandle,
        &gEfiLoadedImageProtocolGuid, DriverEntry->LoadedImage,
        NULL
        );

    //
    // Print the load address and the PDB file name if it is available
    //

    //  DEBUG_CODE_BEGIN ();
#if EFI_DEBUG
    {
        UINTN Index;
        UINTN StartIndex;
        CHAR8 EfiFileName[256];


        TRACE ((-1,
            "Loading driver at 0x%11p EntryPoint=0x%11p ",
            (VOID *)(UINTN) ImageContext.ImageAddress,
            FUNCTION_ENTRY_POINT (ImageContext.EntryPoint)));


        //
        // Print Module Name by Pdb file path.
        // Windows and Unix style file path are all trimmed correctly.
        //
        if (ImageContext.PdbPointer != NULL) {
            StartIndex = 0;
            for (Index = 0; ImageContext.PdbPointer[Index] != 0; Index++) {
                if ((ImageContext.PdbPointer[Index] == '\\') || (ImageContext.PdbPointer[Index] == '/')) {
                    StartIndex = Index + 1;
                }
            }
            //
            // Copy the PDB file name to our temporary string, and replace .pdb with .efi
            // The PDB file name is limited in the range of 0~255.
            // If the length is bigger than 255, trim the redudant characters to avoid overflow in array boundary.
            //
            for (Index = 0; Index < sizeof (EfiFileName) - 4; Index++) {
                EfiFileName[Index] = ImageContext.PdbPointer[Index + StartIndex];
                if (EfiFileName[Index] == 0) {
                    EfiFileName[Index] = '.';
                }
                if (EfiFileName[Index] == '.') {
                    EfiFileName[Index + 1] = 'e';
                    EfiFileName[Index + 2] = 'f';
                    EfiFileName[Index + 3] = 'i';
                    EfiFileName[Index + 4] = 0;
                    break;
                }
            }

            if (Index == sizeof (EfiFileName) - 4) {
                EfiFileName[Index] = 0;
            }
            TRACE ((-1, "%a", EfiFileName)); // &Image->ImageContext.PdbPointer[StartIndex]));
        }
        TRACE ((-1, "\n"));
    }
//  DEBUG_CODE_END ();
#endif

    //
    // Free buffer allocated by Fv->ReadSection.
    //
    // The UEFI Boot Services FreePool() function must be used because Fv->ReadSection
    // used the UEFI Boot Services AllocatePool() function
    //
*/
      Status = pBS->FreePool(Buffer);
      return Status;
}

//<AMI_PHDR_START>
//---------------------------------------------------------------------------
//
// Procedure: SmmInsertOnScheduledQueueWhileProcessingBeforeAndAfter
//
// Description: Add drivers on queue with before or after dependencies.
//
// Input: IN EFI_SMM_DRIVER_ENTRY   *InsertedDriverEntry
//
// Output: VOID
//---------------------------------------------------------------------------
//<AMI_PHDR_END>

VOID SmmInsertOnScheduledQueueWhileProcessingBeforeAndAfter (
      IN  EFI_SMM_DRIVER_ENTRY   *InsertedDriverEntry
)
{
    LIST_ENTRY            *Link;
    EFI_SMM_DRIVER_ENTRY *DriverEntry;

    //
    // Process Before Dependency
    //
    for (Link = mDiscoveredList.ForwardLink; Link != &mDiscoveredList; Link = Link->ForwardLink) {
        DriverEntry = CR(Link, EFI_SMM_DRIVER_ENTRY, Link, EFI_SMM_DRIVER_ENTRY_SIGNATURE);
        if (DriverEntry->Before && DriverEntry->Dependent) {
            if (! guidcmp (&InsertedDriverEntry->FileName, &DriverEntry->BeforeAfterGuid)) {
                //
                // Recursively process BEFORE
                //
                SmmInsertOnScheduledQueueWhileProcessingBeforeAndAfter (DriverEntry);
            }
        }
    }

    //
    // Convert driver from Dependent to Scheduled state
    //

    InsertedDriverEntry->Dependent = FALSE;
    InsertedDriverEntry->Scheduled = TRUE;
    InsertTailList (&mScheduledQueue, &InsertedDriverEntry->ScheduledLink);

    //
    // Process After Dependency
    //
    for (Link = mDiscoveredList.ForwardLink; Link != &mDiscoveredList; Link = Link->ForwardLink) {
        DriverEntry = CR(Link, EFI_SMM_DRIVER_ENTRY, Link, EFI_SMM_DRIVER_ENTRY_SIGNATURE);
        if (DriverEntry->After && DriverEntry->Dependent) {
            if (!guidcmp (&InsertedDriverEntry->FileName, &DriverEntry->BeforeAfterGuid)) {
                //
                // Recursively process AFTER
                //
                SmmInsertOnScheduledQueueWhileProcessingBeforeAndAfter (DriverEntry);
            }
        }
    }
}

//<AMI_PHDR_START>
//---------------------------------------------------------------------------
//
// Procedure: SmmDispatcher
//
// Description: Dispatch drivers that dependencies are met.
//
// Input: VOID
//
// Output: VOID
//---------------------------------------------------------------------------
//<AMI_PHDR_END>

EFI_STATUS SmmDispatcher(VOID)
{
    EFI_STATUS            Status;
    EFI_STATUS            ReturnStatus;
    LIST_ENTRY            *Link;
    EFI_SMM_DRIVER_ENTRY  *DriverEntry;
    BOOLEAN               ReadyToRun;

    if (!gRequestDispatch) {
        return EFI_NOT_FOUND;
    }

    if (gDispatcherRunning) {
        //
        // If the dispatcher is running don't let it be restarted.
        //
        return EFI_ALREADY_STARTED;
    }

    gDispatcherRunning = TRUE;
    ReturnStatus = EFI_NOT_FOUND;

    do {
        //
        // Drain the Scheduled Queue
        //
        while (!IsListEmpty (&mScheduledQueue)) {
            DriverEntry = CR (
                mScheduledQueue.ForwardLink,
                EFI_SMM_DRIVER_ENTRY,
                ScheduledLink,
                EFI_SMM_DRIVER_ENTRY_SIGNATURE
            );

            //
            // Load the SMM Driver image into memory. If the Driver was transitioned from
            // Untrusted to Scheduled it would have already been loaded so we may need to
            // skip the LoadImage
            //
            if (DriverEntry->ImageHandle == NULL) {
                Status = SmmLoadImage (DriverEntry);

                //
                // Update the driver state to reflect that it's been loaded
                //
                if (EFI_ERROR (Status)) {
                    if (Status == EFI_SECURITY_VIOLATION) {
                        //
                        // Take driver from Scheduled to Untrusted state
                        //
                        DriverEntry->Untrusted = TRUE;
                    } else {
                        //
                        // The SMM Driver could not be loaded, and do not attempt to load or start it again.
                        // Take driver from Scheduled to Initialized.
                        //
                        // This case include the Never Trusted state if EFI_ACCESS_DENIED is returned
                        //
                        DriverEntry->Initialized  = TRUE;
                    }

                    DriverEntry->Scheduled = FALSE;
                    RemoveEntryList (&DriverEntry->ScheduledLink);

                    //
                    // If it's an error don't try the StartImage
                    //
                    continue;
                }
            }

            DriverEntry->Scheduled    = FALSE;
            DriverEntry->Initialized  = TRUE;
            RemoveEntryList (&DriverEntry->ScheduledLink);
/*
            REPORT_STATUS_CODE_WITH_EXTENDED_DATA (
                EFI_PROGRESS_CODE,
                EFI_SOFTWARE_SMM_DRIVER | EFI_SW_PC_INIT_BEGIN,
                &DriverEntry->ImageHandle,
                sizeof(DriverEntry->ImageHandle)
            );

            //
            // For each SMM driver, pass NULL as ImageHandle
            //
            Status = ((EFI_IMAGE_ENTRY_POINT)(UINTN)DriverEntry->ImageEntryPoint)(DriverEntry->ImageHandle, pST);
            if (EFI_ERROR(Status)){
                SmmFreePages(DriverEntry->ImageBuffer, DriverEntry->NumberOfPage);
            }

            REPORT_STATUS_CODE_WITH_EXTENDED_DATA (
                EFI_PROGRESS_CODE,
                EFI_SOFTWARE_SMM_DRIVER | EFI_SW_PC_INIT_END,
                &DriverEntry->ImageHandle,
                sizeof(DriverEntry->ImageHandle)
            );
*/
            ReturnStatus = EFI_SUCCESS;
        }

        //
        // Search DriverList for items to place on Scheduled Queue
        //
        ReadyToRun = FALSE;
        for (Link = mDiscoveredList.ForwardLink; Link != &mDiscoveredList; Link = Link->ForwardLink) {
            DriverEntry = CR (Link, EFI_SMM_DRIVER_ENTRY, Link, EFI_SMM_DRIVER_ENTRY_SIGNATURE);

            if (DriverEntry->DepexProtocolError){
                //
                // If Section Extraction Protocol did not let the Depex be read before retry the read
                //
                Status = SmmGetDepexSectionAndPreProccess (DriverEntry);
            }

            if (DriverEntry->Dependent) {
                if (SmmIsSchedulable (DriverEntry)) {
                    SmmInsertOnScheduledQueueWhileProcessingBeforeAndAfter (DriverEntry);
                    ReadyToRun = TRUE;
                }
            }
        }
    } while (ReadyToRun);

    //
    // If there is no more SMM driver to dispatch, stop the dispatch request
    //
    gRequestDispatch = FALSE;
    for (Link = mDiscoveredList.ForwardLink; Link != &mDiscoveredList; Link = Link->ForwardLink) {
        DriverEntry = CR (Link, EFI_SMM_DRIVER_ENTRY, Link, EFI_SMM_DRIVER_ENTRY_SIGNATURE);

        if (!DriverEntry->Initialized){
        //
        // We have SMM driver pending to dispatch
        //
            gRequestDispatch = TRUE;
            break;
        }
    }

    gDispatcherRunning = FALSE;

    return ReturnStatus;
}

//<AMI_PHDR_START>
//---------------------------------------------------------------------------
//
// Procedure: SmmDriverDispatchHandler
//
// Description: Dispatch SMM drivers
//
// Input: VOID
//
// Output: VOID
//---------------------------------------------------------------------------
//<AMI_PHDR_END>

VOID SmmDriverDispatchHandler ()
{
    EFI_STATUS                    Status;
    UINTN                         HandleCount;
    EFI_HANDLE                    *HandleBuffer;
    EFI_STATUS                    GetNextFileStatus;
    EFI_STATUS                    SecurityStatus;
    EFI_FIRMWARE_VOLUME2_PROTOCOL *Fv;
    EFI_DEVICE_PATH_PROTOCOL      *FvDevicePath;
    EFI_HANDLE                    FvHandle;
    EFI_GUID                      NameGuid;
    UINTN                         Key;
    EFI_FV_FILETYPE               Type;
    EFI_FV_FILE_ATTRIBUTES        Attributes;
    UINTN                         Size;
    EFI_SMM_DRIVER_ENTRY          *DriverEntry;
    EFI_GUID                      *AprioriFile;
    UINTN                         AprioriEntryCount;
    UINTN                         Index;
    LIST_ENTRY                    *Link;
    UINT32                        AuthenticationStatus;
    UINTN                         SizeOfBuffer;

    HandleBuffer = NULL;
    Status = pBS->LocateHandleBuffer (
        ByProtocol,
        &gEfiFirmwareVolume2ProtocolGuid,
        NULL,
        &HandleCount,
        &HandleBuffer
    );
    if (EFI_ERROR (Status)) return; //return EFI_NOT_FOUND;

    for (Index = 0; Index < HandleCount; Index++) {
        FvHandle = HandleBuffer[Index];

        if (FvHasBeenProcessed (FvHandle)) {
            //
            // This Fv has already been processed so lets skip it!
            //
            continue;
        }

        //
        // Since we are about to process this Fv mark it as processed.
        //
        FvIsBeingProcesssed (FvHandle);

        Status = pBS->HandleProtocol (FvHandle, &gEfiFirmwareVolume2ProtocolGuid, (VOID **)&Fv);
        if (EFI_ERROR (Status)) {
            //
            // FvHandle must have a Firmware Volume2 Protocol thus we should never get here.
            //
            ASSERT (FALSE);
            continue;
        }

        Status = pBS->HandleProtocol (FvHandle, &gEfiDevicePathProtocolGuid, (VOID **)&FvDevicePath);
        if (EFI_ERROR (Status)) {
            //
            // The Firmware volume doesn't have device path, can't be dispatched.
            //
            continue;
        }

        //
        // If the Security Architectural Protocol has not been located yet, then attempt to locate it
        //
        if (mSecurity == NULL) {
            pBS->LocateProtocol (&gEfiSecurityArchProtocolGuid, NULL, (VOID**)&mSecurity);
        }

        //
        // Evaluate the authentication status of the Firmware Volume through
        // Security Architectural Protocol
        //
        if (mSecurity != NULL) {
            SecurityStatus = mSecurity->FileAuthenticationState (
                mSecurity,
                0,
                FvDevicePath
            );
            if (SecurityStatus != EFI_SUCCESS) {
                //
                // Security check failed. The firmware volume should not be used for any purpose.
                //
                continue;
            }
        }

        //
        // Discover Drivers in FV and add them to the Discovered Driver List.
        // Process EFI_FV_FILETYPE_SMM type and then EFI_FV_FILETYPE_COMBINED_SMM_DXE
        //
        for (Index = 0; Index < sizeof (mSmmFileTypes)/sizeof (EFI_FV_FILETYPE); Index++) {
        //
        // Initialize the search key
        //
            Key = 0;
            do {
                Type = mSmmFileTypes[Index];
                GetNextFileStatus = Fv->GetNextFile (
                    Fv,
                    &Key,
                    &Type,
                    &NameGuid,
                    &Attributes,
                    &Size
                );
                if (!EFI_ERROR (GetNextFileStatus)) {
                    SmmAddToDriverList (Fv, FvHandle, &NameGuid);
                }
            } while (!EFI_ERROR (GetNextFileStatus));
        }

        //
        // Read the array of GUIDs from the Apriori file if it is present in the firmware volume
        // (Note: AprioriFile is in DXE memory)
        //
        AprioriFile = NULL;
        Status = Fv->ReadSection (
            Fv,
            &gAprioriGuid,
            EFI_SECTION_RAW,
            0,
            (VOID **)&AprioriFile,
            &SizeOfBuffer,
            &AuthenticationStatus
        );
        if (!EFI_ERROR (Status)) {
            AprioriEntryCount = SizeOfBuffer / sizeof (EFI_GUID);
        } else {
            AprioriEntryCount = 0;
        }

        //
        // Put drivers on Apriori List on the Scheduled queue. The Discovered List includes
        // drivers not in the current FV and these must be skipped since the a priori list
        // is only valid for the FV that it resided in.
        //

        for (Index = 0; Index < AprioriEntryCount; Index++) {
            for (Link = mDiscoveredList.ForwardLink; Link != &mDiscoveredList; Link = Link->ForwardLink) {
                DriverEntry = CR(Link, EFI_SMM_DRIVER_ENTRY, Link, EFI_SMM_DRIVER_ENTRY_SIGNATURE);
                if (!guidcmp (&DriverEntry->FileName, &AprioriFile[Index]) &&
                    (FvHandle == DriverEntry->FvHandle)
                    ){
                    DriverEntry->Dependent = FALSE;
                    DriverEntry->Scheduled = TRUE;
                    InsertTailList (&mScheduledQueue, &DriverEntry->ScheduledLink);
                    break;
                }
            }
        }

        //
        // Free data allocated by Fv->ReadSection ()
        //
        // The UEFI Boot Services FreePool() function must be used because Fv->ReadSection
        // used the UEFI Boot Services AllocatePool() function
        //
        pBS->FreePool (AprioriFile);
    }

    //
    // Execute the SMM Dispatcher on any newly discovered FVs and previously
    // discovered SMM drivers that have been discovered but not dispatched.
    //
    SmmDispatcher();
}
#endif

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
