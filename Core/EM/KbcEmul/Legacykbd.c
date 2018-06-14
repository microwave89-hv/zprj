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
// $Header: /Alaska/SOURCE/Modules/KbcEmulation/ALASKA/KBCEMUL/Legacykbd.c 4     6/27/12 1:30a Jittenkumarp $
//
// $Revision: 4 $
//
// $Date: 6/27/12 1:30a $
//
//****************************************************************************
// Revision History
// ----------------
// $Log: /Alaska/SOURCE/Modules/KbcEmulation/ALASKA/KBCEMUL/Legacykbd.c $
// 
// 4     6/27/12 1:30a Jittenkumarp
// [TAG]  		EIP89838 
// [Category]  	Improvement
// [Description]  	KbcEmulation module can't changed NUM LOCK ,CAPS
// LOCK,Scroll lock LED.
// [Files]  		Legacykbd.c
// 
// 3     2/10/11 1:04a Rameshr
// [TAG]  		EIP53687
// [Category]  	Improvement
// [Description]  	AMI headers update for KbcEmulation Module
// [Files]  		KbcEmul.mak,KbcEmul.dxs,KbcEmul.c,KbcEmul.h,KbcEmulLib.h,Kbc
// EmulLib.c,Kbc.h,KbcDevEmul.h,Kbccore.c,Legacykbc.c,Legacykbd.c,LegacyMo
// use.c,VirtualKbc.c,VirtualKbd.c,VirtualMouse.c,Ap4x.h,Ap4x.c,KbcUhci.c,
// KbcUhci.h,KbcEmulIrq.c, KbcOhci.c, Kbcohci.h
// 
// 2     6/30/09 11:31a Rameshr
// Coding Standard and File header updated.
// 
// 1     12/14/07 10:26a Rameshraju
// Initial Check-in
//****************************************************************************

//<AMI_FHDR_START>
//****************************************************************************
// Name:        LegacyKbd.c
//
// Description: Legacy Keyboard functions
//
//****************************************************************************
//<AMI_FHDR_END>

#include "KbcEmul.h"
#include "KbcDevEmul.h"
#include "KbcEmulLib.h"

void    LegacyKbd_initParams(LEGACYKBD* kbd);
void    LegacyKbd_read_codes(PS2SINK* ps2dev, UINT8 cmd );
void    LegacyKbd_read_option(PS2SINK* ps2dev, UINT8 cmd );
void    LegacyKbd_rw_scancode(PS2SINK* ps2dev, UINT8 cmd );
void    LegacyKbd_send_resp(LEGACYKBD* mouse, UINT8* data, int count );

BOOLEAN KBC_WaitForInputBufferToBeFree ();
BOOLEAN KBC_WaitForOutputBufferToBeFilled ();
UINT8   KBC_ReadDataByte ();
void    KBC_WriteSubCommandByte(UINT8   bCmd);
void    KBC_WriteCommandByte(UINT8  bCmd);

#define COUNTOF(x) (sizeof(x)/sizeof(x[0]))

static UINT8 ackResp[] = {0xFA};
static UINT8 ResetResp[] = {0xFA,0xAA};
static UINT8 IdResp[] = {0xFA,0xAB, 0x41};
static UINT8 ScanCodePageResp[] = {0xFA, 0x00};
static UINT8 CmdED = 0;

//<AMI_PHDR_START>
//----------------------------------------------------------------------------
// Procedure:   Legacykbd_scanning
//
// Description: Handle commands sent from KBC to PS2 Keyboard. Keyboard is scanning or idle, waiting for command 
//              or key
//
// Input:       ps2dev  - pointer to the KBD structure
//              Cmd     - Data from the kbc buffer
//
// Output:      None
//
//----------------------------------------------------------------------------
//<AMI_PHDR_END>
void Legacykbd_scanning(PS2SINK* ps2dev, UINT8 cmd )
{
    LEGACYKBD* kbd = _CR(ps2dev,LEGACYKBD,sink);
    switch(cmd){
        case 0xFF: //reset
            LegacyKbd_initParams(kbd);
            LegacyKbd_send_resp(kbd, ResetResp,COUNTOF(ResetResp));
            break;
        case 0xFD:
        case 0xFC:
        case 0xFB:
            LegacyKbd_send_resp(kbd, ackResp,COUNTOF(ackResp));
            kbd->read_code_action = cmd;
            kbd->sink.onCommand = LegacyKbd_read_codes;
            break;
        case 0xFA:
        case 0xF9:
        case 0xF8:
        case 0xF7:
        case 0xF6:
        case 0xF5:  //Disable
        case 0xF4:  //Enable
            LegacyKbd_send_resp(kbd, ackResp,COUNTOF(ackResp));
            break;
        case 0xF3:  //Set Typeatic Rate/Delay
            LegacyKbd_send_resp(kbd, ackResp,COUNTOF(ackResp));
            kbd->sink.onCommand = LegacyKbd_read_option;
            kbd->option_ptr = &kbd->typematicRateDelay;
            break;
        case 0xF2:
            LegacyKbd_send_resp(kbd, IdResp,COUNTOF(IdResp));
            break;
        case 0xF0:
            LegacyKbd_send_resp(kbd, ackResp,COUNTOF(ackResp));
            kbd->sink.onCommand = LegacyKbd_rw_scancode;
            kbd->option_ptr = &kbd->scancodepage;
            break;

        case 0xEE:  //Echo
            LegacyKbd_send_resp(kbd, &cmd,1);
            break;

        case 0xED:  //LED
            LegacyKbd_send_resp(kbd, ackResp,COUNTOF(ackResp));
            kbd->sink.onCommand = LegacyKbd_read_option;
            kbd->option_ptr = &kbd->typematicRateDelay;
             CmdED = 1;
            break;
    }
}
//<AMI_PHDR_START>
//----------------------------------------------------------------------------
// Procedure:   LegacyKbd_read_codes
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
void LegacyKbd_read_codes(PS2SINK* ps2dev, UINT8 cmd )
{
    LEGACYKBD* kbd = _CR(ps2dev,LEGACYKBD,sink);
    if( cmd >= 0xED ){
        kbd->sink.onCommand = Legacykbd_scanning;
        Legacykbd_scanning(ps2dev,cmd);
    } else
        LegacyKbd_send_resp(kbd, ackResp,COUNTOF(ackResp));
}
//<AMI_PHDR_START>
//----------------------------------------------------------------------------
// Procedure:   LegacyKbd_read_option
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
void LegacyKbd_read_option(PS2SINK* ps2dev, UINT8 cmd )
{
    LEGACYKBD* kbd = _CR(ps2dev,LEGACYKBD,sink);
    UINT8*   fPtr;

    kbd->sink.onCommand = Legacykbd_scanning;

    if (CmdED == 1) {
        fPtr = (UINT8*)(UINTN)0x417;
        *fPtr &= ~0x70;
        *fPtr |= ((cmd & 0x07) << 4);
        CmdED = 0;
        LegacyKbd_send_resp(kbd, ackResp,COUNTOF(ackResp));
    } else {
        if (cmd > 0xED) {
            Legacykbd_scanning(ps2dev,cmd);
        } else  {
            *(kbd->option_ptr) = cmd;
            LegacyKbd_send_resp(kbd, ackResp,COUNTOF(ackResp));
        }
    }
}
//<AMI_PHDR_START>
//----------------------------------------------------------------------------
// Procedure:   LegacyKbd_rw_scancode
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
void LegacyKbd_rw_scancode(PS2SINK* ps2dev, UINT8 cmd )
{
    LEGACYKBD* kbd = _CR(ps2dev,LEGACYKBD,sink);
    if(cmd != 0 )
        LegacyKbd_read_option(ps2dev,cmd);
    else {
        kbd->sink.onCommand = Legacykbd_scanning;
        ScanCodePageResp[1] = kbd->scancodepage;
        LegacyKbd_send_resp(kbd, ScanCodePageResp,COUNTOF(ScanCodePageResp));
    }
}
//<AMI_PHDR_START>
//----------------------------------------------------------------------------
// Procedure:   LegacyKbd_send_resp
//
// Description: Place the Responce bytes in the keyboard buffer.
//
// Input:       ps2dev      - pointer to the KBD structure
//              Data        - Pointer to the Data
//              count       - Length of the data
//
// Output:      None
//
//----------------------------------------------------------------------------
//<AMI_PHDR_END>
void LegacyKbd_send_resp(LEGACYKBD* kbd, UINT8* data, int count )
{
    //
    //When there is no PS2 Keyboard present in the system, Emulation should send the responce byte for the keyboard command.
    //If PS2 Keyboard present, it will send the responce to the KBC. So Emulation code doesn't need to responce it.
    //
    if(!kbd->sink.present_ ){
        //
        // Emulation must provide the responce. Override any previos kbd data queued to KBC
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
                kbd->qhead = kbd->queue;        }
    }
}

//<AMI_PHDR_START>
//----------------------------------------------------------------------------
// Procedure:   LegacyKbd_pumpQueue
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
void LegacyKbd_pumpQueue(PS2SINK* ps2dev)
{
    LEGACYKBD* kbd = _CR(ps2dev,LEGACYKBD,sink);
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
// Procedure:   LegacykbdInput_Send
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
EFI_STATUS LegacykbdInput_Send(EFI_EMUL6064KBDINPUT_PROTOCOL* p, UINT8* buffer, UINT32 count)
{
    LEGACYKBD* kbd = _CR(p,LEGACYKBD,kbdInput_);
    UINTN c = 0;

    //
    // count of free items in the queue
    //
    if( kbd->qtail >= kbd->qhead )
        c = KBDQUEUE_SIZE - (kbd->qtail - kbd->qhead);
    else
        c = kbd->qhead - kbd->qtail -1;

    if(c < count )
        return EFI_NOT_AVAILABLE_YET;

    for( ; count > 0; --count ){
        *kbd->qtail++ = *buffer++;
        if(kbd->qtail >= kbd->queue+KBDQUEUE_SIZE)
            kbd->qtail = kbd->queue;
    }

    //
    // Disable trap to access real harware
    //
    TrapEnable(FALSE);
    LegacyKbd_pumpQueue(&kbd->sink);
    //
    // Enable trap back and clear statuses
    //
    TrapEnable(TRUE);

    return EFI_SUCCESS;
}
//<AMI_PHDR_START>
//----------------------------------------------------------------------------
// Procedure:   LegacykbdInput_GetTranslation
//
// Description: KBC translation
//
// Input:       P   - pointer to the Emulation Protocol
//
// Output:     None
//
//----------------------------------------------------------------------------
//<AMI_PHDR_END>
EFI_STATUS LegacykbdInput_GetTranslation(
        EFI_EMUL6064KBDINPUT_PROTOCOL* p,
        OUT KBC_KBDTRANSLATION* outTrans )
{
    LEGACYKBD* kbd = _CR(p,LEGACYKBD,kbdInput_);
    *outTrans = (kbd->sink.kbc->read_ccb(kbd->sink.kbc) & KBC_CCB_XLAT) != 0?
            KBC_KBDTRANS_PCXT : KBC_KBDTRANS_AT;
    return EFI_SUCCESS;
}


//<AMI_PHDR_START>
//----------------------------------------------------------------------------
// Procedure:   LegacykbdInput_updateLED
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
EFI_STATUS LegacykbdInput_updateLED(
        EFI_EMUL6064KBDINPUT_PROTOCOL* p,
        IN UINT8 data )
{
    UINT8       bKBData = 0;
    UINT8       bSave;

    //
    // Disable trap to access real harware
    //
    TrapEnable(FALSE);
    //
    // Wait for input buffer to be free
    //
    KBC_WaitForInputBufferToBeFree();
    KBC_WriteCommandByte(KBCCMD_LOCK);
    bSave = ByteReadIO(KBC_STATUS_REG);

    //
    // Data is pending. Read it in AL
    //
    if(bSave & KBC_STATUS_OBF)
    {
        bKBData = ByteReadIO(KBC_DATA_REG);
    }
    KBC_WriteCommandByte(0xAE);
    KBC_WriteSubCommandByte(0xED);
    KBC_ReadDataByte();
    KBC_WriteSubCommandByte(data);
    KBC_ReadDataByte();

    if(bSave & KBC_STATUS_OBF){
        KBC_WriteCommandByte(bSave & KBC_STATUS_AUXB? 0xD3: 0xD2);
        KBC_WriteSubCommandByte(bKBData);
    }
    //
    // Enable trap back and clear statuses
    //
    TrapEnable(TRUE);

    return EFI_SUCCESS;
}

//<AMI_PHDR_START>
//----------------------------------------------------------------------------
// Procedure:   LegacyKbd_initParams
//
// Description: Initialize the KBD data
//
// Input:       kbd   - Pointer to the KBD structure
//
// Output:      None
//
//----------------------------------------------------------------------------
//<AMI_PHDR_END>
void LegacyKbd_initParams(LEGACYKBD* kbd)
{
}

//<AMI_PHDR_START>
//----------------------------------------------------------------------------
// Procedure:   InitLegacyKbd
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
void InitLegacyKbd(KBC* kbc, LEGACYKBD* kbd )
{
    EFI_HANDLE hEmulationService = 0;
    kbd->qhead = kbd->qtail = kbd->queue;
    kbd->sink.kbc = kbc;
    kbd->sink.onCommand = Legacykbd_scanning;
    kbd->sink.onQueueFree = LegacyKbd_pumpQueue;
    kbd->kbdInput_.Send = LegacykbdInput_Send;
    kbd->kbdInput_.GetTranslation = LegacykbdInput_GetTranslation;
    kbd->kbdInput_.UpdateLEDState = LegacykbdInput_updateLED;
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
