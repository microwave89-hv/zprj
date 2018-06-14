//**********************************************************************
//**********************************************************************
//**                                                                  **
//**        (C)Copyright 1985-2010, American Megatrends, Inc.         **
//**                                                                  **
//**                       All Rights Reserved.                       **
//**                                                                  **
//**           5555 Oakbrook Pkwy, Suite 200, Norcross, GA 30093      **
//**                                                                  **
//**                       Phone: (770)-246-8600                      **
//**                                                                  **
//**********************************************************************
//**********************************************************************

//**********************************************************************
// $Header: /Alaska/SOURCE/Modules/CSM/Generic/Thunk/x86/thunk.c 49    10/07/13 9:41a Olegi $
//
// $Revision: 49 $
//
// $Date: 10/07/13 9:41a $
//**********************************************************************
// Revision History
// ----------------
// $Log: /Alaska/SOURCE/Modules/CSM/Generic/Thunk/x86/thunk.c $
// 
// 49    10/07/13 9:41a Olegi
// Undone previous checkin related to EIP125856 as it is causing assert
// during boot.
// 
// 48    8/30/13 4:25a Srikantakumarp
// [TAG]  		EIP125856
// [Category]  	Bug Fix
// [Severity]  	Normal
// [Symptom]  	Assert came in SetKbcPresenceInMiscInfo() when FarCall86()
// function is called first time in POST.
// [RootCause]  	BiosLessThan1MB value is used in
// SetKbcPresenceInMiscInfo(); and this has been initialized only after
// the function 0 csm16 call.
// [Solution]  	Returned from SetKbcPresenceInMiscInfo() if
// BiosLessThan1MB value is not initialized.
// [Files]  		thunk.c
// 
// 47    9/12/12 1:45a Srikantakumarp
// [TAG]  		EIP99561
// [Category]  	Bug Fix
// [Severity]  	Normal
// [Symptom]  	KbcEmulation enabled in Int86 call but NO_KBC_PRESENT_BIT
// bit not set properly.
// [RootCause]  	Incase of INT86 , it directly calls the interrupt service
// routine and it might be that the NO_KBC_PRESENT_BIT is not set
// according to the KbcEmulation enabled or disabled.
// [Solution]  	The NO_KBC_PRESENT_BIT is set according to the
// KbcEmulation enabled or disabled before the call to thunk in Int86
// function in thunk.c.
// [Files]  		thunk.c
// 
// 46    3/02/12 3:24a Rameshr
// [TAG]  		EIP81041
// [Category]  	Improvement
// [Description]  	Re-entrance support for Farcall86 and Int86 protocol
// function
// [Files]  		thunk.c
// 
// 45    10/19/11 3:31p Olegi
// [TAG]  		EIP72642, 72645, 72810
// [Category]  	Bug Fix
// [Severity]  	Important
// [Symptom]  	Adaptec x805 SAS Option ROM code hangs
// [RootCause]  	Adaptec ROM has a code that directly access KBC during
// INT handler. We did not have KBC emulation enabled for Int86 function.
// [Solution]  	Added enabling KBC emulation in Int86 function.
// [Files]  		thunk.c
// 
// 44    9/29/11 11:00a Olegi
// [TAG]  		EIP70382
// [Category]  	Improvement
// [Description]  	Clear keyboard status in BDA after FarCall86 execution.
// [Files]  		thunk.c
// 
// 43    12/14/10 4:46p Olegi
// [TAG]  		EIP50111
// [Category]  	Bug Fix
// [Severity]  	Important
// [Symptom]  	TPL asserts in some cases during LegacyBoot
// [RootCause]  	TPL.C asserts during LocateHandleBuffer call executed
// during LegacyBoot from FarCall86.
// [Solution]  	removed a call GetPs2SimpleTextInProtocolInterface
// execution during FarCall86. The existing handle of Ps2SimpleTextIn will
// be used.
// [Files]  		thunk.c
// 
// 42    10/23/10 3:22p Olegi
// Undone the changes related to moving TPL raising/lowering outside of
// FarCall86. This made the IF to be active during thunk that caused
// various problems.
// 
// 41    8/17/10 2:26p Olegi
// Reset PS/2 keyboard before legacy boot. EIP40711
// 
// 40    7/25/10 2:43p Olegi
// RaiseTPL/RestroreTPL are moved from FarCall86 to the ASM area.
// 
// 39    7/19/10 4:44p Olegi
// 
// 38    6/28/10 5:04p Olegi
// EIP26277: Added a callback notification on
// NonSmmEmul6064TrapProtocolGuid installation.
// 
// 37    6/19/10 12:32p Olegi
// Temporary undone the resolution for EIP26277 until the final resolution
// is found. Current changes causes ASSERT due to LocateHandle is executed
// on TPL_LEVEL_HIGH.
// 
// 36    2/22/10 9:46a Olegi
// Fixed the problem where some keys pressed on USB keyboard are lost
// during the transition to OpROM. EIP26277
// 
// 35    1/18/10 3:41a Rameshr
// NumLock,Capslock,Scroll Lock LED's synced properly between EFI and
// Legacy Mode.
// EIP 27917
// 
// 34    1/12/10 11:47a Olegi
// Copyright message updated.
// 
// 33    9/23/09 11:13a Olegi
// Changed the global variable name according to the coding standard.
// 
// 32    9/09/09 3:11p Davidd
// Fixed hanging problem when USB is disabled by the newly added "USB
// Support" setup question - EIP 25360
// 
// 31    2/05/09 12:28p Olegi
// 
// 30    2/04/09 5:30p Olegi
// Several modifications in FarCall86:
// - PIC SetMode is moved after raising TPL to highest level (cli)
// - Set Pmode interrupt mask to FF before setting Rmode mask. That avoids
// the problem where IVT is not yet set in real mode (before Func#0) and
// some HW interrupt is pending.
// 
// 29    11/13/08 10:00a Olegi
// Reverse thunk implementation started.
// 
// 28    11/07/08 4:04p Rameshraju
// Removed unused code.
// 
// 27    11/07/08 4:01p Rameshraju
// BugFix- Sometime system hangs on S4 resume.
// Fix Reason : If the Timer interrupt generates between CLI and Timer
// Interrupt mask code, Next STI instruction try to services the Timer
// interrupt.In this case before setting IVT system will hang
// EIP:17401
// 
// 26    6/12/08 8:14a Olegi
// Modified FarCall86 to execute USB keyboard change mode code for CSM16
// function #5 (EIP14051).
// 
// 25    8/27/07 12:44p Olegi
// 
// 23    6/28/07 4:14p Olegi
// 
// 22    6/25/07 12:27p Olegi
// 
// 21    6/18/07 5:54p Olegi
// 
// 20    5/29/07 6:17p Olegi
// Added UsbChangeEfiToLegacy call.
// 
// 19    4/27/07 5:14p Olegi
// CSM.CHM file preparation.
//
// 18    8/24/06 6:56p Felixp
//
// 17    8/24/06 6:55p Felixp
// x64 support (warnings/errors fixed)
//
// 16    8/24/06 3:11p Felixp
// Preliminary x64 support (work in progress)
//
// 15    7/28/06 4:45p Olegi
//
// 14    5/19/06 11:22p Felixp
// Device Path code updated to use NEXT_NODE/NODE_LENGTH/SET_NODE_LENGTH
// macros to remove direct access to the Length field
//
// 13    3/13/06 2:35p Felixp
//
// 12    10/13/05 6:19p Olegi
// Added condition to a previous change.
//
// 11    10/11/05 4:20p Srinin
// PS2 KBD reset function is called after CM16 function 2, 3 and 5 are
// called.
//
// 10    8/25/05 10:28a Olegi
// Previous changes undone - instead the vector base for the master 8259
// is changed from 0x68 to 0x58; with this there is no need to preserve
// and restore IVT.
//
// 8     3/04/05 1:47p Mandal
//
//**********************************************************************
//<AMI_FHDR_START>
//
// Name:    Thunk.c
//
// Description: 32/64 bit to 16 bit code thunk implementation
//
//<AMI_FHDR_END>
//**********************************************************************

#include <Protocol\DevicePath.h>
#include <Protocol\LegacyBios.h>
#include <Protocol\Legacy8259.h>
#include <Protocol\SimpleTextin.h>
#include <protocol\FirmwareVolume.h >
#include <Ffs.h>
#include "csm.h"
#include <AmiDxeLib.h>
#include "token.h"
#if defined(AMIUSB_SUPPORT)
#include <protocol\amiusbcontroller.h>
#endif
#include <Protocol\SimpleTextInEx.h>
#include <Protocol\AmiKeycode.h>


#pragma pack(1)
typedef struct {
    UINT16  Offset;
    UINT16  Segment;
} FAR_CALL_PTR_16;

typedef struct {
    UINT32  Stack;
    UINT32  StackSize;
} STACK;

typedef struct {
    FAR_CALL_PTR_16         FarCall;
    EFI_IA32_REGISTER_SET   Regs;
    STACK                   Stack;
    BOOLEAN                 isFarCall;  //if false, then INT86.
    UINT8                   BiosInt;
} THUNK_DATA;

typedef struct _ACPI_PNPID {
    UINT32  Signature   :16;
    UINT32  PnpID       :16;
} ACPI_PNPID;
#pragma pack()


#if defined(AMIUSB_SUPPORT)
EFI_USB_PROTOCOL *gUsbProtocol = NULL;
#endif
AMI_EFIKEYCODE_PROTOCOL *pKeyCodeProtocol=NULL;

EFI_SIMPLE_TEXT_INPUT_PROTOCOL  *gPS2KBDInterface = NULL;
EFI_GUID gCsmThunkGuid = {
    0xA08276EC,0xA0FE,0x4e06,0x86,0x70,0x38,0x53,0x36,0xC7,0xD0,0x93
};

EFI_LEGACY_8259_PROTOCOL *gLegacy8259;
extern BIOS_INFO        *CoreBiosInfo;

UINTN gThunkAsmAddr;
extern BOOLEAN gIsBootPrepared;
BOOLEAN gInsideThunk = FALSE;

EFI_STATUS GetPs2SimpleTextInProtocolInterface(
    BIOS_INFO               *This,
    EFI_SIMPLE_TEXT_INPUT_PROTOCOL  **PS2KBDInterface
);

//<AMI_PHDR_START>
//---------------------------------------------------------------------------
//
// Name:        SetKbcPresenceInMiscInfo 
//
// Description: Updates CSM16_NO_KBC_PRESENT_BIT of MiscInfoAddress accordingly
//              by checking if the KbcEmulation is Enabled or Disabled.
//
// Input:
//
// Output:
//  EFI_STATUS
//
// Referrals:
//
//---------------------------------------------------------------------------
//<AMI_PHDR_END>

VOID SetKbcPresenceInMiscInfo()
{
    EFI_TO_COMPATIBILITY16_INIT_TABLE   *Csm16InitTable;
    LEGACY16_TO_EFI_DATA_TABLE_STRUC    *Csm16Data;
    UINT8   KbcSupport,KbcCheck=0;
    EFI_STATUS  Status;

    //
    // Retrieving the Data at MiscInfoAddress
    //
    Csm16InitTable = &CoreBiosInfo->Thunk->Csm16InitTable;
    Csm16Data = (LEGACY16_TO_EFI_DATA_TABLE_STRUC*)(UINTN)Csm16InitTable->BiosLessThan1MB;

    KbcCheck = *(UINT8*)(UINTN)Csm16Data->MiscInfoAddress;

    //
    // Setting/Resetting the CSM16_NO_KBC_PRESENT_BIT according to the KbcEmulation
    //
    KbcSupport = IoRead8(0x64);
    if (KbcSupport != 0xff) {
        KbcCheck &= ~(CSM16_NO_KBC_PRESENT_BIT);
    }
    else {
        KbcCheck |= (CSM16_NO_KBC_PRESENT_BIT);
    }
    //
    // Checking if the Data at MiscInfoAddress is already updated
    //
    if((*(UINT8*)(UINTN)Csm16Data->MiscInfoAddress) != KbcCheck){
        //
        // Checking if F0000 region is writable
        //
        *(UINT8*)(UINTN)Csm16Data->MiscInfoAddress = KbcCheck;

        if((*(UINT8*)(UINTN)Csm16Data->MiscInfoAddress) == KbcCheck){
            return;
        }
        else{
            //
            // Unlocking the region 0xE0000 - 0xFFFFF
            //
            Status = CoreBiosInfo->iRegion->UnLock (CoreBiosInfo->iRegion,
                                                    0xE0000,
                                                    0x20000,
                                                    NULL);
            ASSERT_EFI_ERROR(Status);
        
            //
            // Updating the Data at MiscInfoAddress
            //
            *(UINT8*)(UINTN)Csm16Data->MiscInfoAddress = KbcCheck;
    
            //
            // Locking the region 0xE0000 - 0xFFFFF
            //
            CoreBiosInfo->iRegion->Lock (CoreBiosInfo->iRegion,
                                         0xE0000,
                                         0x20000,
                                         NULL);
        }
    }
}

//<AMI_PHDR_START>
//---------------------------------------------------------------------------
//
// Name:        Int86
//
// Description: Executes BIOS interrupt routine
//
// Input:
//  LegacyBios protocol instance pointer
//  BiosInt     Interrupt number
//  Regs        CPU register values to pass to the interrupt handler
//
// Output:
//  TRUE        Interrupt was not executed
//  FALSE       INT completed. Caller will see Regs for status
//
// Referrals:   EFI_IA32_REGISTER_SET
//
//---------------------------------------------------------------------------
//<AMI_PHDR_END>

BOOLEAN Int86(
    IN EFI_LEGACY_BIOS_PROTOCOL     *This,
    IN UINT8                        BiosInt,
    IN OUT EFI_IA32_REGISTER_SET    *Regs
)
{
    EFI_TPL     OldTpl;

    THUNK_DATA *ThunkData = (THUNK_DATA*)(gThunkAsmAddr+6);
    //
    // To avoid reentrance in Int86
    //
    if(gInsideThunk){
        return FALSE;
    }
    gInsideThunk = TRUE;
    ThunkData->isFarCall = FALSE;
    ThunkData->BiosInt = BiosInt;
    ThunkData->Stack.StackSize = 0; //This is required


    //Copy thunk registers.
    ThunkData->Regs = *Regs;

#if defined(AMIUSB_SUPPORT)
{
    EFI_STATUS  Status;

    if (gUsbProtocol == NULL) {
        Status = pBS->LocateProtocol(&gEfiUsbProtocolGuid, NULL, &gUsbProtocol);
        if (EFI_ERROR(Status)) {
            gUsbProtocol=NULL;      // To be used later, after returning from INT
        }
    }
    if (gUsbProtocol != NULL) {
        gUsbProtocol->UsbChangeEfiToLegacy(1);
    }
}
#endif

    OldTpl = pBS->RaiseTPL(TPL_HIGH_LEVEL);
    gLegacy8259->SetMode(gLegacy8259,Efi8259LegacyMode,NULL,NULL);

    SetKbcPresenceInMiscInfo();

    ((void(*)(UINTN))gThunkAsmAddr)(gThunkAsmAddr);

#if defined(AMIUSB_SUPPORT)
    if (gUsbProtocol) {
        gUsbProtocol->UsbChangeEfiToLegacy(0);
    }
#endif

    gLegacy8259->SetMode(gLegacy8259,Efi8259ProtectedMode,NULL,NULL);
    pBS->RestoreTPL(OldTpl);

    //Restore thunk registers.
    *Regs = ThunkData->Regs;
    gInsideThunk = FALSE;

    return FALSE;   // INT completed. Caller will see Regs for status.
}


//<AMI_PHDR_START>
//---------------------------------------------------------------------------
//
// Name:        FarCall86
//
// Description: Executes 16 bit code starting from a given address
//
// Input:
//  This        LegacyBiosProtocol instance pointer
//  Segment, Offset     Starting address of the 16 bit routine
//  Regs        CPU register values to pass to the routine
//  Stack       Stack pointer with the possible data to be passed to the routine
//  StackSize   Size of the stack passed to the routine
//
// Output:
//  TRUE        Call was not executed
//  FALSE       Call completed. Caller will see Regs for status
//
//---------------------------------------------------------------------------
//<AMI_PHDR_END>

BOOLEAN FarCall86(
  IN EFI_LEGACY_BIOS_PROTOCOL         *This,
  IN  UINT16                          Segment,
  IN  UINT16                          Offset,
  IN  EFI_IA32_REGISTER_SET           *Regs,
  IN  VOID                            *Stack,
  IN  UINTN                           StackSize
)
{
    EFI_TPL     OldTpl;
    UINT16      IrqMask, SaveIrqMask;
    UINT16      ProtectedIrqMask, ProtectedSaveIrqMask;
    THUNK_DATA *ThunkData = (THUNK_DATA*)(gThunkAsmAddr+6);
    UINT16      FuncNumber;
    BOOLEAN     IsCsm16Call =
                    Segment == CoreBiosInfo->Csm16EntrySeg &&
                    CoreBiosInfo->Csm16EntryOfs == Offset;
    BOOLEAN     IsCsm16DispatchOpRom = IsCsm16Call &&
                    Regs->X.AX == Compatibility16DispatchOprom;

    BOOLEAN     IsCsm16LegacyBoot = IsCsm16Call &&
                    Regs->X.AX == Compatibility16Boot;

    EFI_STATUS  Status = EFI_SUCCESS;
    EFI_KEY_TOGGLE_STATE    KeyToggleState=0;  
    // 
    // To avoid reentrance in FarCall86
    //
    if(gInsideThunk){
        return  FALSE;
    }

    gInsideThunk = TRUE;

    //
    // Change USB operation mode indicator from EFI to Legacy
    //
#if defined(AMIUSB_SUPPORT)
    if (IsCsm16LegacyBoot == FALSE) {
        if (gUsbProtocol == NULL) {
            Status = pBS->LocateProtocol(&gEfiUsbProtocolGuid, NULL, &gUsbProtocol);
            if (EFI_ERROR(Status)) {
                gUsbProtocol=NULL;      // To be used later, after FarCall execution
            }
        }
    }
    if (gUsbProtocol != NULL) {
        gUsbProtocol->UsbChangeEfiToLegacy(1);
    }
#endif

    ThunkData->isFarCall = TRUE;

    //Copy address for thunk.
    ThunkData->FarCall.Segment = Segment;
    ThunkData->FarCall.Offset = Offset;

    //Copy address for stack
    if (Stack)
    {
        ThunkData->Stack.Stack = (UINT32)Stack;
        ThunkData->Stack.StackSize = (UINT32)StackSize;
    } else ThunkData->Stack.StackSize = 0;

    //Copy thunk registers.
    ThunkData->Regs = *Regs;

    // Reset the PS/2 keyboard before legacy boot
    if (IsCsm16LegacyBoot == TRUE) {
        if (gPS2KBDInterface) gPS2KBDInterface->Reset(gPS2KBDInterface, FALSE);
    }

    FuncNumber = Regs->X.AX;

    if (IsCsm16Call) {
        if (FuncNumber != 05 && FuncNumber != 02 && FuncNumber != 03) {
            gLegacy8259->GetMask(gLegacy8259, &SaveIrqMask, NULL, NULL, NULL);      // Save current Mask

            IrqMask = -1;
            gLegacy8259->SetMask(gLegacy8259, &IrqMask, NULL, NULL, NULL);          // Set new Mask
        }
    }

    //
    // Mask all HW interrupts for real mode for CSM16 function #0 (InitializeYourself).
    // This is needed since IVT is not installed before executing function #0.
    //
    // TODO: Explore the possibility of IVT installation from CSM32; in this case the
    // code that is updating and using ProtectedIrqMask can be removed.
    //
    if (IsCsm16Call && FuncNumber == 00 ) {
        gLegacy8259->GetMask(gLegacy8259, NULL, NULL, &ProtectedSaveIrqMask, NULL);      // Save current Mask
        ProtectedIrqMask = -1;
        gLegacy8259->SetMask(gLegacy8259, NULL , NULL, &ProtectedIrqMask, NULL);          // Set new Mask
    }

    OldTpl = pBS->RaiseTPL(TPL_HIGH_LEVEL);
    //
    // The following call will change the PIC settings to real mode; this includes
    // unmasking all real mode interrupts. Note, that at this point HW interrupts
    // must be disabled. This is done by the previous RaiseTPL call.
    //
    gLegacy8259->SetMode(gLegacy8259,Efi8259LegacyMode,NULL,NULL);

    ((void(*)(UINTN))gThunkAsmAddr)(gThunkAsmAddr);

#if defined(AMIUSB_SUPPORT)
    if (gUsbProtocol) {
        gUsbProtocol->UsbChangeEfiToLegacy(0);
    }
#endif

    if (IsCsm16Call && FuncNumber == 00 ) {
        gLegacy8259->SetMask(gLegacy8259, NULL , NULL, &ProtectedSaveIrqMask, NULL);          // Set new Mask
    }

    gLegacy8259->SetMode(gLegacy8259,Efi8259ProtectedMode,NULL,NULL);
     
    //Restore thunk registers.
    *Regs = ThunkData->Regs;
    pBS->RestoreTPL(OldTpl);

    //
    // Change USB operation mode indicator back to EFI
    //

    if (!IsCsm16Call ||
        (IsCsm16Call &&
            (FuncNumber == 05 || FuncNumber == 02 || FuncNumber == 03))) {
//      Reset PS2 Mouse
        if (!gPS2KBDInterface) {
            GetPs2SimpleTextInProtocolInterface((BIOS_INFO *)This, &gPS2KBDInterface);
        }

        if (gPS2KBDInterface) gPS2KBDInterface->Reset(gPS2KBDInterface, FALSE);

    }
    else    gLegacy8259->SetMask(gLegacy8259, &SaveIrqMask, NULL, NULL, NULL);  // Restore mask

    if(IsCsm16DispatchOpRom) {
        if((pKeyCodeProtocol == NULL && IsCsm16LegacyBoot == FALSE)) {
            pBS->HandleProtocol(pST->ConsoleInHandle, &gAmiEfiKeycodeProtocolGuid, (void*)&pKeyCodeProtocol);
        }
        if(pKeyCodeProtocol != NULL) {
            UINT8   KeyState;
            KeyState = *(UINT8*)(UINTN)0x417;
            if(KeyState & 0x10) {
                KeyToggleState |= SCROLL_LOCK_ACTIVE;
            }
            if(KeyState & 0x20) {
                KeyToggleState |= NUM_LOCK_ACTIVE;
            }
            if(KeyState & 0x40) {
                KeyToggleState |= CAPS_LOCK_ACTIVE;
            }
            KeyToggleState |= TOGGLE_STATE_VALID;
            pKeyCodeProtocol->SetState((EFI_SIMPLE_TEXT_INPUT_EX_PROTOCOL*)pKeyCodeProtocol,&KeyToggleState);
        }
    }

    *(UINT8*)(UINTN)0x417 &= 0x70;  // Clear key modifiers status in BDA
   
    gInsideThunk = FALSE;

    return FALSE;   // CALL completed. Caller will see Regs for status.
}


//<AMI_PHDR_START>
//---------------------------------------------------------------------------
//
// Name:        LoadRealModeFile
//
// Description: Code that loads 16-bit thunk code at a particular address
//
// Input:
//  16-bit binary file GUID
//  Address to load the binary to
//
// Output:
//  Status of the load operation
//
//---------------------------------------------------------------------------
//<AMI_PHDR_END>

EFI_STATUS LoadRealModeFile(EFI_GUID *Guid, VOID *Address)
{
    EFI_FIRMWARE_VOLUME_PROTOCOL    *Fv;
    UINT32      Authentication;
    VOID        *BufferAddr=0;
    UINTN       BufferSize=0;
    EFI_STATUS  Status;
    UINTN       NumHandles;
    EFI_HANDLE  *HandleBuffer;
    UINTN       i;

    Status = pBS->LocateHandleBuffer(ByProtocol,&gEfiFirmwareVolumeProtocolGuid,NULL,&NumHandles,&HandleBuffer);
    if (EFI_ERROR(Status)) return Status;

    for (i = 0; i< NumHandles; ++i)
    {
        Status = pBS->HandleProtocol(HandleBuffer[i],&guidFV,&Fv);
        if (EFI_ERROR(Status)) continue;

        Status = Fv->ReadSection(Fv,
            Guid,
            EFI_SECTION_RAW,
            0,
            &BufferAddr,
            &BufferSize,
            &Authentication);

        if (Status == EFI_SUCCESS)
        {
            MemCpy(
                Address,
                (UINT8*)BufferAddr,
                BufferSize
            );
            pBS->FreePool(BufferAddr);
            break;
        }
    }

    pBS->FreePool(HandleBuffer);

    return Status;
}


//<AMI_PHDR_START>
//---------------------------------------------------------------------------
//
// Name:    InitializeThunk
//
// Description: 16-bit thunk initialization routine. It calls 16 bit code to
//              do the address fixups within 16-bit code.
//
// Input:   The instance of BIOS_INFO pointer
//
// Output:  Status of the initialization completion
//
//---------------------------------------------------------------------------
//<AMI_PHDR_END>

EFI_STATUS InitializeThunk(
    BIOS_INFO* CoreBiosInfo
)
{
    EFI_STATUS Status;
    EFI_PHYSICAL_ADDRESS    Thunkaddr = (EFI_PHYSICAL_ADDRESS)CoreBiosInfo->Thunk;
    UINT16 ThunkFixupsOffset;

    //Locate Legacy8259 Protocol
    gLegacy8259 = CoreBiosInfo->i8259;

    //Copy ThunkAsm to memory.
    Status = LoadRealModeFile(&gCsmThunkGuid, (VOID*)Thunkaddr);
    if (EFI_ERROR(Status)) return Status;

    gThunkAsmAddr = (UINT32)Thunkaddr;

    //Call fixups
    ThunkFixupsOffset = *(UINT16*)(gThunkAsmAddr+2);
    ((void(*)(UINTN))(gThunkAsmAddr+ThunkFixupsOffset))(gThunkAsmAddr);

    return Status;
}


//<AMI_PHDR_START>
//---------------------------------------------------------------------------
//
// Name:        GetPs2SimpleTextInProtocolInterface
//
// Description: This function returns the SimpleTextIn protocol interface
//
//---------------------------------------------------------------------------
//<AMI_PHDR_END>

EFI_STATUS GetPs2SimpleTextInProtocolInterface(
    BIOS_INFO   *This,
    EFI_SIMPLE_TEXT_INPUT_PROTOCOL  **PS2KBDInterface
)
{
    EFI_STATUS          Status;
    UINTN               i,cnt;
    ACPI_HID_DEVICE_PATH    *siodp;
    ACPI_PNPID          *pnpid;
    EFI_HANDLE          *hbuff = NULL;
    EFI_DEVICE_PATH_PROTOCOL        *dp;
    BOOLEAN             bIsConnected = FALSE;

    Status = pBS->LocateHandleBuffer(ByProtocol,&gEfiSimpleTextInProtocolGuid, NULL, &cnt, &hbuff);

    if (EFI_ERROR(Status)) return Status;

    for(i=0; i<cnt; i++){
        Status=pBS->HandleProtocol(hbuff[i],&gEfiDevicePathProtocolGuid,&dp);
        if(EFI_ERROR(Status)) continue;

        siodp=DPGetLastNode(dp);
        if(siodp->Header.Type!=ACPI_DEVICE_PATH
            || siodp->Header.SubType!=ACPI_DP
            || NODE_LENGTH(&siodp->Header) != ACPI_DEVICE_PATH_LENGTH) continue;

        pnpid=(ACPI_PNPID*)&siodp->HID;
        if (pnpid->PnpID == 0x0303) {
//          Status = pBS->OpenProtocol (hbuff[i], &gEfiSimpleTextInProtocolGuid, &PS2KBDInterface, This->hBios, NULL, EFI_OPEN_PROTOCOL_GET_PROTOCOL);
            Status = pBS->HandleProtocol(hbuff[i],&gEfiSimpleTextInProtocolGuid, PS2KBDInterface);
            break;
        }
        Status = EFI_NOT_FOUND;
    }
    pBS->FreePool(hbuff);
    return Status;
}
//**********************************************************************
//**********************************************************************
//**                                                                  **
//**        (C)Copyright 1985-2010, American Megatrends, Inc.         **
//**                                                                  **
//**                       All Rights Reserved.                       **
//**                                                                  **
//**           5555 Oakbrook Pkwy, Suite 200, Norcross, GA 30093      **
//**                                                                  **
//**                       Phone: (770)-246-8600                      **
//**                                                                  **
//**********************************************************************
//**********************************************************************
