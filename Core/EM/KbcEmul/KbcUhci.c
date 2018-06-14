//**********************************************************************
//**********************************************************************
//**                                                                  **
//**        (C)Copyright 1985-2013, American Megatrends, Inc.         **
//**                                                                  **
//**                       All Rights Reserved.                       **
//**                                                                  **
//**         5555 Oakbrook Pkwy, Suite 200, Norcross, GA 30093        **
//**                                                                  **
//**                       Phone: (770)-246-8600                      **
//**                                                                  **
//**********************************************************************
//**********************************************************************
// $Header: /Alaska/SOURCE/Modules/KbcEmulation/ALASKA/KBCEMUL/KbcUhci.c 11    5/13/13 2:51a Rameshr $
//
// $Revision: 11 $
//
// $Date: 5/13/13 2:51a $
//
//****************************************************************************
// Revision History
// ----------------
// $Log: /Alaska/SOURCE/Modules/KbcEmulation/ALASKA/KBCEMUL/KbcUhci.c $
// 
// 11    5/13/13 2:51a Rameshr
// [TAG]  		EIP119870
// [Category]  	Improvement
// [Description]  	Build error with KbcEmulation module if update USB
// module label 4.6.3_USB_08.10.26
// [Files]  		KbcEmul.Mak, KbcEmul.SDl, KbcUhci.c, KbcUhci.h, KbcOhci.c
// 
// 10    2/10/11 1:10a Rameshr
// [TAG]  		EIP53687
// [Category]  	Improvement
// [Description]  	AMI headers update for KbcEmulation Module 
// [Files]  		KbcEmul.mak,KbcEmul.dxs,KbcEmul.c,KbcEmul.h,KbcEmulLib.h,Kbc
// EmulLib.c,Kbc.h,KbcDevEmul.h,Kbccore.c,Legacykbc.c,Legacykbd.c,LegacyMo
// use.c,VirtualKbc.c,VirtualKbd.c,VirtualMouse.c,Ap4x.h,Ap4x.c,KbcUhci.c,
// KbcUhci.h,KbcEmulIrq.c, KbcOhci.c, Kbcohci.h
// 
// 9     7/12/10 7:38a Rameshr
// Ich10 Workaround added.
// 
// 8     7/12/10 6:58a Rameshr
// Workaround added when the Emulation enabled and Another USB controller
// is disabled in ICH10.
// EIP 39755
// 
// 7     7/08/10 2:07a Rameshr
// Function Output parameter changed for OHCI emulation support.
// 
// 6     2/02/10 4:28a Rameshr
// Before Regsiter the SMI call back for the USB PCI device, check the USB
// PCI device presence
// EIP 34601
// 
// 5     6/30/09 11:36a Rameshr
// Coding Standard and File header updated.
// 
// 4     6/01/09 10:03a Rameshr
// Added Emulation Support for RMH enable/Disable
// EIP 21131
// 
// 3     2/05/09 9:44a Rameshr
// Symptom : With Latest CSM Emulation doesn't work.
// Solution: Added Emulation enable code in outside SMM. This is called
// from Uhcd.c when ever USB mode changes to Legacy
// EIP:18730
// 
// 2     8/07/08 10:21a Rameshraju
// All UHCI controller registed for the SMI handler 
// 
// 1     12/14/07 10:26a Rameshraju
// Initial Check-in
//****************************************************************************

//<AMI_FHDR_START>
//****************************************************************************
// Name:        KbcUhci.c
//
// Description: Handles the SMI events for port 60/64
//
//****************************************************************************
//<AMI_FHDR_END>
#ifdef FRAMEWORK_AP4
#include "token.h"
#else
#include "tokens.h"
#endif
#include "KbcEmul.h"
#include "KbcUhci.h"
#include "KbcEmulLib.h"
#include "Kbc.h"

extern KBC* gVirtualKBC;

#if ICH10_WORKAROUND
EFI_STATUS  EnableAllUhciController();
EFI_STATUS  RestoreUhciControllerStatus();
#endif

//Carries the LEGKEY status information saved before enable/disable trapping from outside trap handler is
//performed; The saving of the status allows recovering legacy I/O accesss event in case when multiple
//sources are serviced at signle SMI# ( legacy I/O and USB keyboard interupt, for example)

static UINT16 SavedLegcyStatus = 0;

static BOOLEAN gInTrapHandler = FALSE;


UHCI_EMUL_DEVICE Uhci_Hc_Array[] = { UHCI_EMUL_PCI_DEVICES };
UINTN Uhci_Hc_Array_Size = sizeof(Uhci_Hc_Array) / sizeof(Uhci_Hc_Array[0]);

void DisableLegKeyRegs();
void trap64w();
void trap60w();
void trap64r();
void trap60r();

TRAPDISPATCH trap_dispatcher[] = {
    { UHCI_TRAPBY64W,  trap64w },
    { UHCI_TRAPBY64R,  trap64r },
    { UHCI_TRAPBY60W,  trap60w },
    { UHCI_TRAPBY60R,  trap60r },
};

#define trap_dispatcher_size  (sizeof(trap_dispatcher)/sizeof(trap_dispatcher[0]))

//status bits for SMI#, parenthesis is needed for ~ or other conversion
#define UHCI_TRAPBY_MASK        (UHCI_TRAPBY64W | UHCI_TRAPBY64R | UHCI_TRAPBY60W | UHCI_TRAPBY60R | UHCI_SMIBYENDPS)
//#define UHCI_TRAPBY_MASK      (UHCI_TRAPBY64W |  UHCI_TRAPBY60W | UHCI_TRAPBY60R | UHCI_SMIBYENDPS)

//enable bits for traps
#define UHCI_TRAPEN_MASK        (UHCI_64WEN | UHCI_60WEN  | UHCI_64REN | UHCI_60REN | UHCI_A20PASSEN )
//#define UHCI_TRAPEN_MASK      (UHCI_64WEN | UHCI_60WEN  |  UHCI_60REN | UHCI_A20PASSEN )

void Trap6064_Handler (
  IN  EFI_HANDLE                    DispatchHandle,
  IN  EFI_SMM_USB_DISPATCH_CONTEXT  * DispatchContext
  );

//<AMI_PHDR_START>
//----------------------------------------------------------------------------
// Procedure:   ValidateUhc
//
// Description: Validate the UHCI controller.
//
// Input:       Boolean
//
// Output:      Boolean
//
//----------------------------------------------------------------------------
//<AMI_PHDR_END>
BOOLEAN
ValidateUhc (
    UHCI_EMUL_DEVICE  *Uhc
)
{
    UINT32  Data32 = 0;

    if (ReadPCIConfig (Uhc->BusDevFunc, 0) == 0xFFFFFFFF) {
        return FALSE;
    }

    Data32 = ReadPCIConfig (Uhc->BusDevFunc, 8) >> 8;
    if (Data32 != (*((UINT32*)&Uhc->InterfaceType) & 0x00FFFFFF)) {
        return FALSE;
    }

	return TRUE;
}

//<AMI_PHDR_START>
//----------------------------------------------------------------------------
// Procedure:   Smm_Register
//
// Description: Enable the SMI for port 6064 access.
//
// Input:       None
//
// Output:      None
//
//----------------------------------------------------------------------------
//<AMI_PHDR_END>
void Smm_Register()
{
    EFI_SMM_USB_DISPATCH_CONTEXT    context;
    EFI_SMM_USB_DISPATCH_PROTOCOL*  pDispatch;
    EFI_HANDLE hDisp;
    EFI_STATUS Status;
    static FULL_USB_DEVICE_PATH hc_dp = USB1_1_DEVICE_PATH;
    UINTN UhciCount;

    //
    // Register the USB HW SMI handler
    //
    Status = gBS->LocateProtocol(&gEfiSmmUsbDispatchProtocolGuid, NULL, &pDispatch);
    ASSERT_EFI_ERROR(Status);
    //
    // SMI registration routines will install the handlers, set enable bit
    // and clear status in PM IO space.
    //
    for( UhciCount = 0; UhciCount < Uhci_Hc_Array_Size; ++UhciCount ){
        //
        //Validate the PCI device before regsiter the SMI callback.
        //
        if (!ValidateUhc(&Uhci_Hc_Array[UhciCount])) {
            continue;
        }
        hc_dp.pci.Device=(Uhci_Hc_Array[UhciCount].BusDevFunc >> 3);
        hc_dp.pci.Function=(Uhci_Hc_Array[UhciCount].BusDevFunc & 07);
        context.Type = UsbLegacy;
        context.Device = (EFI_DEVICE_PATH_PROTOCOL *)&hc_dp;
        Status = pDispatch->Register(pDispatch,Trap6064_Handler, &context, &hDisp);
    }

    SavedLegcyStatus = 0;
    //
    //The SMI source for the port6064 is disabled. it will be enabled when we are in legacy enviorment. EFI enviorment Emulation is
    //Disabled.
    //
    DisableLegKeyRegs();
}

//<AMI_PHDR_START>
//----------------------------------------------------------------------------
// Procedure:   WriteLegKeyReg
//
// Description: Write the Value in to all the UHCI controller Legacy Regsiters.
//
// Input:       UINT8 Value
//
// Output:      None
//
//----------------------------------------------------------------------------
//<AMI_PHDR_END>
void WriteLegKeyReg ( UINT16 Value)
{
    UINTN UhciCount;
    for( UhciCount = 0; UhciCount < Uhci_Hc_Array_Size; ++UhciCount ){
        WordWritePCIConfig( Uhci_Hc_Array[UhciCount].BusDevFunc, 
                        Uhci_Hc_Array[UhciCount].LegacyRegOffset, Value);
    }
}

//<AMI_PHDR_START>
//----------------------------------------------------------------------------
// Procedure:   ClearLegKeyStatusReg
//
// Description: Clear the Port6064 SMI Status Reg 
//
// Input:       UINT8 Value
//
// Output:      None
//
//----------------------------------------------------------------------------
//<AMI_PHDR_END>
void ClearLegKeyStatusReg ( UINT16 Value)
{
    UINTN UhciCount;

#if ICH10_WORKAROUND
        //
        // Enable all the UCHI controller 
        // In ICH10 chipset, we need to clear the Port 6064 SMI status in disabled controller 
        // also. Otherwise it's keep on generating SMI
        //
        EnableAllUhciController();
#endif
    
        for( UhciCount = 0; UhciCount < Uhci_Hc_Array_Size; ++UhciCount ){
            WordWritePCIConfig( Uhci_Hc_Array[UhciCount].BusDevFunc,  
                            Uhci_Hc_Array[UhciCount].LegacyRegOffset, Value);
        }


#if ICH10_WORKAROUND
        //
        // Restore the UCHI controller's in RCBA Reg
        //
        RestoreUhciControllerStatus();
#endif

}


//<AMI_PHDR_START>
//----------------------------------------------------------------------------
// Procedure:   DisableLegKeyRegs
//
// Description: Disable the port6064 SMI source based on the Trap enable mask.
//
// Input:       None
//
// Output:      None
//
//----------------------------------------------------------------------------
//<AMI_PHDR_END>
void DisableLegKeyRegs()
{
    UINT16  legkeyStatus;
    UINTN   UhciCount;

    for( UhciCount = 0; UhciCount < Uhci_Hc_Array_Size; ++UhciCount ){

        //
        // Skip for Invalid Pci Devices
        //
        if (!ValidateUhc(&Uhci_Hc_Array[UhciCount])) {
            continue;
        }

        //
        //Read the Legacy Keyboard and mouse control register
        //
        legkeyStatus =(UINT16) ReadPCIConfig(Uhci_Hc_Array[UhciCount].BusDevFunc , 
                            Uhci_Hc_Array[UhciCount].LegacyRegOffset );      // Read the status

        //
        //Clear the enable bits
        //

        WordWritePCIConfig( Uhci_Hc_Array[UhciCount].BusDevFunc , 
            Uhci_Hc_Array[UhciCount].LegacyRegOffset, legkeyStatus & ~UHCI_TRAPEN_MASK);

        //
        //Disable the trap
        //
        WordWritePCIConfig( Uhci_Hc_Array[UhciCount].BusDevFunc,  
            Uhci_Hc_Array[UhciCount].LegacyRegOffset, legkeyStatus & (~UHCI_TRAPEN_MASK));
    }
    return;
}

//<AMI_PHDR_START>
//----------------------------------------------------------------------------
// Procedure:   Trap6064_Handler
//
// Description: SMI handler to handle the 64write, 64read, 60 write and 60 read SMI.
//
// Input:       DispatchHandle  - EFI Handle
//              DispatchContext - Pointer to the EFI_SMM_SW_DISPATCH_CONTEXT

// Output:      None
//
//----------------------------------------------------------------------------
//<AMI_PHDR_END>
void Trap6064_Handler (
  IN  EFI_HANDLE                    DispatchHandle,
  IN  EFI_SMM_USB_DISPATCH_CONTEXT  * DispatchContext
  )
{
    UINT16 LegcyKeyStatus;
    UINT32 TrapFunCount;
    UINTN UhciCount;

    for( UhciCount = 0; UhciCount < Uhci_Hc_Array_Size; ++UhciCount ){

        if (!ValidateUhc(&Uhci_Hc_Array[UhciCount])) {
            continue;
        }

        //
        // Read UHCI_PCI_LEGKEY
        //
        LegcyKeyStatus = (UINT16) ReadPCIConfig( Uhci_Hc_Array[UhciCount].BusDevFunc , 
                                    Uhci_Hc_Array[UhciCount].LegacyRegOffset );
        SavedLegcyStatus |= LegcyKeyStatus;

        if(SavedLegcyStatus==0xFFFF) {
            SavedLegcyStatus=0;
            continue;
        }

        if( (SavedLegcyStatus & UHCI_TRAPBY_MASK) != 0 ) {
            break;
        }

        SavedLegcyStatus=0;
    }

    if(UhciCount >=Uhci_Hc_Array_Size) {
        return;
    }
    //
    // External application has chaned UHCI trap enable configuration, exit
    //
    if ((LegcyKeyStatus & UHCI_TRAPEN_MASK) != UHCI_TRAPEN_MASK)
        return;

    //
    // Set the variable that we are processing the Trap
     //
    gInTrapHandler = TRUE;

    //
    // Clear the status
    //
    ClearLegKeyStatusReg( LegcyKeyStatus | UHCI_TRAPBY_MASK);

    //
    // Disable Traps ( in responce to i/o handler can try to access a real KBC)
    //
    WriteLegKeyReg( (LegcyKeyStatus & ~UHCI_TRAPEN_MASK));

    //
    // Dispatch the interrupt depending on saved status
    //
    for( TrapFunCount = 0; TrapFunCount < trap_dispatcher_size; ++TrapFunCount ){
        if( (LegcyKeyStatus & trap_dispatcher[TrapFunCount].status_bit  ) != 0){
            (*trap_dispatcher[TrapFunCount].trap_function)();
        }
    }

    //
    // Clear the Status
    //
    ClearLegKeyStatusReg( LegcyKeyStatus | UHCI_TRAPBY_MASK);

    //
    // Enable Traps 
    //
    WriteLegKeyReg( LegcyKeyStatus | UHCI_TRAPEN_MASK);

    SavedLegcyStatus = 0;
    gInTrapHandler = FALSE;

    return;
}

//<AMI_PHDR_START>
//----------------------------------------------------------------------------
// Procedure:  Uhci_HasTrapStatus
//
// Description: Check if trap status is set in UHCI HC.
//
// Input:       None
//
// Output:      None
//
//----------------------------------------------------------------------------
//<AMI_PHDR_END>

BOOLEAN Uhci_HasTrapStatus()
{
    UINT16 LegcyKeyStatus = 0;
    UINTN UhciCount;

    for( UhciCount = 0; UhciCount < Uhci_Hc_Array_Size; ++UhciCount ){
        if (!ValidateUhc(&Uhci_Hc_Array[UhciCount])) {
            continue;
        }

        LegcyKeyStatus |= (UINT16) ReadPCIConfig(Uhci_Hc_Array[UhciCount].BusDevFunc,  
                                    Uhci_Hc_Array[UhciCount].LegacyRegOffset );
    }
    return ((LegcyKeyStatus & UHCI_TRAPBY_MASK) != 0 );
}

//<AMI_PHDR_START>
//----------------------------------------------------------------------------
// Procedure:   Uhci_TrapEnable
//
// Description: Enable/Disable traping in UHCI HC.
//
// Input:       Boolean
//
// Output:      None
//
//----------------------------------------------------------------------------
//<AMI_PHDR_END>

BOOLEAN    Uhci_TrapEnable(BOOLEAN TrapEnable)
{
    UINT16    LegcyKeyStatus;
    UINTN       UhciCount;

    if(gInTrapHandler)
        return FALSE;

    for( UhciCount = 0; UhciCount < Uhci_Hc_Array_Size; ++UhciCount ){
        if (!ValidateUhc(&Uhci_Hc_Array[UhciCount])) {
            continue;
        }

        LegcyKeyStatus =(UINT16) ReadPCIConfig( Uhci_Hc_Array[UhciCount].BusDevFunc , 
                                        Uhci_Hc_Array[UhciCount].LegacyRegOffset );
        
        //
        //Record first time that trapping is disabled. Record only trap status bits handled by Trap handler
        //
        if( (LegcyKeyStatus & UHCI_TRAPEN_MASK)== UHCI_TRAPEN_MASK &&
            ( LegcyKeyStatus & UHCI_TRAPBY_MASK) != 0 ){
            //If legacy I/O caused SMI# and this is first time we are in uhci_trapEnable
            //then trapping in LEGKEY reg must have been enabled and one trap status is set.
            //Any port 60/64 operation within SMI# must be wrapped into
            //enable/ disable&clear status. So subsequent trapEnable will not produce any
            //trap statuses
            SavedLegcyStatus |= LegcyKeyStatus;
        }
        if(TrapEnable){
        
            //
            //clear status(es) that might be asserted by our handlers
            //
            ClearLegKeyStatusReg( LegcyKeyStatus | UHCI_TRAPBY_MASK);
            //
            // Enable Traps
            //
            WriteLegKeyReg( LegcyKeyStatus | UHCI_TRAPEN_MASK);
        } else {
        
            //
            //clear status(es) that might be asserted by our handlers
            //
            ClearLegKeyStatusReg( LegcyKeyStatus | UHCI_TRAPBY_MASK);
            //
            // Disable Traps
            //
            WriteLegKeyReg( (LegcyKeyStatus & ~UHCI_TRAPEN_MASK) );
        }
    }
    return TRUE;
}

//<AMI_PHDR_START>
//----------------------------------------------------------------------------
// Procedure:   NonSmmValidateUhc
//
// Description: Validate the UHCI controller.
//
// Input:       Boolean
//
// Output:      Boolean
//
//----------------------------------------------------------------------------
//<AMI_PHDR_END>
BOOLEAN
NonSmmValidateUhc (
    UHCI_EMUL_DEVICE  *Uhc
)
{
    UINT32  Data32 = 0;

    if (NonSmmReadPCIConfig (Uhc->BusDevFunc, 0) == 0xFFFFFFFF) {
        return FALSE;
    }

    Data32 = NonSmmReadPCIConfig (Uhc->BusDevFunc, 8) >> 8;
    if (Data32 != (*((UINT32*)&Uhc->InterfaceType) & 0x00FFFFFF)) {
        return FALSE;
    }

	return TRUE;
}

//<AMI_PHDR_START>
//----------------------------------------------------------------------------
// Procedure:   NonSmmWriteLegKeyReg
//
// Description: Write the Value in to all the UHCI controller Legacy Regsiters.
//
// Input:       UINT8 Value
//
// Output:      None
//
//----------------------------------------------------------------------------
//<AMI_PHDR_END>
void NonSmmWriteLegKeyReg ( UINT16 Value)
{
    UINTN UhciCount;

    for( UhciCount = 0; UhciCount < Uhci_Hc_Array_Size; ++UhciCount ){
        if (!NonSmmValidateUhc(&Uhci_Hc_Array[UhciCount])) {
            continue;
        }
        NonSmmWordWritePCIConfig( Uhci_Hc_Array[UhciCount].BusDevFunc, 
                        Uhci_Hc_Array[UhciCount].LegacyRegOffset, Value);
    }
    return;
}

//<AMI_PHDR_START>
//----------------------------------------------------------------------------
// Procedure:   NonSmmClearLegKeyStatusReg
//
// Description: Clear the Port6064 SMI Status 
//
// Input:       UINT8 Value
//
// Output:      None
//
//----------------------------------------------------------------------------
//<AMI_PHDR_END>
void NonSmmClearLegKeyStatusReg ( UINT16 Value)
{

    UINTN UhciCount;

#if ICH10_WORKAROUND
    //
    // Enable all the UCHI controller 
    // In ICH10 chipset, we need to clear the Port 6064 SMI status in disabled controller 
    // also. Otherwise it's keep on generating SMI
    //
    EnableAllUhciController();
#endif

    for( UhciCount = 0; UhciCount < Uhci_Hc_Array_Size; ++UhciCount ){
        if (!NonSmmValidateUhc(&Uhci_Hc_Array[UhciCount])) {
             continue;
        }
        NonSmmWordWritePCIConfig( Uhci_Hc_Array[UhciCount].BusDevFunc,  
                        Uhci_Hc_Array[UhciCount].LegacyRegOffset, Value);
    }

#if ICH10_WORKAROUND
    //
    // Restore the UCHI controller's in RCBA Reg
    //
    RestoreUhciControllerStatus();
#endif

    return;
}

//<AMI_PHDR_START>
//----------------------------------------------------------------------------
// Procedure:   NonSmmUhci_TrapEnable
//
// Description: Enable/Disable traping in UHCI HC.
//
// Input:       Boolean
//
// Output:      None
//
//----------------------------------------------------------------------------
//<AMI_PHDR_END>

BOOLEAN    NonSmmUhci_TrapEnable(BOOLEAN TrapEnable)
{

    UINT16    LegcyKeyStatus;
    EFI_TPL     OldTpl;
    UINT16      UhciCount;

    for( UhciCount = 0; UhciCount < Uhci_Hc_Array_Size; ++UhciCount ){
        if (!NonSmmValidateUhc(&Uhci_Hc_Array[UhciCount])) {
             continue;
        }

        LegcyKeyStatus =(UINT16) NonSmmReadPCIConfig( Uhci_Hc_Array[UhciCount].BusDevFunc , 
                                        Uhci_Hc_Array[UhciCount].LegacyRegOffset );
        //
        //Record first time that trapping is disabled. Record only trap status bits handled by Trap handler
        //
        if( (LegcyKeyStatus & UHCI_TRAPEN_MASK)== UHCI_TRAPEN_MASK &&
            ( LegcyKeyStatus & UHCI_TRAPBY_MASK) != 0 ){
            //If legacy I/O caused SMI# and this is first time we are in uhci_trapEnable
            //then trapping in LEGKEY reg must have been enabled and one trap status is set.
            //Any port 60/64 operation within SMI# must be wrapped into
            //enable/ disable&clear status. So subsequent trapEnable will not produce any
            //trap statuses
            SavedLegcyStatus |= LegcyKeyStatus;
        }

        OldTpl = pBS->RaiseTPL(TPL_HIGH_LEVEL);

        if(TrapEnable){
            //
            // Clear the status
            //
            NonSmmClearLegKeyStatusReg(LegcyKeyStatus | UHCI_TRAPBY_MASK);
            //
            // Enable Traps 
            //
            NonSmmWriteLegKeyReg( LegcyKeyStatus | UHCI_TRAPEN_MASK);
        } else {
            //
            // Clear the status
            //
            NonSmmClearLegKeyStatusReg(LegcyKeyStatus | UHCI_TRAPBY_MASK);

            //
            // Disable the Trap
            //
            NonSmmWriteLegKeyReg( (LegcyKeyStatus & ~UHCI_TRAPEN_MASK) );
        }
        pBS->RestoreTPL(OldTpl);
    }

    return TRUE;
}

//**********************************************************************
//**********************************************************************
//**                                                                  **
//**        (C)Copyright 1985-2013, American Megatrends, Inc.         **
//**                                                                  **
//**                       All Rights Reserved.                       **
//**                                                                  **
//**         5555 Oakbrook Pkwy, Suite 200, Norcross, GA 30093        **
//**                                                                  **
//**                       Phone: (770)-246-8600                      **
//**                                                                  **
//**********************************************************************
//**********************************************************************
