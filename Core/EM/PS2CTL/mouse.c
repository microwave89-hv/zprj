//**********************************************************************
//**********************************************************************
//**                                                                  **
//**        (C)Copyright 1985-2009, American Megatrends, Inc.         **
//**                                                                  **
//**                       All Rights Reserved.                       **
//**                                                                  **
//**         5555 Oakbrook Pkwy, Suite 200, Norcross, GA 30093        **
//**                                                                  **
//**                       Phone: (770)-246-8600                      **
//**                                                                  **
//**********************************************************************
//**********************************************************************

//**********************************************************************
// $Header: /Alaska/SOURCE/Core/CORE_DXE/PS2CTL/mouse.c 24    11/07/12 12:26a Srikantakumarp $
//
// $Revision: 24 $
//
// $Date: 11/07/12 12:26a $
//**********************************************************************
// Revision History
// ----------------
// $Log: /Alaska/SOURCE/Core/CORE_DXE/PS2CTL/mouse.c $
// 
// 24    11/07/12 12:26a Srikantakumarp
// [TAG]  		EIP99411
// [Category]  	Improvement
// [Description]  	Add port validation check in the PS2Ctrl module before
// starting the driver.
// [Files]  		kbc.c, kbc.h, mouse.c, ps2main.c, CORE_DXE.sdl, Tokens.c
// 
// 23    10/18/12 9:49a Deepthins
// [TAG]  		EIP95111
// [Category]  	Bug Fix
// [Severity]  	Normal
// [Symptom]  	PS2 mouse is not working in setup.
// [RootCause]  	In stream mode data reporting is disabled by default. The
// mouse will not actually issue any movement data packets until it
// receives the "Enable Data Reporting" (0xF4) command. So even when the
// DETECT_PS2_KEYBOARD and DETECT_PS2_MOUSE token is disabled we need to
// send command 0xf4 to Enable Data Reporting.
// [Solution]  	In MouseReset function, Set sampleRate ,Resolution and
// Enable streaming.
// [Files]  		mouse.c and ps2kbd.c
// 
// 22    5/02/12 2:28a Deepthins
// [TAG]  		EIP63116
// [Category]  	New Feature
// [Description]  	PS/2 Keyboard/Mouse IRQ mode generic support
// [Files]  		Ps2kbd.c, Mouse.c, kbc.h, kbc.c
// 
// 21    2/01/12 2:00a Deepthins
// [TAG]  		EIP63116
// [Category]  	New Feature
// [Description]  	PS/2 Keyboard/Mouse IRQ mode generic support
// [Files]  		Token.c, Ps2main.c, Ps2kbd.c, Mouse.c, kbc.h, kbc.c,
// CORE_DXE.sdl
// 
// 20    9/19/11 9:38a Lavanyap
// [TAG]  		EIP66198
// [Category]  	Improvement
// [Description]  	Added Mouse Wheel support in PS2 and USB drivers. 
// [Files]  		usbdef.h, usbms.c, efiusbms.c, ps2mouse.h, mouse.c
// 
// 19    7/29/11 1:07a Lavanyap
// [TAG]  		EIP63310
// [Category]  	Bug Fix
// [Severity]  	Normal
// [Symptom]  	MouseGetState() does not differentiate between driver busy
// and no state change between GetState calls.
// [RootCause]  	MouseGetState() return status codes does not follow UEFI
// specification.
// [Solution]  	MouseGetState() return status codes has been updated as
// per UEFI specification.
// [Files]  		mouse.c
// 
// 18    4/27/11 4:37a Lavanyap
// [TAG] - EIP49407
// [Category] - IMPROVEMENT
// [Description] - Move the Ps2 driver SDL tokens from Core Source to Core
// Bin,So that we don't need to add Core source for changing the Ps2
// driver SDL tokens.
// [Files] - Ps2Ctl.sdl, ps2kbd.c, ps2main.c, ps2ctl.h, kbc.c, mouse.c,
// hotkey.c, CORE_DXE.sdl, Tokens.c
// 
// 17    12/10/10 5:31a Rameshr
// [TAG] - EIP 47011
// [Category]- BUG FIX
// [Severity]- Minor
// [Symptom] - DTM IO Tests fail due to presence of PS/2 devices that are
// not ready - no PS/2 devices attached during test.
// [RootCause]- PS2 device _STA method returns that, device is present .
// [Solution] - Updated the SIO device status based on the device
// presence.
// [Files] - Kbc.c , Kbc.h, Mouse.c
// 
// 16    8/23/10 4:25a Rameshr
// Bug Fix : EIP 40838
// Symptoms: KBC.C build failed in DetectPS2Keyboard() if
// DETECT_PS2_KEYBOARD=0 & PS2MOUSE_SUPPORT=0
// Files Modified: Efismplpp.c, Kbc.c, Kbc.h, Mouse.c PS2ctl.cif,
// Ps2ctl.sdl, Ps2Kbd.c, Ps2Mouse.h
// Details: 
// 1) Added Detect_PS2_Mouse sdl token and modified the code.
// 2) INSTALL_KEYBOARD_MOUSE_ALWAYS sdl token added.
//    1 - Install the Keyboard- SimpleTextIn, Mouse - AbsPointer Always, 
//    0 - Install the Keyboard- SimpleTextIn, Mouse - AbsPointer only if
// the device is present at the time of detection.
//    This is for Ps2Keyboard Hot plug support in EFI 
// 3) Code clean up in mouse.c EfiSmplpp.c ,ps2mouse.h
// 4) Unused file automaton.h removed.
// 
// 15    7/01/09 12:32p Olegi
// Source is corrected according to the coding standard: function headers,
// copyright messages are updated.
// 
// 14    10/08/08 4:55p Olegi
// Change in GetMouseData that will reset the mouse in case the recieved
// packet is wrong. The failure was observed in TSE.
// 
// 13    4/22/08 4:31p Felixp
// Additional progress codes added
// 
// 12    4/09/08 10:19a Olegi
// Changed the key attributes (modifiers and shift state) reporting.
// 
// 11    4/16/07 6:28p Pats
// Modified to conform with coding standards. No code changes.
// 
// 10    3/01/07 3:43p Pats
// Modified for faster boot if keyboard detection disabled.
// 
// 9     5/05/06 5:23p Ambikas
// 
// 8     1/09/06 11:38a Felixp
// 
// 6     12/22/05 10:25a Srinin
// Cleaned up the code. KBD disable inside GetMousedata removed.
// 
// 5     10/11/05 4:15p Srinin
// Mouse is initialized for Streaming mode but kept disabled. Re-entry
// problem fixed.
// 
// 4     7/18/05 3:37p Felixp
// 
// 3     3/04/05 1:36p Mandal
// 
//**********************************************************************
//<AMI_FHDR_START>
//
// Name:    Mouse.c
//
// Description: This is the PS/2 mouse EFI driver source file.
//
//<AMI_FHDR_END>
//**********************************************************************

//<AMI_FHDR_START>
//----------------------------------------------------------------------
//
// Name: mouse.c
//
// Description: PS/2 mouse I/O support fuctions
//
//----------------------------------------------------------------------
//<AMI_FHDR_END>

//----------------------------------------------------------------------

#include <Efi.h>
#include <AmiLib.h>
#include "ps2ctl.h"
#include "kbc.h"
#include "ps2mouse.h"

STATEMACHINEPROC DrivePS2MouseMachine;
BOOLEAN Ps2MouseDetected = FALSE;
UINT8   MouseData[5] = {0,};
BOOLEAN InsideGetMouseData = FALSE; 
BOOLEAN MouseResetRequired = FALSE;
UINT8   ByteCount = NON_WHEEL_REPORT_FORMAT;
extern  BOOLEAN InsideKbdReadKey;
extern  BOOLEAN InsideOnWaitingOnKey;
extern KEYBOARD gKbd;
typedef struct _STATE;
MOUSE gMouse = {0,};
EFI_CPU_ARCH_PROTOCOL       *gCpuArch;
EFI_LEGACY_8259_PROTOCOL    *mLegacy8259;
UINT8                       gMouseIrqInstall = FALSE;
extern  UINT8               gKeyboardIrqInstall;
extern                      BOOLEAN KBDEnableState;  
UINT8                       gCurrentMouseIndex = NULL;
UINT8                       gGetMouseStateStart=FALSE;
VOID                        GetMouseDataFromIrq(VOID);
UINT8                       gMouseCommandActive=FALSE;
BOOLEAN                     InsideMouseReset;
extern  BOOLEAN             MsIrqSupport; 
extern  BOOLEAN             MouseEnableState;
extern  BOOLEAN             DetectPs2MouseValue;
extern  BOOLEAN             InstallKeyboardMouseAlways;
extern  BOOLEAN             KbdIrqSupport;
extern  BOOLEAN             InsideKbdReset;
extern  UINT32              IbFreeMaxTimeoutValue;

//<AMI_PHDR_START>
//----------------------------------------------------------------------
//
// Procedure:       ObFullRead
//
// Description:     Waits for Output Buffer Full and then reads the data port
//
// Parameters:      None
//
// Output:          UINT8 KBC Data port data
//
//----------------------------------------------------------------------
//<AMI_PHDR_END>

UINT8 ObFullReadM()
{
    for (;;) {
        if ((IoRead8(KBC_CMDSTS_PORT) & (KBC_OBF|KBC_AUX_OBF)) == (KBC_OBF|KBC_AUX_OBF)) {
            return IoRead8(KBC_DATA_PORT);
        }
    }
}


//<AMI_PHDR_START>
//----------------------------------------------------------------------
//
// Procedure:       ObFullReadMTimeout
//
// Description:     This routine checks for the data availbility in output
//                  buffer for a short period of time, if data is available
//                  within this time, it reads and returns the data from 
//                  output buffer.
//
// Paremeters:      UINT8* data - Pointer to the byte to be updated
//                  UINT32 msec - Milliseconds timeout
//
// Output:          BOOLEAN - Returns FALSE if data is successfully updated  
//                  (no timeout), data is updated
//                  Returns TRUE if time-out
//
//----------------------------------------------------------------------
//<AMI_PHDR_END>

BOOLEAN ObFullReadMTimeout (
    UINT8*  data,
    UINT32  msec )
{

    UINT8       bData;
    UINT32      loopcount = msec << 1;

    for (; loopcount; loopcount--) {

        bData = IoRead8(KBC_CMDSTS_PORT);

        if ((bData & (KBC_OBF|KBC_AUX_OBF)) == (KBC_OBF|KBC_AUX_OBF)) {

            *data = IoRead8(KBC_DATA_PORT);
            if (bData & 0x40) {
                *data = IoRead8(KBC_DATA_PORT);
                TRACEKBD((-1, "Status Reg M : %x, %x\n", bData, *data));
                return TRUE;
            }
            else return FALSE;  // No timeout

        }

        if ((bData & (KBC_OBF|KBC_AUX_OBF)) == (KBC_OBF)){
            TRACEKBD((-1, "KB OBF inside Mouse"));
            return TRUE;
        }

        gSysTable->BootServices->Stall(500);                // 0.5 msec

    }

    return TRUE;    // Timeout
}


//<AMI_PHDR_START>
//----------------------------------------------------------------------
//
// Procedure:       ReadDeviceM
//
// Description:     Sends the given command to KBD, reads and returns the
//                  acknowledgement byte returned from KBD.
//
// Parameters:      UINT8 bCmd - Command to send to KBC
//                  UINT8 *Data - Pointer to data buffer
//                  UINT8 Response - Response expected
//
// Output:          EFI_SUCCESS - Data == Response
//                  EFI_DEVICE_ERROR - Data != Response
//
//----------------------------------------------------------------------
//<AMI_PHDR_END>

EFI_STATUS ReadDeviceM (
    UINT8   bCmd, 
    UINT8   *Data, 
    UINT8   Response )
{
    EFI_STATUS  Status;
    Status = IbFreeTimeout(IbFreeMaxTimeoutValue);
    if (EFI_ERROR(Status)) {
        return Status;
    }
    IoWrite8(KBC_CMDSTS_PORT, 0xD4);
    IbFree();
    WriteKeyboardData(bCmd);

    if (ObFullReadMTimeout(Data, 1000)) { 
        return EFI_DEVICE_ERROR;
    }
    if (*Data == Response) { 
        return EFI_SUCCESS;
    }

    return EFI_DEVICE_ERROR; 
}


                          
//<AMI_PHDR_START>
//----------------------------------------------------------------------------
// Procedure: MouseInterruptHandler
//
// Description: An interrupt handler for PS2 mouse
//
//
// Input:     InterruptType  Interrupt type
//            SystemContext  System context
//
// Output:    EFI_SUCCESS
//
//----------------------------------------------------------------------------
//<AMI_PHDR_END>
VOID MouseInterruptHandler(
    IN EFI_EXCEPTION_TYPE   InterruptType,
    IN EFI_SYSTEM_CONTEXT   SystemContext
)
{
    EFI_TPL  OldTpl=NULL;
    KEYBOARD *Kbd = &gKbd;

    //
    // Disable interrupt to prevent interrupt chaining
    //
    gCpuArch->DisableInterrupt(gCpuArch);

    //
    // Post Code verifies the Mouse IRQ generation by sending command 0xD4(Write mouse device)
    // and data. For the data if the control comes to Mouse IRQ handler, and IRQ method is enabled
    // and active. Otherwise it will disable the Mouse IRQ 

    if (gMouseCommandActive){
        gMouseIrqInstall = TRUE;
        //
        // Throw out the Dummy data that we sent to test the Mouse IRQ generation
        //
        IoRead8(KBC_DATA_PORT);
        
    } else {
        
        //
        // Handle the Mouse Data
        //
        GetMouseDataFromIrq();
    }

    EnableAuxDevice();
    
    //
    // Send End Of Interrupt command twice as PIC is connected 
    // in cascade mode, once for master and once for corresponding
    // slave 
    //
    mLegacy8259->EndOfInterrupt(mLegacy8259, SYSTEM_MOUSE_IRQ);
    mLegacy8259->EndOfInterrupt(mLegacy8259, SLAVE_IRQ);
    gCpuArch->EnableInterrupt(gCpuArch);
}

//<AMI_PHDR_START>
//----------------------------------------------------------------------
//
// Procedure:       InitMOUSE
//
// Description:     Initializes mouse driver
//
// Parameters:      MOUSE** ppMouse - Pointer to mouse structure
//
// Output:          EFI_SUCCESS - Mouse initialized
//                  EFI_DEVICE_ERROR - Mouse not detected
//                  EFI_OUT_OF_RESOURCES - Not enough memory for buffers
//
//----------------------------------------------------------------------
//<AMI_PHDR_END>


EFI_STATUS InitMOUSE ( 
    MOUSE**     ppMouse )
{
    MOUSE* pmouse;
    EFI_STATUS  Status;                               
    UINT32      MouseVector = NULL;
    UINT32      loopcount = 1000;

    pmouse = *ppMouse = &gMouse;

    MemSet( &pmouse->state, sizeof(pmouse->state), 0 );
    pmouse->saved_flags=0;

    if (EFI_ERROR(DetectPS2mouse(pmouse))) {
        //
        // Ps2 Mouse not Present.
        //
        return EFI_DEVICE_ERROR;
    }

    //
    // Ps2 Mouse Present. Install Simple Pointer protocol.
    //
    (pmouse->iSmplPtr).Mode =   MallocZ(sizeof (EFI_SIMPLE_POINTER_MODE));

    if(!((pmouse->iSmplPtr).Mode)) { 
        return EFI_OUT_OF_RESOURCES;
    }

    //
    // Check for mouse IRQ support. 
    //
    if(MsIrqSupport){
        if (!gMouseIrqInstall){
            if(mLegacy8259 == NULL){
                Status = pBS->LocateProtocol(&gEfiLegacy8259ProtocolGuid, NULL, &mLegacy8259);
                if (EFI_ERROR(Status)) {
					return Status;
				}
            }

            //
            // Find the CPU Arch Protocol  
            // 
            if(gCpuArch == NULL){
                Status = pBS->LocateProtocol(&gEfiCpuArchProtocolGuid, NULL, &gCpuArch);
                if (EFI_ERROR(Status)) {
					return Status;
				}
            }
    	    //
            // Get Mouse vector
            //
            Status = mLegacy8259->GetVector(mLegacy8259, SYSTEM_MOUSE_IRQ, (UINT8 *) & MouseVector);
            if (EFI_ERROR(Status))	{
				return Status;
			}
            //
            // Register interrupt handler for mouse
            //
            Status = gCpuArch->RegisterInterruptHandler(gCpuArch, MouseVector, MouseInterruptHandler);
            if (EFI_ERROR(Status)) {
				return Status;
			}
            //
            // To set the interrupt mode operation in legacy mode
            //

            mLegacy8259->SetMode(mLegacy8259,Efi8259LegacyMode,NULL,NULL);
            //
            // Enable Mouse interrupt
            //
            Status = mLegacy8259->EnableIrq(mLegacy8259, SYSTEM_MOUSE_IRQ, FALSE);
            if (EFI_ERROR(Status)) {
				return Status;
			}

            Status = mLegacy8259->EnableIrq(mLegacy8259, 0x02, FALSE);
            if (EFI_ERROR(Status)) {
				return Status;
			}
            //
            // To set the interrupt mode operation in protected mode
            //
            mLegacy8259->SetMode(mLegacy8259,Efi8259ProtectedMode,NULL,NULL);

            //
            // Enable PS2 mouse interrupt
            //
            Status = mLegacy8259->EnableIrq(mLegacy8259, SYSTEM_MOUSE_IRQ, FALSE);
            if (EFI_ERROR(Status)) {
				return Status;
			}

            //
            // Enable Master PIC interrupt IRQ2
            //
            Status = mLegacy8259->EnableIrq(mLegacy8259, 0x02, FALSE);
            if (EFI_ERROR(Status)) {
				return Status;
			}
            //
            // Enable INT2 bit in command register. 
            //
            Write8042CommandByte(0x67);

            // Is Mouse IRQ active?
            gMouseCommandActive = TRUE;
            Status = IbFreeTimeout(IbFreeMaxTimeoutValue);
            if (EFI_ERROR(Status)) {
                return Status;
            }
            IoWrite8(KBC_CMDSTS_PORT, 0xD4);
            IbFree();
            //
            // Write mouse data
            //
            WriteKeyboardData(0xf4);

            for (; loopcount; loopcount--) {
    	        if (gMouseIrqInstall) break;
                gSysTable->BootServices->Stall(500);        // 0.5 msec
            }
            gMouseCommandActive = FALSE;

            //
            // If Mouse irq is not installed then disable interrupt
            //
            if (!gMouseIrqInstall){
                //
                // a dummy read after writing to mouse
                //
                IoRead8(0x60);
                Write8042CommandByte(0x65);
                mLegacy8259->DisableIrq(mLegacy8259, SYSTEM_MOUSE_IRQ);
            
            }
        }
    }

    (pmouse->iSmplPtr).Mode->ResolutionX = 4;
    (pmouse->iSmplPtr).Mode->ResolutionY = 4;
    (pmouse->iSmplPtr).Mode->ResolutionZ = 4;
    (pmouse->iSmplPtr).Mode->RightButton = TRUE;
    (pmouse->iSmplPtr).Mode->LeftButton = TRUE;

    //
    // Initialize pointer interface functions
    //
    (pmouse->iSmplPtr).Reset = (EFI_SIMPLE_POINTER_RESET)MouseReset;
    (pmouse->iSmplPtr).GetState= (EFI_SIMPLE_POINTER_GET_STATE)MouseGetState;
    
    return EFI_SUCCESS;
}


//<AMI_PHDR_START>
//----------------------------------------------------------------------
//
// Procedure:   DetectPs2Mouse
//
// Description: 
// Implements Reset operation of SimplePointer protocol.
// As part of initialization process, the firmware/device will make a quick 
// but reasonable attempt to verify that the device is functioning. If the 
// ExtendedVerification flag is TRUE the firmware may take an extended amount 
// of time to verify the device is operating on reset. Otherwise the reset 
// operation is to occur as quickly as possible.
//
// Parameters:  None
//
// Output:        
//      Returns EFI_SUCCESS if the device was reset, othewise returns 
//      EFI_DEVICE_ERROR - device is not functioning correctly and could 
//      not be reset.
//
// Modified:    MouseEnableState
//      
//----------------------------------------------------------------------
//<AMI_PHDR_END>

EFI_STATUS  DetectPs2Mouse()
{

    UINT8 bData = 0, b1, b2, loop;
    EFI_STATUS Status;

    if ( DetectPs2MouseValue ) {


        PROGRESS_CODE(DXE_MOUSE_RESET);

        for (loop = 3; loop; loop--) {

            if ((IoRead8(KBC_CMDSTS_PORT) & KBC_OBF)) {
                TRACEKBD((-1,"KBD"));
                //
                // Consume Data and discard it
                //
                KBCGetData();
            }

            TRACEKBD((-1,"Reseting mouse...\n"));

            Status = ReadDeviceM(0xFF, &bData, 0xFA);
            TRACEKBD((-1,"%x, %x ", bData, Status));
            //
            // ACK received
            //
            if (Status == EFI_SUCCESS) {    

                if (ObFullReadMTimeout(&b1, 1000)) { 
                    continue;
                }
                if (ObFullReadMTimeout(&b2, 1000)) {
                    continue;
                }

                TRACEKBD((-1,"Data %x; %x\n",b1,b2));   

                if ( b1 == 0xAA && b2 == 0x00) {
                    TRACEKBD((-1,"Reset Mouse Ok\n"));

                    //
                    // Enable wheel report format
                    //
                    if (EFI_ERROR(ReadDeviceM(0xF3, &bData, 0xFA))) {
                        continue;       // Set Sample Rate
                    }
                    if (EFI_ERROR(ReadDeviceM(0xC8, &bData, 0xFA))) {
                        continue;       // 200 samples/sec
                    }
                    if (EFI_ERROR(ReadDeviceM(0xF3, &bData, 0xFA))) {
                        continue;       // Set Sample Rate
                    }
                    if (EFI_ERROR(ReadDeviceM(0x64, &bData, 0xFA))) {
                        continue;       // 100 samples/sec
                    }
                    if (EFI_ERROR(ReadDeviceM(0xF3, &bData, 0xFA))) {
                        continue;       // Set Sample Rate
                    }
                    if (EFI_ERROR(ReadDeviceM(0x50, &bData, 0xFA))) {
                        continue;       // 80 samples/sec
                    }

                    ReadDeviceM(0xF2, &bData, 0xFA); // Read Mouse ID
                    ObFullReadMTimeout(&bData, 1000);

                    // If scroll wheel is supported Mouse Response = 3 
                    // else Mouse Response = 0
                    if (bData == 3) {
                        ByteCount = WHEEL_REPORT_FORMAT;
                    }

                    if (EFI_ERROR(ReadDeviceM(0xF3, &bData, 0xFA))) {
                        continue;       // Set Sample Rate
                    }    
                    if (EFI_ERROR(ReadDeviceM(0x64, &bData, 0xFA))) { 
                        continue;       // 20 samples/sec
                    }
                    if (EFI_ERROR(ReadDeviceM(0xE8, &bData, 0xFA))) {
                        continue;       // Set resolution
                    }
                    if (EFI_ERROR(ReadDeviceM(0x2, &bData, 0xFA))) { 
                        continue;        // 4 Count/mm
                    }

                    //
                    // Enable streaming
                    //
                    ReadDeviceM(0xF4, &bData, 0xFA);                                

                    MouseEnableState = TRUE;
                    DisableAuxDevice();
                    Ps2MouseDetected = TRUE;

                    return EFI_SUCCESS;

                }
            }
        }

        //
        // Ps2 Mouse Not Present. Return with Error.
        //
        return EFI_DEVICE_ERROR;
    } else {
        //
        // By default Ps2 mouse is enabled and Present
        //
        MouseEnableState = TRUE;
        Ps2MouseDetected = TRUE;
        return EFI_SUCCESS;
    }
}

//<AMI_PHDR_START>
//----------------------------------------------------------------------
//
// Procedure:   MouseReset
//
// Description: 
//  Implements Reset operation of SimplePointer protocol.
//  As part of initialization process, the firmware/device will make a quick 
//  but reasonable attempt to verify that the device is functioning. If the 
//  ExtendedVerification flag is TRUE the firmware may take an extended amount 
//  of time to verify the device is operating on reset. Otherwise the reset 
//  operation is to occur as quickly as possible.
//
// Parameters:  
//  MOUSE *self     - pointer to the mouse structure
//  BOOLEAN extended - Indicates that the driver may perform a more exhaustive
//                  verification operation of the device during reset.
//
// Output:        
//  Returns EFI_SUCCESS if the device was reset, othewise returns 
//  EFI_DEVICE_ERROR - device is not functioning correctly and could 
//  not be reset.
//
//----------------------------------------------------------------------
//<AMI_PHDR_END>

EFI_STATUS  MouseReset(
    MOUSE   *self,
    BOOLEAN extended)
{
    UINT8       bData = 0;
    UINT8       b1;
    UINT8       b2;
    UINT8       loop;
    EFI_STATUS  Status;


    //
    // If ExtendedVerification Flag is true then reset the mouse, set 
    // sampleRate and Resolution and Enable streaming.
    //
    if(extended) {

        InsideMouseReset = TRUE;
        Write8042CommandByte(0x74);

        //
        // Check for keyboard IRQ support
        //
        if(KbdIrqSupport ) {
            //
            // Now Disable the interrupt
            //
            mLegacy8259->DisableIrq(mLegacy8259, SYSTEM_KEYBOARD_IRQ);
        }

        //
        // Check for mouse IRQ support
        //
        if(MsIrqSupport) {
            //
            // Now Disable the interrupt
            //
            mLegacy8259->DisableIrq(mLegacy8259, SLAVE_IRQ);
            mLegacy8259->DisableIrq(mLegacy8259, SYSTEM_MOUSE_IRQ);
        }

        for (loop = 3; loop; loop--) {

            if ((IoRead8(KBC_CMDSTS_PORT) & KBC_OBF)) {
                TRACEKBD((-1,"KBD"));
                //
                // Consume Data and discard it
                //
                KBCGetData();
            }

            TRACEKBD((-1,"Reseting mouse...\n"));

            Status = ReadDeviceM(0xFF, &bData, 0xFA);
            TRACEKBD((-1,"%x, %x ", bData, Status));
            //
            // ACK received
            //
            if (Status == EFI_SUCCESS) {    

                ByteCount = NON_WHEEL_REPORT_FORMAT;

                if (ObFullReadMTimeout(&b1, 1000)) { 
                    continue;
                }
                if (ObFullReadMTimeout(&b2, 1000)) {
                    continue;
                }

                TRACEKBD((-1,"Data %x; %x\n",b1,b2));   

                if ( b1 == 0xAA && b2 == 0x00) {
                    TRACEKBD((-1,"Reset Mouse Ok\n"));

                    //
                    // Enable wheel report format
                    //
                    if (EFI_ERROR(ReadDeviceM(0xF3, &bData, 0xFA))) {
                        continue;       // Set Sample Rate
                    }
                    if (EFI_ERROR(ReadDeviceM(0xC8, &bData, 0xFA))) {
                        continue;       // 200 samples/sec
                    }
                    if (EFI_ERROR(ReadDeviceM(0xF3, &bData, 0xFA))) {
                        continue;       // Set Sample Rate
                    }
                    if (EFI_ERROR(ReadDeviceM(0x64, &bData, 0xFA))) {
                        continue;       // 100 samples/sec
                    }
                    if (EFI_ERROR(ReadDeviceM(0xF3, &bData, 0xFA))) {
                        continue;       // Set Sample Rate
                    }
                    if (EFI_ERROR(ReadDeviceM(0x50, &bData, 0xFA))) {
                        continue;       // 80 samples/sec
                    }

                    ReadDeviceM(0xF2, &bData, 0xFA); // Read Mouse ID
                    ObFullReadMTimeout(&bData, 1000);

                    // If scroll wheel is supported Mouse Response = 3 
                    // else Mouse Response = 0
                    if (bData == 3) {
                        ByteCount = WHEEL_REPORT_FORMAT;
                    }

                    if (EFI_ERROR(ReadDeviceM(0xF3, &bData, 0xFA))) {
                        continue;       // Set Sample Rate
                    }    
                    if (EFI_ERROR(ReadDeviceM(0x64, &bData, 0xFA))) { 
                        continue;       // 20 samples/sec
                    }
                    if (EFI_ERROR(ReadDeviceM(0xE8, &bData, 0xFA))) {
                        continue;       // Set resolution
                    }
                    if (EFI_ERROR(ReadDeviceM(0x2, &bData, 0xFA))) { 
                        continue;        // 4 Count/mm
                    }


                    //
                    // Enable streaming
                    //
                    ReadDeviceM(0xF4, &bData, 0xFA);                                
                    break;
               }
            }
        }

        //
        // Check for keyboard IRQ support
        //
        if(KbdIrqSupport ) {
            //
            // Now Disable the interrupt
            //
            mLegacy8259->EnableIrq(mLegacy8259, SYSTEM_KEYBOARD_IRQ, FALSE);
        }
        if(MsIrqSupport) {
            mLegacy8259->EnableIrq(mLegacy8259, SYSTEM_MOUSE_IRQ, FALSE);
            mLegacy8259->EnableIrq(mLegacy8259, SLAVE_IRQ, FALSE);
        }

        Write8042CommandByte(0x47);
        InsideMouseReset = FALSE;
    }

    return EFI_SUCCESS;
}


//<AMI_PHDR_START>
//----------------------------------------------------------------------
//
// Procedure:       MouseGetState
//
// Description:     Retrieves the current state of a pointer device.
//
// Parameters:  
//  MOUSE *self - Pointer to the mouse structure
// EFI_SIMPLE_POINTER_STATE *state - Pointer to state machine buffer
//
// Output:          EFI_SUCCESS - Mouse data ready
//                  EFI_NOT_READY - Mouse data not ready
//
// Modified:        MouseData
//      
// Referrals:       MouseData
//
// Notes: 
//  The function retrieves the current state of a pointer device. This includes
//  information on the buttons associated with the pointer device and the 
//  distance that each of the axes associated with the pointer device has been
//  moved. If the state of the pointer device has not changed since the last 
//  call to MouseGetState(), then EFI_NOT_READY is returned. If the state of 
//  the pointer device has changed since the last call to MouseGetState(), then
//  the state information is placed in State, and EFI_SUCCESS is returned. If a
//  device error occurs while attempting to retrieve the state information,
//  then EFI_DEVICE_ERROR is returned.
//----------------------------------------------------------------------
//<AMI_PHDR_END>


EFI_STATUS  MouseGetState(
    MOUSE *self,
    EFI_SIMPLE_POINTER_STATE *state)
{

    StdMouseDataPacket* packet = (StdMouseDataPacket*)MouseData;
    EFI_STATUS Status;

    //  Check if Mouse Data ready
    if (!MouseData[ByteCount]) {
        Status = GetMouseData();
        if (EFI_ERROR(Status)) {
            return Status;
        }
    }

    if (MouseData[ByteCount]) {

        MouseData[ByteCount] = 0;

        if( packet->flags & (MOUSE_X_OVF|MOUSE_Y_OVF) ){
            return EFI_DEVICE_ERROR;
        } else {
            state->RelativeMovementX = (packet->flags & MOUSE_X_NEG)? (signed char)packet->x:packet->x;
            state->RelativeMovementY = -(int)((packet->flags & MOUSE_Y_NEG)? (signed char)packet->y:packet->y);
            state->LeftButton = (packet->flags & BUTTON_LEFT)?TRUE:FALSE;
            state->RightButton = (packet->flags & BUTTON_RIGHT)?TRUE:FALSE;
			
            if (ByteCount == WHEEL_REPORT_FORMAT) {
                state->RelativeMovementZ = ((signed char)packet->z);
            } else {
            	state->RelativeMovementZ = 0;			
			}
            return EFI_SUCCESS;
        }
    }

    return EFI_NOT_READY;

}


//<AMI_PHDR_START>
//----------------------------------------------------------------------
//
// Procedure:       DetectPS2mouse
//
// Description:     Detects the presence of mouse in KBC port.
//
// Parameters:      MOUSE* self - Pointer to the mouse structure    
//
// Output:          EFI_SUCCESS if mouse is detected
//                  EFI_NOT_FOUND if mouse is not detected
//
//----------------------------------------------------------------------
//<AMI_PHDR_END>

EFI_STATUS  DetectPS2mouse (
    MOUSE*  self )
{
    if ( InstallKeyboardMouseAlways ) {
        return EFI_SUCCESS;
    } else {
        return Ps2MouseDetected ? EFI_SUCCESS : EFI_NOT_FOUND;
    }
}


//<AMI_PHDR_START>
//----------------------------------------------------------------------
//
// Procedure:       OnWaitingOnMouse
//
// Description:     Callback for the WaitForInput event;
//                  checks whether the mouse state has changed and if so - 
//                  signals the event.
//
// Parameters:      EFI_EVENT event - Event to signal
//                  MOUSE *self - Pointer to the mouse structure    
//
// Output:          None
//
//----------------------------------------------------------------------
//<AMI_PHDR_END>

VOID OnWaitingOnMouse (
    EFI_EVENT   event, 
    MOUSE       *self )
{
    //  Check if Mouse Data ready
    if (!MouseData[ByteCount]) {
        GetMouseData();
    }

    if (MouseData[ByteCount]) gSysTable->BootServices->SignalEvent(event);

}

//<AMI_PHDR_START>
//----------------------------------------------------------------------
//
// Procedure:       GetMouseDataFromIrq
//
// Description:     Enables Mouse and returns data if available 
//
// Parameters:      None
//
// Output:          EFI_SUCCESS - Mouse data returned
//                  EFI_NO_RESPONSE - No response from mouse
//
// Modified:        MouseData, InsideGetMouseData
//      
// Referrals:       MouseData, InsideGetMouseData, MouseResetRequired,
//                  InsideKbdReadKey, InsideOnWaitingOnKey, gKbd
//
//----------------------------------------------------------------------
//<AMI_PHDR_END>
VOID GetMouseDataFromIrq(VOID)
{
    UINT8    Port64flag = IoRead8(KBC_CMDSTS_PORT);
    
   

    if ((Port64flag & (KBC_OBF|KBC_AUX_OBF)) == (KBC_OBF|KBC_AUX_OBF)) {
    	MouseData[gCurrentMouseIndex] = KBCGetData();
        if (gCurrentMouseIndex ==(ByteCount-1)){ 
            DisableAuxDevice();
            gCurrentMouseIndex = 0;
            MouseData[ByteCount] = 1;
            return;
        }
        gCurrentMouseIndex++;
    }

    return;
}


//<AMI_PHDR_START>
//----------------------------------------------------------------------
//
// Procedure:       GetMouseData
//
// Description:     Enables Mouse and returns data if available 
//
// Parameters:      None
//
// Output:          EFI_SUCCESS - Mouse data returned
//                  EFI_NO_RESPONSE - No response from mouse
//
// Modified:        MouseData, InsideGetMouseData
//      
// Referrals:       MouseData, InsideGetMouseData, MouseResetRequired,
//                  InsideKbdReadKey, InsideOnWaitingOnKey, gKbd
//
//----------------------------------------------------------------------
//<AMI_PHDR_END>
EFI_STATUS GetMouseData() 
{
    
    UINT8       Index;
    BOOLEAN     MouseDataRead;
    KEYBOARD    *kbd = &gKbd;
    UINT8       KbdData[20], KbdDataIndex=0, Data8;
    UINTN       Delay, DelayPeriod = 100;
    BOOLEAN     MouseDataValid = FALSE;

    //
    // If mouse irq is supported and installed then return with success
    //
    if(MsIrqSupport){                          
        if (gMouseIrqInstall){
            return EFI_SUCCESS;
        }
    }

    //  Return if we are in the middle of KBD get key
    if (InsideGetMouseData || InsideKbdReadKey || InsideOnWaitingOnKey || InsideKbdReset || InsideMouseReset) {
        return EFI_DEVICE_ERROR;
    }

    if (MouseData[ByteCount] == 1) return EFI_SUCCESS;

    //  Try to complete the LED sequence
    for (Index = 0; (Index < 40) && kbd->LEDCommandState; Index++ ) {
        //
        // if keyboard irq is supported but not installed yet then call
        // Ps2DataDispatcher to check whether data is available on port or not
        //
        if(KbdIrqSupport)
            if (!gKeyboardIrqInstall)
                PS2DataDispatcher(NULL);
        pBS->Stall(500);        
    }

    //  LED sequence is still on, restart it
    if (kbd->LEDCommandState) {
        if(KbdIrqSupport)          
            if (!gKeyboardIrqInstall){
                TRACEKBD((-1,"BLS%x ", kbd->LEDCommandState));
                ProcessKBDResponse(kbd, 0xfe);
            }
    }

    InsideGetMouseData = TRUE;

    if ((IoRead8(KBC_CMDSTS_PORT) & (KBC_OBF|KBC_AUX_OBF)) == KBC_OBF) {
        KbdData[KbdDataIndex] = KBCGetData();
        KbdDataIndex++;
    }

    EnableAuxDevice();
    if (MouseResetRequired) {
        DisableKeyboard();
        if ((IoRead8(KBC_CMDSTS_PORT) & (KBC_OBF|KBC_AUX_OBF)) == KBC_OBF) {
            KbdData[KbdDataIndex] = KBCGetData();
            KbdDataIndex++;
        }
        ReadDeviceM(0xF4, &Index, 0xFA);
        MouseResetRequired = FALSE;
    }

    MouseData[ByteCount] = 0;

    DelayPeriod = 200;                  // Delay for the first byte
    for (Index = 0; Index < ByteCount; Index++) {

        MouseDataRead = FALSE;

        for (Delay = 0; Delay < DelayPeriod; Delay++) {

            Data8 = IoRead8(KBC_CMDSTS_PORT);

            if ((Data8 & (KBC_OBF|KBC_AUX_OBF)) == KBC_OBF) {           
                KbdData[KbdDataIndex] = KBCGetData();
                KbdDataIndex++;
            }

            if ((Data8 & (KBC_OBF|KBC_AUX_OBF)) == (KBC_OBF|KBC_AUX_OBF)) {         
                MouseData[Index] = KBCGetData();
                MouseDataValid = TRUE;
                MouseDataRead = TRUE;
                if (Index == (ByteCount-1)) DisableAuxDevice();
                break;              
            }

            pBS->Stall(100);

        }

        DelayPeriod = 100;          // Delay for the Second & Third byte

        if (Index == (ByteCount-1) && MouseDataRead) {
                MouseData[ByteCount] = 1;
        } else if (Index == (ByteCount-1) && MouseDataValid) {
            MouseResetRequired=TRUE;
        }

        if (MouseDataRead) continue;
        else break;

    }
    
    //  Reset mouse counters if the mouse sequence is not correct
    if (MouseData[ByteCount] == 1 && !(MouseData[0] & 8)) {

        for (; Index; Index--) {
            TRACEKBD((-1,"%X ", MouseData[Index]));
        }
        TRACEKBD((-1,"\n"));

        DisableKeyboard();
        if ((IoRead8(KBC_CMDSTS_PORT) & (KBC_OBF|KBC_AUX_OBF)) == KBC_OBF) {
            KbdData[KbdDataIndex] = KBCGetData();
            KbdDataIndex++;
        }
        ReadDeviceM(0xF4, &Index, 0xFA);
    }

    EnableKeyboard();                   
    DisableAuxDevice();

    for (Index =0 ; KbdDataIndex; KbdDataIndex--, Index++) {
        ProcessKBDData(kbd, KbdData[Index]);        
    }

    InsideGetMouseData = FALSE;

    return EFI_SUCCESS;

}

//**********************************************************************
//**********************************************************************
//**                                                                  **
//**        (C)Copyright 1985-2009, American Megatrends, Inc.         **
//**                                                                  **
//**                       All Rights Reserved.                       **
//**                                                                  **
//**         5555 Oakbrook Pkwy, Suite 200, Norcross, GA 30093        **
//**                                                                  **
//**                       Phone: (770)-246-8600                      **
//**                                                                  **
//**********************************************************************
//**********************************************************************
