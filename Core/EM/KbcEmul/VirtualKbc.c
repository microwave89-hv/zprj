//**********************************************************************
//**********************************************************************
//**                                                                  **
//**        (C)Copyright 1985-2011, American Megatrends, Inc.         **
//**                                                                  **
//**                       All Rights Reserved.                       **
//**                                                                  **
//**         5555 Oakbrook Pkwy, Suite 200, Norcross, GA 30093        **
//**                                                                  **
//**                       Phone: (770)-246-8600                      **
//**                                                                  **
//**********************************************************************
//**********************************************************************
// $Header: /Alaska/SOURCE/Modules/KbcEmulation/ALASKA/KBCEMUL/VirtualKbc.c 14    2/11/13 12:45a Rameshr $
//
// $Revision: 14 $
//
// $Date: 2/11/13 12:45a $
//
//****************************************************************************
// Revision History
// ----------------
// $Log: /Alaska/SOURCE/Modules/KbcEmulation/ALASKA/KBCEMUL/VirtualKbc.c $
// 
// 14    2/11/13 12:45a Rameshr
// [TAG]  		EIP114926
// [Category]  	Bug Fix
// [Severity]  	Minor
// [Symptom]  	Write CCB command doesn't enable the keyboard interface
// [RootCause]  	Data bytes are not decoded properly.
// [Solution]  	Data bytes are decoded properly and device interface and
// IRQ state values are set properly.
// [Files]  		VirtualKbc.c
// 
// 13    9/30/11 12:45a Rameshr
// [TAG]  		EIP71408
// [Category]  	Improvement
// [Description]  	Remove the customer name reference from the
// KbcEmulation module.
// [Files]  		KbcDevEmul.h,VirtualKbc.c
// 
// 12    2/10/11 1:06a Rameshr
// [TAG]  		EIP53687
// [Category]  	Improvement
// [Description]  	AMI headers update for KbcEmulation Module 
// [Files]  		KbcEmul.mak,KbcEmul.dxs,KbcEmul.c,KbcEmul.h,KbcEmulLib.h,Kbc
// EmulLib.c,Kbc.h,KbcDevEmul.h,Kbccore.c,Legacykbc.c,Legacykbd.c,LegacyMo
// use.c,VirtualKbc.c,VirtualKbd.c,VirtualMouse.c,Ap4x.h,Ap4x.c,KbcUhci.c,
// KbcUhci.h,KbcEmulIrq.c, KbcOhci.c, Kbcohci.h
// 
// 11    1/19/11 4:45a Rameshr
// [TAG] - EIP 52171
// [Category]- BUG FIX
// [Severity]- Minor
// [Symptom] - System gives Assert when Keyboard Reset Command issued. 
// [RootCause]- KBC Emulation Module SMI handler is using EFI Runtime
// services for Reset() Instead of SMM RunTime Services
// [Solution] - Smm Runtime Services used to reset the system 
// [Files] - VirtualKbc.c
// 
// 10    7/08/10 2:01a Rameshr
// Ohci Emulation support Added.
// EIP 39712
// 
// 9     2/10/10 7:03p Davidd
// Corrected the USB KB stopped working in DOS after "net init" utility is
// run - EIP 33687.
// 
// 8     2/03/10 1:16a Rameshr
// Install Netware6.5 SP8 Fail.
// EIP 28411
// Single byte and two Byte command is identified properly and handled.
// 
// 7     12/23/09 1:31a Rameshr
// Symptom: KbcEmulation can't install FreeBSD
// Solution: Implemented command 0xAA (Controller self-test) and 0xAB
// (Keyboard interface test)
// EIP: 26451
// 
// 6     6/30/09 11:31a Rameshr
// Coding Standard and File header updated.
// 
// 5     10/30/08 10:45a Rameshraju
// Keyboard & Mouse enable/disable command handled
// 
// 4     10/24/08 11:56a Rameshraju
// IRQ1 or IRQ12 generated again if there is pending data.
// 
// 3     5/01/08 10:40a Rameshraju
// Keyboard command D2 support added
// 
// 2     12/27/07 4:54p Rameshraju
// KBC reset command added
// 
// 1     12/14/07 10:26a Rameshraju
// Initial Check-in
//****************************************************************************

//<AMI_FHDR_START>
//**********************************************************************
// Name:        VirtualKbc.c
//
// Description: Handles the Virtual KBC(Without KBC system) function
//
//**********************************************************************
//<AMI_FHDR_END>

#include "KbcEmul.h"
#include "KbcDevEmul.h"
#include "Kbc.h"

void    vkbc_write_command( KBC* kbc, UINT8 cmd );
UINT8   vkbc_read_status( KBC* kbc );
void    vkbc_write_data( KBC* kbc, UINT8 cmd );
UINT8   vkbc_read_data( KBC* kbc );
BOOLEAN virtkbc_sendout(KBC* kbc, PS2DEV_TYPE devtype,BOOLEAN ovrd, UINT8 data);
void    initKBC(KBC* kbc, PS2SINK* kbd, PS2SINK* mouse );

//
//Depend on the KBC command generate IRQ12
//
BOOLEAN     MouseIrq= TRUE;

//
//Depend on the KBC command generate IRQ1
//
BOOLEAN     KeyboardIrq= TRUE;

//
//To hold the keyboard outport Status.
//
UINT8       OutPortStatus= 0xDF;

//
//To hold the number of Mouse byte already send
//
UINT8       PacketSize=00;


extern  EFI_EMUL6064KBDINPUT_PROTOCOL   *gKbdProtocol;

#if IRQ_EMUL_SUPPORT
extern  GenerateIRQ12(VIRTKBC*);
extern  GenerateIRQ1(VIRTKBC*);
#endif

#if OHCI_EMUL_SUPPORT
UINT8   GetHceStatus(void);
#endif

//<AMI_PHDR_START>
//----------------------------------------------------------------------------
// Procedure:   vkbc_write_command
//
// Description: Handle write to command port of virtual KBC
//
// Input:       kbc     - pointer to the KBC structure
//              cmd     - keyboard controller command
//
// Output:      None
//
//----------------------------------------------------------------------------
//<AMI_PHDR_END>
void    vkbc_write_command( KBC* kbc, UINT8 cmd )
{
    VIRTKBC*    vkbc = (VIRTKBC*)kbc;
    VIRTMOUSE*  Mouse = (VIRTMOUSE*)kbc->mouse_dev;
    VIRTKBD*    Kbd = (VIRTKBD*)kbc->kbd_dev;
    EFI_RUNTIME_SERVICES 	*SmmRuntimeVar;
    EFI_GUID SmmRsTableGuid = EFI_SMM_RUNTIME_SERVICES_TABLE_GUID;
    UINT8 Index;
    
    SmmRuntimeVar = NULL;    
 
    //
    //Save the KBC command
    //
    vkbc->kbc_command_ = cmd;
    vkbc->st_ |= KBC_STATUS_A2;
    vkbc->TwoByteCmd = FALSE;

    //
    //Process the KBC command
    //
    switch( vkbc->kbc_command_ ){
        case KBCCMD_READ_CCB:
                //move ccb into the ouput buffer
                virtkbc_sendout(kbc,PS2DEV_KBD,TRUE,vkbc->ccb_);
                break;
        case KBCCMD_KBDDSBL:
                vkbc->ccb_|=CCB_KEYBOARD_DISABLED;
                Kbd->Enabled= FALSE;    
                break;
        case KBCCMD_KBDENBL:
                vkbc->ccb_&=(~CCB_KEYBOARD_DISABLED);
                Kbd->Enabled= TRUE;    
                break;
        case KBCCMD_AUXDSBL:
                vkbc->ccb_|=CCB_MOUSE_DISABLED;
                Mouse->Enabled = FALSE;
                break;
        case KBCCMD_AUXENBL:
                vkbc->ccb_&=(~CCB_MOUSE_DISABLED);
                Mouse->Enabled = TRUE;
                break;
        case KBCCMD_ReadOutPort:
                virtkbc_sendout(kbc,PS2DEV_KBD,TRUE,OutPortStatus);
                break;
        //
        //Selft Test- Returns 0x55 if okay 
        //
        case KBCCMD_SelfTest:
                virtkbc_sendout(kbc,PS2DEV_KBD,TRUE,KBCCMD_RES_SelfTestOk);
                break;
        //
        //Returns 0x00 if okay, 0x01 if Clock line stuck low, 0x02 if clock line stuck high, 
        //0x03 if data line stuck low, and 0x04 if data line stuck high
        //
        case KBCCMD_CheckKbd:
                virtkbc_sendout(kbc,PS2DEV_KBD,TRUE,KBCCMD_RES_KBInterfaceOk);
                break;
        //
        //Reset the System for KBC command 0xFE
        //
        case KBCCMD_ResetSystem:
                
                for (Index = 0; Index < gSmst->NumberOfTableEntries; ++Index) {
                    if (guidcmp(&gSmst->SmmConfigurationTable[Index].VendorGuid, \
                                        &SmmRsTableGuid) == 0) {
                        break;
                    }
                }
                if (Index != gSmst->NumberOfTableEntries) {
                     SmmRuntimeVar =(EFI_RUNTIME_SERVICES *) gSmst->SmmConfigurationTable[Index].VendorTable;
                     
                }
                if(SmmRuntimeVar){
                   SmmRuntimeVar->ResetSystem(EfiResetCold, EFI_SUCCESS, 0, NULL);
                }
                break;
        //
        //Below are 2 byte commands. Next byte expected in Port 60.
        //    
        case KBCCMD_WriteAuxDev:
        case KBCCMD_WRITE_CCB:
        case KBCCMD_WriteAuxBuffer:
        case KBCCMD_WriteKbdBuffer:
        case KBCCMD_WriteOutPort:
                vkbc->TwoByteCmd = TRUE;
                break;

        default:
                break;
    }
}

//<AMI_PHDR_START>
//----------------------------------------------------------------------------
// Procedure:   vkbc_read_status
//
// Description: Handle read from status port of virtual KBC
//
// Input:       kbc     - pointer to the KBC structure
//
//
// Output:      Status      - keyboard controller Status
//
//----------------------------------------------------------------------------
//<AMI_PHDR_END>
UINT8   vkbc_read_status( KBC* kbc )
{
    VIRTKBC* vkbc = (VIRTKBC*)kbc;

    //
    //If we send 1 byte of mouse already , then try to send the remaining 2 bytes of data first and process the keyboard data.
    //

    if(PacketSize >0 && PacketSize < MOUSE_PACKET_SIZE) {
        //
        //Check the OBF, If it's empty , check Mouse queue , if it's has the data push the data to KBC.
        //
        if(!(vkbc->st_ & KBC_STATUS_OBF)) {
            (*kbc->mouse_dev->onQueueFree)(kbc->mouse_dev);
        }

        //
        //Check the OBF, If it's empty , check KBD queue , if it's has the data push the data to KBC.
        //
        if(!(vkbc->st_ & KBC_STATUS_OBF)) {
            (*kbc->kbd_dev->onQueueFree)(kbc->kbd_dev);
        }
    } else {
        //
        //Try to process the keyboard data first.
        //

        PacketSize=0;
        //
        //Check the OBF, If it's empty , check KBD queue , if it's has the data push the data to KBC.
        //
        if(!(vkbc->st_ & KBC_STATUS_OBF)) {
            (*kbc->kbd_dev->onQueueFree)(kbc->kbd_dev);
        }

        //
        //Check the OBF, If it's empty , check Mouse queue , if it's has the data push the data to KBC.
        //
        if(!(vkbc->st_ & KBC_STATUS_OBF)) {
            (*kbc->mouse_dev->onQueueFree)(kbc->mouse_dev);
        }
    }

    return vkbc->st_;
}


//<AMI_PHDR_START>
//----------------------------------------------------------------------------
// Procedure:   vkbc_write_data
//
// Description: Handle write to data port of virtual KBC
//
// Input:       kbc     - pointer to the KBC structure
//              Data    - keyboard controller Data
//
// Output:      Status  - keyboard controller Status
//
//----------------------------------------------------------------------------
//<AMI_PHDR_END>
void    vkbc_write_data( KBC* kbc, UINT8 cmd )
{
    VIRTKBC* vkbc = (VIRTKBC*)kbc;
    VIRTMOUSE* Mouse = (VIRTMOUSE*)kbc->mouse_dev;
    VIRTKBD* Kbd = (VIRTKBD*)kbc->kbd_dev;

    //
    //Check that perviously we got command in port64, if yes then we got data byte for the pervious command
    //
    if (vkbc->TwoByteCmd) {
        vkbc->TwoByteCmd = FALSE;
        switch( vkbc->kbc_command_ ){
            case KBCCMD_WriteAuxDev:
                if(kbc->mouse_dev)
                    (*kbc->mouse_dev->onCommand)(kbc->mouse_dev,cmd);
                vkbc->st_ |= KBC_STATUS_AUXB | KBC_STATUS_OBF;
                break;
            case KBCCMD_WRITE_CCB:
                KeyboardIrq = cmd & BIT0 ? TRUE : FALSE;
                MouseIrq = cmd & BIT1 ? TRUE : FALSE;
                Kbd->Enabled = cmd & BIT4 ? FALSE : TRUE;
                Mouse->Enabled = cmd & BIT5 ? FALSE : TRUE;
                vkbc->ccb_ = cmd;
                break;
            case KBCCMD_WriteAuxBuffer:
                vkbc->st_ |= KBC_STATUS_AUXB | KBC_STATUS_OBF;
                vkbc->outb_ = cmd;
                break;
            case KBCCMD_WriteKbdBuffer:
                gKbdProtocol->Send(gKbdProtocol, (UINT8 *)&cmd,1);
                break;
            case KBCCMD_WriteOutPort:
                OutPortStatus=cmd;
                break;
            default:
                break;
        }
    } else {
        //
        // We got data byte here and process the data byte
        //
        if(kbc->kbd_dev)
            (*kbc->kbd_dev->onCommand)(kbc->kbd_dev,cmd);
    }

    //
    //reset the command and status that command has been processed.
    //
    vkbc->kbc_command_ = 0;
    vkbc->st_ &= ~KBC_STATUS_A2;
}

//<AMI_PHDR_START>
//----------------------------------------------------------------------------
// Procedure:   vkbc_read_data
//
// Description: Handle read from data port of virtual KBC
//
// Input:       kbc     - pointer to the KBC structure
//
//
// Output:      Data    - Data from the keyboard controller
//
//----------------------------------------------------------------------------
//<AMI_PHDR_END>
UINT8   vkbc_read_data( KBC* kbc )
{
    VIRTKBC*    vkbc = (VIRTKBC*)kbc;
    UINT8           Data;

    Data = vkbc->outb_;

    if(vkbc->st_ & KBC_STATUS_OBF) {
        //
        //Reset the OBF flag
        //
        vkbc->st_ &= (~(KBC_STATUS_AUXB | KBC_STATUS_OBF));
    }

    //
    //If we send 1 byte of mouse already , then try to send the remaining 2 bytes of data first and process the keyboard data.
    //

    if(PacketSize >0 && PacketSize < MOUSE_PACKET_SIZE) {

        //
        //Check the OBF, If it's empty , check Mouse queue , if it's has the data push the data to KBC.
        //
        if(!(vkbc->st_ & KBC_STATUS_OBF)) {
            (*kbc->mouse_dev->onQueueFree)(kbc->mouse_dev);
        }

        //
        //Check the OBF, If it's empty , check KBD queue , if it's has the data push the data to KBC.
        //
        if(!(vkbc->st_ & KBC_STATUS_OBF)) {
            (*kbc->kbd_dev->onQueueFree)(kbc->kbd_dev);
        }
    } else {
        //
        //Try to process the keyboard data first.
        //

        PacketSize=0;
        //
        //Check the OBF, If it's empty , check KBD queue , if it's has the data push the data to KBC.
        //
        if(!(vkbc->st_ & KBC_STATUS_OBF)) {
            (*kbc->kbd_dev->onQueueFree)(kbc->kbd_dev);
        }

        //
        //Check the OBF, If it's empty , check Mouse queue , if it's has the data push the data to KBC.
        //
        if(!(vkbc->st_ & KBC_STATUS_OBF)) {
            (*kbc->mouse_dev->onQueueFree)(kbc->mouse_dev);
        }
  }

    return Data;
}


//<AMI_PHDR_START>
//----------------------------------------------------------------------------
// Procedure:   virtkbc_sendout
//
// Description: Keep the data in the output buffer and set the OBF bit set. Based on device set the status bit also.
//
// Input:       kbc     - pointer to the KBC structure
//              Devtype - Data from which device (KBD or Mouse)
//              orvd    -
//              Data    - Data to the kbc buffer
//
// Output:      True: Placed the data successfully.
//
//----------------------------------------------------------------------------
//<AMI_PHDR_END>

BOOLEAN virtkbc_sendout(KBC* kbc, PS2DEV_TYPE devtype,BOOLEAN ovrd, UINT8 data)
{
    VIRTKBC* vkbc = (VIRTKBC*)kbc;
    VIRTKBD* Kbd = (VIRTKBD*)kbc->kbd_dev;

#if OHCI_EMUL_SUPPORT
    //
    // Actual OBF status is maintained by the OHCI controller. 
    // Update the internal structure
    //
    vkbc->st_ &= (~(KBC_STATUS_OBF | KBC_STATUS_AUXB));
    vkbc->st_ |= GetHceStatus() & (KBC_STATUS_OBF  | KBC_STATUS_AUXB);		
#endif 

    if( vkbc->st_ & KBC_STATUS_OBF) {
        if(vkbc->st_ & KBC_STATUS_AUXB) {
            if(MouseIrq) {
            #if IRQ_EMUL_SUPPORT
                GenerateIRQ12(vkbc);
            #endif
            }
        } else {
            #if IRQ_EMUL_SUPPORT
            GenerateIRQ1(vkbc);
            #endif
        }
        //
        //KBC already has the data.
        //
        return FALSE;
    }
    //
    //Save the data in the KBC buffer
    //
    vkbc->outb_ = data;

    //
    //Set the OBF full
    //
    vkbc->st_ |= KBC_STATUS_OBF;

#if OHCI_EMUL_SUPPORT	
    //
	// This is the write place to do. Code flow may take IRQ disabled path or 
    // Trap6064_Handler won't get control because of USB SMI
    //
    SetHceOutput(data);
#endif
    //
    //Set the device type ( from which device data is out)
    //
    if( devtype == PS2DEV_MOUSE) {
        vkbc->st_ |= KBC_STATUS_AUXB;
        //
        //Generate the IRQ12, as AUX OBF is set.
        //
        if(MouseIrq) {
#if IRQ_EMUL_SUPPORT
            GenerateIRQ12(vkbc);
#endif
            //
            //If the input is Mouse data, increment the Packet size, otherwise (responce byte) initlize to 0
            //
            if(ovrd)
                PacketSize=0;
            else
                PacketSize++;
        }
    }else {
        vkbc->st_ &= ~KBC_STATUS_AUXB;
        //
        //Generate IRQ1
        //
#if IRQ_EMUL_SUPPORT
        GenerateIRQ1(vkbc);
#endif
    }

    return TRUE;
}

//<AMI_PHDR_START>
//----------------------------------------------------------------------------
// Procedure:   vkbc_readCCB
//
// Description: Return the CCB data from the KBC buffer
//
// Input:       kbc     - pointer to the KBC structure
//
// Output:      Data: CCB data
//
//----------------------------------------------------------------------------
//<AMI_PHDR_END>
UINT8 vkbc_readCCB(KBC* kbc)
{
    VIRTKBC* vkbc = (VIRTKBC*)kbc;
    return vkbc->ccb_;
}

//
// Initialize KBC structure
//
void initKBC(KBC* kbc, PS2SINK* kbd, PS2SINK* mouse )
{
    kbc->mouse_dev = mouse;
    kbc->kbd_dev = kbd;
    kbc->sqTail[PS2DEV_KBD] = kbc->sqHead[PS2DEV_KBD] = kbc->send_queue;
    kbc->sqTail[PS2DEV_MOUSE] = kbc->sqHead[PS2DEV_MOUSE] = kbc->send_queue_aux;
    kbc->aux_en = KBCCMD_AUXENBL;
    kbc->kbd_en = KBCCMD_KBDENBL;
    kbd->present_ = TRUE;
    kbd->presence_detected_ = FALSE;
    mouse->presence_detected_ = FALSE;
    mouse->present_ = TRUE;
}

//<AMI_PHDR_START>
//----------------------------------------------------------------------------
// Procedure:   InitVirtualKBC
//
// Description: Initialize KBC structure. Set initial state of the emulated KBC
//
// Input:       kbc     - pointer to the KBC structure
//              kbd     - Pointer to the KBD structure
//              mouse - Pointer to the Mouse Structure
//
// Output:      None
//
//----------------------------------------------------------------------------
//<AMI_PHDR_END>
void InitVirtualKBC(VIRTKBC* vkbc, PS2SINK* kbd, PS2SINK* mouse )
{
    initKBC(&vkbc->kbc,kbd,mouse);

    //
    //Initialize the KBC Structure
    //
    vkbc->kbc.kbc_write_command = vkbc_write_command;
    vkbc->kbc.kbc_write_data = vkbc_write_data;
    vkbc->kbc.kbc_read_status = vkbc_read_status;
    vkbc->kbc.kbc_read_data = vkbc_read_data;
    vkbc->kbc.send_outb1 = virtkbc_sendout;
    vkbc->kbc.read_ccb = vkbc_readCCB;

    //
    //Initialize the CCB
    //
    vkbc->ccb_ = 0;
    //
    //Initialize the Port64 Status
    //
    vkbc->st_ = 0x1c;
    //
    //Initialize the Port64 command regsiter
    //
    vkbc->kbc_command_ = 0;
}

//**********************************************************************
//**********************************************************************
//**                                                                  **
//**        (C)Copyright 1985-2011, American Megatrends, Inc.         **
//**                                                                  **
//**                       All Rights Reserved.                       **
//**                                                                  **
//**         5555 Oakbrook Pkwy, Suite 200, Norcross, GA 30093        **
//**                                                                  **
//**                       Phone: (770)-246-8600                      **
//**                                                                  **
//**********************************************************************
//**********************************************************************