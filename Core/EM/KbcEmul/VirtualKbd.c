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
// $Header: /Alaska/SOURCE/Modules/KbcEmulation/ALASKA/KBCEMUL/VirtualKbd.c 6     2/10/11 1:07a Rameshr $
//
// $Revision: 6 $
//
// $Date: 2/10/11 1:07a $
//
//****************************************************************************
// Revision History
// ----------------
// $Log: /Alaska/SOURCE/Modules/KbcEmulation/ALASKA/KBCEMUL/VirtualKbd.c $
// 
// 6     2/10/11 1:07a Rameshr
// [TAG]  		EIP53687
// [Category]  	Improvement
// [Description]  	AMI headers update for KbcEmulation Module 
// [Files]  		KbcEmul.mak,KbcEmul.dxs,KbcEmul.c,KbcEmul.h,KbcEmulLib.h,Kbc
// EmulLib.c,Kbc.h,KbcDevEmul.h,Kbccore.c,Legacykbc.c,Legacykbd.c,LegacyMo
// use.c,VirtualKbc.c,VirtualKbd.c,VirtualMouse.c,Ap4x.h,Ap4x.c,KbcUhci.c,
// KbcUhci.h,KbcEmulIrq.c, KbcOhci.c, Kbcohci.h
// 
// 5     2/19/10 3:50p Davidd
// Corrected arrow keys not working properly during Netware 6.5
// installation - EIP 28411
// 
// 4     6/30/09 11:31a Rameshr
// Coding Standard and File header updated.
// 
// 3     10/30/08 10:47a Rameshraju
// Keyboard & Mouse enable/disable command handled
// 
// 2     5/01/08 10:43a Rameshraju
// Keyboard command D2 support added
// 
// 1     12/14/07 10:26a Rameshraju
// Initial Check-in
//****************************************************************************

//<AMI_FHDR_START>
//****************************************************************************
// Name:        VirtualKbd.c
//
// Description: Virtual keyboard functions
//****************************************************************************
//<AMI_FHDR_END>

#include "KbcEmul.h"
#include "KbcDevEmul.h"

#define COUNTOF(x) (sizeof(x)/sizeof(x[0]))

void vkbd_initParams(VIRTKBD* kbd);
void vkbd_read_codes(PS2SINK* ps2dev, UINT8 cmd );
void vkbd_read_option(PS2SINK* ps2dev, UINT8 cmd );
void vkbd_rw_scancode(PS2SINK* ps2dev, UINT8 cmd );
void vkbd_send_resp(VIRTKBD* mouse, UINT8* data, int count );

static UINT8 ackResp[] = {0xFA};
static UINT8 ResetResp[] = {0xFA,0xAA};
static UINT8 IdResp[] = {0xFA,0xAB, 0x41};
static UINT8 ScanCodePageResp[] = {0xFA, 0x00};
EFI_EMUL6064KBDINPUT_PROTOCOL   *gKbdProtocol=NULL;
static UINT8 CmdED = 0;

//<AMI_PHDR_START>
//----------------------------------------------------------------------------
// Procedure:   kbd_scanning
//
// Description: Handle commands sent from KBC to PS2 Keyboard. Keyboard is scanning or idle, waiting for command or key
//
// Input:       ps2dev  - pointer to the KBD structure
//              Cmd     -   Data from the kbc buffer
//
// Output:      None
//
//----------------------------------------------------------------------------
//<AMI_PHDR_END>
void kbd_scanning(PS2SINK* ps2dev, UINT8 cmd )
{
    VIRTKBD* kbd = _CR(ps2dev,VIRTKBD,sink);

    switch(cmd){
        //
        //Reset
        //
        case 0xFF:
            vkbd_initParams(kbd);
            vkbd_send_resp(kbd, ResetResp,COUNTOF(ResetResp));
            break;
        case 0xFD:
        case 0xFC:
        case 0xFB:
            vkbd_send_resp(kbd, ackResp,COUNTOF(ackResp));
            kbd->read_code_action = cmd;
            kbd->sink.onCommand = vkbd_read_codes;
            break;
        case 0xFA:
        case 0xF9:
        case 0xF8:
        case 0xF7:
        case 0xF6:
        case 0xF5:  
        case 0xF4:  //Enable
            kbd->Enabled=TRUE;
            vkbd_send_resp(kbd, ackResp,COUNTOF(ackResp));
            break;
        //
        //Set Typeatic Rate/Delay
        //
        case 0xF3:
            vkbd_send_resp(kbd, ackResp,COUNTOF(ackResp));
            kbd->sink.onCommand = vkbd_read_option;
            kbd->option_ptr = &kbd->typematicRateDelay;
            break;
        case 0xF2:
            vkbd_send_resp(kbd, IdResp,COUNTOF(IdResp));
            break;
        case 0xF0:
            vkbd_send_resp(kbd, ackResp,COUNTOF(ackResp));
            kbd->sink.onCommand = vkbd_rw_scancode;
            kbd->option_ptr = &kbd->scancodepage;
            break;
        //
        //Ehco
        //
        case 0xEE:
            vkbd_send_resp(kbd, &cmd, 1);
            break;

        //
        //Led
        //
        case 0xED:
            vkbd_send_resp(kbd, ackResp, COUNTOF(ackResp));
            kbd->sink.onCommand = vkbd_read_option;
            kbd->option_ptr = &kbd->typematicRateDelay;
            CmdED = 1;
            break;
    }
}

//<AMI_PHDR_START>
//----------------------------------------------------------------------------
// Procedure:   vkbd_read_codes
//
// Description: Keyboard Read Codes.
//
// Input:       ps2dev  - pointer to the KBD structure
//              Cmd     - Data from the kbc buffer
//
// Output:      None
//
//----------------------------------------------------------------------------
//<AMI_PHDR_END>
void vkbd_read_codes(PS2SINK* ps2dev, UINT8 cmd )
{
    VIRTKBD* kbd = _CR(ps2dev,VIRTKBD,sink);
    if( cmd >= 0xED ){
        kbd->sink.onCommand = kbd_scanning;
        kbd_scanning(ps2dev,cmd);
    } else
        vkbd_send_resp(kbd, ackResp,COUNTOF(ackResp));
}

//<AMI_PHDR_START>
//----------------------------------------------------------------------------
// Procedure:   vkbd_read_option
//
// Description: Keyboard Read option.
//
// Input:       ps2dev  - pointer to the KBD structure
//              Cmd     - Data from the kbc buffer
//
// Output:      None
//
//----------------------------------------------------------------------------
//<AMI_PHDR_END>
void vkbd_read_option(PS2SINK* ps2dev, UINT8 cmd )
{
    VIRTKBD* kbd = _CR(ps2dev,VIRTKBD,sink);
    UINT8*   fPtr;

    kbd->sink.onCommand = kbd_scanning;

    if (CmdED == 1) {
        fPtr = (UINT8*)(UINTN)0x417;
        *fPtr &= ~0x70;
        *fPtr |= ((cmd & 0x07) << 4);
        CmdED = 0;
        vkbd_send_resp(kbd, ackResp,COUNTOF(ackResp));
    }
    else {
        if (cmd > 0xED) {
            kbd_scanning(ps2dev,cmd);
        } else  {
            *(kbd->option_ptr) = cmd;
            vkbd_send_resp(kbd, ackResp,COUNTOF(ackResp));
        }
    }
}

//<AMI_PHDR_START>
//----------------------------------------------------------------------------
// Procedure:   vkbd_rw_scancode
//
// Description: Keyboard Read write Scan code.
//
// Input:       ps2dev  - pointer to the KBD structure
//              Cmd     - Data from the kbc buffer
//
// Output:      None
//
//----------------------------------------------------------------------------
//<AMI_PHDR_END>
void vkbd_rw_scancode(PS2SINK* ps2dev, UINT8 cmd )
{
    VIRTKBD* kbd = _CR(ps2dev,VIRTKBD,sink);
    if(cmd != 0 )
        vkbd_read_option(ps2dev,cmd);
    else {
        kbd->sink.onCommand = kbd_scanning;
        ScanCodePageResp[1] = kbd->scancodepage;
        vkbd_send_resp(kbd, ScanCodePageResp,COUNTOF(ScanCodePageResp));
    }
}
//<AMI_PHDR_START>
//----------------------------------------------------------------------------
// Procedure:   vkbd_send_resp
//
// Description: Place the Responce bytes in the keyboard buffer.
//
// Input:       ps2dev      - pointer to the KBD structure
//              Data        -   Pointer to the Data
//              count       - Length of the data
//
// Output:      None
//
//----------------------------------------------------------------------------
//<AMI_PHDR_END>
void vkbd_send_resp(VIRTKBD* kbd, UINT8* data, int count )
{
    if( kbd->sink.present_ ){
        //
        // Emulation must provide the responce. Override any pervious kbd data queued to KBC
        //
        kbd->qtail = kbd->qhead = kbd->queue;
        for( ; count > 0; --count ){
            *kbd->qtail++ = *data++;
        }

        //
        // push the first byte to the KBC
        //
        if( kbd->qhead != kbd->qtail &&
            kbd->sink.kbc->send_outb1(kbd->sink.kbc,
            PS2DEV_KBD,TRUE,*kbd->qhead))
        {
            if(++kbd->qhead >=  kbd->queue+KBDQUEUE_SIZE)
                kbd->qhead = kbd->queue;
        }
    }
}

//<AMI_PHDR_START>
//----------------------------------------------------------------------------
// Procedure:   vkbd_pumpQueue
//
// Description: KBC has empty queue; Legacy I/O trapping is being processed.If Kbd has data to push into KBC,
//              now is a good time to do it
//
// Input:       ps2dev  - pointer to the KBD structure
//
// Output:      None
//
//----------------------------------------------------------------------------
//<AMI_PHDR_END>

void vkbd_pumpQueue(PS2SINK* ps2dev)
{
    VIRTKBD* kbd = _CR(ps2dev,VIRTKBD,sink);
    //
    //send the Keyboard data to the KBC
    //
    if( kbd->qhead != kbd->qtail &&
        ps2dev->kbc->send_outb1(ps2dev->kbc,PS2DEV_KBD,FALSE,*kbd->qhead))
    {
        if(++kbd->qhead >=  kbd->queue+KBDQUEUE_SIZE)
            kbd->qhead = kbd->queue;
    }

}

//<AMI_PHDR_START>
//----------------------------------------------------------------------------
// Procedure:   kbdInput_Send
//
// Description: Keyboard Input source sends data. Put the data into the buffer, attempt to send the first byte.
//              The call comes outside of Trapping Leg access. Check that Trapping status will not be overriden
//
// Input:       P       - pointer to the Emulation Protocol
//              Buffer  - Data buffer
//              Count   - Buffer Length
//
// Output:      None
//
//----------------------------------------------------------------------------
//<AMI_PHDR_END>
EFI_STATUS kbdInput_Send(EFI_EMUL6064KBDINPUT_PROTOCOL* p, UINT8* buffer, UINT32 count)
{
    VIRTKBD* kbd = _CR(p,VIRTKBD,kbdInput_);
    UINTN c = 0;

    //
    //Keyboard is disabled by KBC command 
    //
    if(!kbd->Enabled) {
        return EFI_DEVICE_ERROR;
    }

    //
    // count of free items in the queue
    //
    if( kbd->qtail >= kbd->qhead )
        c = KBDQUEUE_SIZE - (kbd->qtail - kbd->qhead);
    else
        c = kbd->qhead - kbd->qtail;

    if(c < count )
        return EFI_NOT_AVAILABLE_YET;

    for( ; count > 0; --count ){
        *kbd->qtail++ = *buffer++;
        if(kbd->qtail >= kbd->queue+KBDQUEUE_SIZE)
            kbd->qtail = kbd->queue;
    }
    //
    //Place the first data into the KBC buffer
    //
    vkbd_pumpQueue(&kbd->sink);

    return EFI_SUCCESS;
}

//<AMI_PHDR_START>
//----------------------------------------------------------------------------
// Procedure:   kbdInput_GetTranslation
//
// Description: KBC translation
//
// Input:       P   - pointer to the Emulation Protocol
//
// Output:     None
//
//----------------------------------------------------------------------------
//<AMI_PHDR_END>

EFI_STATUS kbdInput_GetTranslation(
        EFI_EMUL6064KBDINPUT_PROTOCOL* p,
        OUT KBC_KBDTRANSLATION* outTrans )
{
    *outTrans=KBC_KBDTRANS_PCXT;
    return EFI_SUCCESS;
}

//<AMI_PHDR_START>
//----------------------------------------------------------------------------
// Procedure:   kbdInput_updateLED
//
// Description: Update the keyboard LED's
//
// Input:       P       - pointer to the Emulation Protocol
//              Data    - LED data
//
// Output:      None
//
//----------------------------------------------------------------------------
//<AMI_PHDR_END>
EFI_STATUS kbdInput_updateLED(
        EFI_EMUL6064KBDINPUT_PROTOCOL* p,
        IN UINT8 data )
{
    return EFI_SUCCESS;
}

//<AMI_PHDR_START>
//----------------------------------------------------------------------------
// Procedure:   vkbd_initParams
//
// Description: Initialize the KBD data
//
// Input:       kbd   - Pointer to the KBD structure
//
// Output:      None
//
//----------------------------------------------------------------------------
//<AMI_PHDR_END>
void vkbd_initParams(VIRTKBD* Kbd)
{
    Kbd->Enabled = TRUE;
}

//<AMI_PHDR_START>
//----------------------------------------------------------------------------
// Procedure:   InitVirtualKbd
//
// Description: Initialize the KBD data
//
// Input:       kbc     - pointer to the KBC Structure
//              kbd     - Pointer to the KBD structure
//
// Output:      None
//
//----------------------------------------------------------------------------
//<AMI_PHDR_END>
void InitVirtualKbd(KBC* kbc, VIRTKBD* kbd )
{
    EFI_HANDLE hEmulationService = 0;
    kbd->qhead = kbd->qtail = kbd->queue;
    kbd->sink.kbc = kbc;
    kbd->sink.onCommand = kbd_scanning;
    kbd->sink.onQueueFree = vkbd_pumpQueue;
    kbd->kbdInput_.Send = kbdInput_Send;
    kbd->kbdInput_.GetTranslation = kbdInput_GetTranslation;
    kbd->kbdInput_.UpdateLEDState = kbdInput_updateLED;
    gKbdProtocol=&kbd->kbdInput_;
    vkbd_initParams(kbd);
    VERIFY_EFI_ERROR(
        gBS->InstallProtocolInterface(&hEmulationService,
        &gEmul6064KbdInputProtocolGuid,EFI_NATIVE_INTERFACE,(void*)&kbd->kbdInput_));
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