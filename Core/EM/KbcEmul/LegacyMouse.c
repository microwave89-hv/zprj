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
// $Header: /Alaska/SOURCE/Modules/KbcEmulation/ALASKA/KBCEMUL/LegacyMouse.c 6     2/16/11 4:05a Rameshr $
//
// $Revision: 6 $
//
// $Date: 2/16/11 4:05a $
//
//****************************************************************************
// Revision History
// ----------------
// $Log: /Alaska/SOURCE/Modules/KbcEmulation/ALASKA/KBCEMUL/LegacyMouse.c $
// 
// 6     2/16/11 4:05a Rameshr
// 
// 5     2/10/11 1:05a Rameshr
// [TAG]  		EIP53687
// [Category]  	Improvement
// [Description]  	AMI headers update for KbcEmulation Module
// [Files]  		KbcEmul.mak,KbcEmul.dxs,KbcEmul.c,KbcEmul.h,KbcEmulLib.h,Kbc
// EmulLib.c,Kbc.h,KbcDevEmul.h,Kbccore.c,Legacykbc.c,Legacykbd.c,LegacyMo
// use.c,VirtualKbc.c,VirtualKbd.c,VirtualMouse.c,Ap4x.h,Ap4x.c,KbcUhci.c,
// KbcUhci.h,KbcEmulIrq.c, KbcOhci.c, Kbcohci.h
// 
// 4     7/08/10 2:01a Rameshr
// Ohci Emulation support Added.
// EIP 39712
// 
// 3     6/30/09 11:31a Rameshr
// Coding Standard and File header updated.
// 
// 2     10/30/08 10:47a Rameshraju
// Keyboard & Mouse enable/disable command handled
// 
// 1     12/14/07 10:26a Rameshraju
// Initial Check-in
//****************************************************************************

//<AMI_FHDR_START>
//****************************************************************************
// Name:        LegacyMouse.c
//
// Description: LegacyMouse functions
//
//****************************************************************************
//<AMI_FHDR_END>

#include "KbcEmul.h"
#include "KbcDevEmul.h"

#define COUNTOF(x) (sizeof(x)/sizeof(x[0]))

static UINT8 resetResp[] = {0xFA, 0xAA, 0x00 } ;
static UINT8 statusResp[] = {0xFA, 0x20, 0x02, 0x64  } ;
static UINT8 dataResp[] = {0xFA, 0x08, 0x00, 0x0  } ;
static UINT8 ackResp[] = {0xFA};
static UINT8 idResp[] = {0xFA, 0};
static UINT8 unknResp[] = {0xFE };

void    Legacymouse_reciev_option(PS2SINK* mouse, UINT8 cmd );
void    Legacymouse_initParams(LEGACYMOUSE* mouse);
void    Legacymouse_flushBuffer(LEGACYMOUSE* mouse);
void    Legacymouse_send_resp(LEGACYMOUSE* mouse, UINT8* data, int count );
void    Legacymouse_echo(PS2SINK* mouse, UINT8 cmd );
BOOLEAN SendLegacyMouseBuffer(LEGACYMOUSE* mouse, UINT8* packet, UINTN Count );
void    Legacymouse_pumpQueue(PS2SINK* ps2dev);
void    KBC_WriteCommandByte(UINT8);
UINT8   KBC_ReadDataByte();
void    KBC_WriteSubCommandByte(UINT8);


//<AMI_PHDR_START>
//----------------------------------------------------------------------------
// Procedure:   mouse_idle
//
// Description: Handle commands sent from KBC to PS2 Mouse. Mouse idle, waiting for command or key
//
// Input:       ps2dev  - pointer to the Mouse structure
//              Cmd     - Data from the kbc buffer
//
// Output:      None
//
//----------------------------------------------------------------------------
//<AMI_PHDR_END>
void Legacymouse_idle(PS2SINK* ps2dev, UINT8 cmd )
{
    LEGACYMOUSE* mouse = (LEGACYMOUSE*)ps2dev;
	UINT8	CCB;

    switch(cmd){
        //
        //reset
        //
        case 0xFF:
            Legacymouse_initParams(mouse);
            Legacymouse_send_resp(mouse, resetResp,COUNTOF(resetResp));
            break;
        //
        //report status
        //
        case 0xE9:
            Legacymouse_send_resp(mouse, statusResp,COUNTOF(statusResp));
            break;
        //
        //read data
        //
        case 0xEB:
            MemCpy(dataResp+1,&mouse->dataPacket,sizeof(mouse->dataPacket));
            Legacymouse_flushBuffer(mouse);
            Legacymouse_send_resp(mouse, dataResp,COUNTOF(dataResp));
            break;
        //
        //Enable Mouse
        //
        case 0xF4:
            //
            //if mouse is not present then atleast CCB needs to be enabled
            //
            if(!mouse->sink.present_ ){
                //
                // Since mouse is not present, Update CCB to enable Mouse. KBC is present if control comes here.	
                //
                KBC_WriteCommandByte(0x20);
                CCB = KBC_ReadDataByte();
                CCB &= 0xDF;
                KBC_WriteCommandByte(0x60);
                KBC_WriteSubCommandByte(CCB);
            }
            mouse->Enabled = TRUE;
            Legacymouse_send_resp(mouse, ackResp,COUNTOF(ackResp));
            break;
        //
        //Disable Mouse
        //
        case 0xF5:
            if(!mouse->sink.present_ ){
                //
                // Since mouse is not present, Update CCB to Disable Mouse. KBC is present if control comes here.	
                //
                KBC_WriteCommandByte(0x20);
                CCB = KBC_ReadDataByte();
                CCB = CCB | 0x20;
                KBC_WriteCommandByte(0x60);
                KBC_WriteSubCommandByte(CCB);
            }
            mouse->Enabled = TRUE;
            Legacymouse_send_resp(mouse, ackResp,COUNTOF(ackResp));
            break;
        //
        //Set Streaming
        //
        case 0xEA:
            mouse->streaming = 1;
            Legacymouse_send_resp(mouse, ackResp,COUNTOF(ackResp));
            break;
        //
        //Set Remote
        //
        case 0xF0:
            mouse->streaming = 0;
            Legacymouse_send_resp(mouse, ackResp,COUNTOF(ackResp));
            break;
        //
        //Set Standard, Set Scaling and Reset Scaling
        //
        case 0xF6:
        case 0xE6:
        case 0xE7:
            Legacymouse_send_resp(mouse, ackResp,COUNTOF(ackResp));
            break;
        //
        //Identify
        //
        case 0xF2:
            Legacymouse_send_resp(mouse, idResp,COUNTOF(idResp));
            break;

        //
        // set resolution
        //
        case 0xE8:
            mouse->option_ptr = &mouse->resolution_;
            ps2dev->onCommand = Legacymouse_reciev_option;
            Legacymouse_send_resp(mouse, ackResp,COUNTOF(ackResp));
            break;
        //
        // set sampling rate
        //
        case 0xF3:
            mouse->option_ptr = &mouse->samplingRate_;
            ps2dev->onCommand = Legacymouse_reciev_option;
            Legacymouse_send_resp(mouse, ackResp,COUNTOF(ackResp));
            break;
        case 0xEE:
            Legacymouse_send_resp(mouse, ackResp,COUNTOF(ackResp));
            ps2dev->onCommand = Legacymouse_echo;
            break;
        //
        ////unknown command; send FE
        //
        default:
            Legacymouse_send_resp(mouse, unknResp,COUNTOF(unknResp));
            break;
    }
}

//<AMI_PHDR_START>
//----------------------------------------------------------------------------
// Procedure:   mouse_echo
//
// Description: Mouse Echo command
//
// Input:       ps2dev  - pointer to the Mouse structure
//              Cmd     - Data from the kbc buffer
//
// Output:      None
//
//----------------------------------------------------------------------------
//<AMI_PHDR_END>
void Legacymouse_echo(PS2SINK* ps2dev, UINT8 cmd )
{
    LEGACYMOUSE* mouse = (LEGACYMOUSE*)ps2dev;
    if( cmd == 0xEC ){
        ps2dev->onCommand = Legacymouse_idle;
        Legacymouse_send_resp(mouse, ackResp,COUNTOF(ackResp));
    } else
        Legacymouse_send_resp(mouse, &cmd,1);

}
//<AMI_PHDR_START>
//----------------------------------------------------------------------------
// Procedure:   mouse_reciev_option
//
// Description: Mouse reciev command
//
// Input:       ps2dev  - pointer to the KBD structure
//              Cmd     - Data from the kbc buffer
//
// Output:      None
//
//----------------------------------------------------------------------------
//<AMI_PHDR_END>
void Legacymouse_reciev_option(PS2SINK* ps2dev, UINT8 cmd )
{
    LEGACYMOUSE* mouse = (LEGACYMOUSE*)ps2dev;
    *(mouse->option_ptr)  = cmd;
    ps2dev->onCommand = Legacymouse_idle;
    Legacymouse_send_resp(mouse, ackResp,COUNTOF(ackResp));
}


//<AMI_PHDR_START>
//----------------------------------------------------------------------------
// Procedure:   msInput_Send
//
// Description: Mouse Input source sends data. Put the data into the buffer, attempt to send the first byte.
//                          The call comes outside of Trapping Leg access. Check that Trapping status will not be overriden
//
// Input:       P   - pointer to the Emulation Protocol
//              Data - Ps2 mouse Data
//
// Output:      None
//
//----------------------------------------------------------------------------
//<AMI_PHDR_END>
EFI_STATUS EFIAPI LegacymsInput_Send(
  IN EFI_EMUL6064MSINPUT_PROTOCOL           * This,
  IN PS2MouseData*                   data
  )
{
    LEGACYMOUSE* mouse = _CR(This,LEGACYMOUSE,msInput_);

    //
    //clear all previous flags except overflow
    //
    mouse->dataPacket.flags &= (PS2MSFLAGS_XO|PS2MSFLAGS_YO);
    //
    //copy overflow and button flags from new packet
    //
    mouse->dataPacket.flags |= data->flags & ~(PS2MSFLAGS_XSIGN|PS2MSFLAGS_YSIGN);
    mouse->dataPacket.flags |= 0x8;
    if( (mouse->dataPacket.flags & PS2MSFLAGS_XO) == 0){
        if(data->flags & PS2MSFLAGS_XSIGN){
            mouse->x += (signed short)((UINT8)data->x | 0xFF00);
        } else {
            mouse->x += data->x;
        }
        mouse->dataPacket.x = (UINT8)(UINT32)(mouse->x);
        if( mouse->x < 0 ){
            mouse->dataPacket.flags |= PS2MSFLAGS_XSIGN;
            if( mouse->x < -256 )
                mouse->dataPacket.flags |= PS2MSFLAGS_XO;
        } else {
            if( mouse->x > 256 )
                mouse->dataPacket.flags |= PS2MSFLAGS_XO;
        }
    }

    if( (mouse->dataPacket.flags & PS2MSFLAGS_YO) == 0){
        if(data->flags & PS2MSFLAGS_YSIGN){
            mouse->y += (signed short)((UINT8)data->y | 0xFF00);
        } else {
            mouse->y += data->y;
        }
        mouse->dataPacket.y = (UINT8)(UINT32)(mouse->y);
        if( mouse->y < 0 ){
            mouse->dataPacket.flags |= PS2MSFLAGS_YSIGN;
            if( mouse->y < -256 )
                mouse->dataPacket.flags |= PS2MSFLAGS_YO;
        } else{
            if( mouse->y > 256 )
                mouse->dataPacket.flags |= PS2MSFLAGS_YO;
        }
    }

    mouse->fFreshPacket = 1;
    if( mouse->Enabled && mouse->streaming ){
        if( SendLegacyMouseBuffer(mouse,(UINT8*)&mouse->dataPacket,sizeof(mouse->dataPacket)))
        {
            Legacymouse_flushBuffer(mouse);
        }
    }
    return EFI_SUCCESS;
}

//<AMI_PHDR_START>
//----------------------------------------------------------------------------
// Procedure:   SendLegacyMouseBuffer
//
// Description: Send the mouse packet to KBC
//
// Input:       Mouse - pointer to the Mouse Structure
//              Packetr - Mouse Data
//              Count - Data Length
//
// Output:      None
//
//----------------------------------------------------------------------------
//<AMI_PHDR_END>
BOOLEAN SendLegacyMouseBuffer(LEGACYMOUSE* mouse, UINT8* packet, UINTN Count )
{
    UINTN   FreeQueue = 0;

    //
    // count of free items in the queue
    //
    if( mouse->qtail >= mouse->qhead )
        FreeQueue = MOUSEQUEUE_SIZE - (mouse->qtail - mouse->qhead);
    else
        FreeQueue = mouse->qhead - mouse->qtail;

    if(FreeQueue < Count )
        return TRUE;

    //
    //place the Mouse data in mouse buffer
    //
    for( ; Count > 0; --Count ){
        *mouse->qtail++ = *packet++;
        if(mouse->qtail >= mouse->queue+MOUSEQUEUE_SIZE)
            mouse->qtail = mouse->queue;
    }

    //
    //Place the dummy 4th byte in mouse buffer,
    //
//  *mouse->qtail++ = 0;
//  if(mouse->qtail >= mouse->queue+MOUSEQUEUE_SIZE)
//      mouse->qtail = mouse->queue;

    //
    // Disable trap to access real harware
    //
    TrapEnable(FALSE);
    //
    //Put the first byte in the KBC buffer
    //
    Legacymouse_pumpQueue(&mouse->sink);
    //
    // Enable trap back and clear statuses
    //
    TrapEnable(TRUE);

    return TRUE;
}

//<AMI_PHDR_START>
//----------------------------------------------------------------------------
// Procedure:   Legacymouse_pumpQueue
//
// Description: KBC has empty queue; Legacy I/O trapping is being processed.If mouse has data to push into KBC,
//              now is a good time to do it
//
// Input:       ps2dev  - pointer to the Mouse structure
//
// Output:      None
//
//----------------------------------------------------------------------------
//<AMI_PHDR_END>
void Legacymouse_pumpQueue(PS2SINK* ps2dev)
{
    LEGACYMOUSE* mouse = (LEGACYMOUSE*)ps2dev;

    //
    //Put the data into KBC
    //
    if((mouse->qhead != mouse->qtail) && (ps2dev->kbc->send_outb1(ps2dev->kbc,PS2DEV_MOUSE,FALSE,*mouse->qhead))) {
        if(++mouse->qhead >=  mouse->queue+MOUSEQUEUE_SIZE)
            mouse->qhead = mouse->queue;
    }
}

//<AMI_PHDR_START>
//----------------------------------------------------------------------------
// Procedure:   Legacymouse_send_resp
//
// Description: Place the Responce bytes in the keyboard buffer.
//
// Input:       Mousev      - pointer to the Mouse structure
//              Data        -   Pointer to the Data
//              count       - Length of the data
//
// Output:      None
//
//----------------------------------------------------------------------------
//<AMI_PHDR_END>
void Legacymouse_send_resp(LEGACYMOUSE* mouse, UINT8* data, int  count )
{
    //
    //When there is no PS2 mouse present in the system, Emulation should send the responce byte for the mouse command.
    //If PS2 mouse present, it will send the responce to the KBC. So Emulation code doesn't need to responce it.
    //
    if(!mouse->sink.present_ ){
        //
        // Emulation must provide the responce. Override any previos mouse data queued to KBC
        //
        mouse->qtail = mouse->qhead = mouse->queue;
        for( ; count > 0; --count ){
            *mouse->qtail++ = *data++;
        }

        ///
        // push the first byte to the KBC
        //
        if( mouse->qhead != mouse->qtail &&
            mouse->sink.kbc->send_outb1(mouse->sink.kbc,PS2DEV_MOUSE,TRUE,*mouse->qhead))
        {
            if(++mouse->qhead >=  mouse->queue+MOUSEQUEUE_SIZE)
                mouse->qhead = mouse->queue;        
        }
    }
}

//<AMI_PHDR_START>
//----------------------------------------------------------------------------
// Procedure:   Legacymouse_flushBuffer
//
// Description: Clear the mouse data buffer that tracks the mouse changes; after the data is cleared any data read
//              will return zero (x,y) and current buttons state.
//
// Input:       ps2dev  - pointer to the KBD structure
//              Cmd     - Data from the kbc buffer
//
// Output:      None
//
//----------------------------------------------------------------------------
//<AMI_PHDR_END>
void Legacymouse_flushBuffer(LEGACYMOUSE* mouse)
{
    mouse->x = mouse->y = 0;
    mouse->dataPacket.x = mouse->dataPacket.y = 0;
    mouse->dataPacket.flags &= (PS2MSFLAGS_LBUTTON|PS2MSFLAGS_RBUTTON);
    mouse->fFreshPacket = 0;
}

//<AMI_PHDR_START>
//----------------------------------------------------------------------------
// Procedure:   mouse_initParams
//
// Description: Initialize the mouse data
//
// Input:       kbd   - Pointer to the mouse structure
//
// Output:      None
//
//----------------------------------------------------------------------------
//<AMI_PHDR_END>
void Legacymouse_initParams(LEGACYMOUSE* mouse)
{
    mouse->samplingRate_ = 0x64;
    mouse->resolution_ = 2;
    mouse->option_ptr = 0;
    mouse->Enabled = FALSE;
    mouse->streaming = 1;
}

//<AMI_PHDR_START>
//----------------------------------------------------------------------------
// Procedure:   InitLegacyMouse
//
// Description: Initialize the Mouse data
//
// Input:       kbc     - pointer to the KBC Structure
//              Mouse   - Pointer to the Mouse structure
//
// Output:      None
//
//----------------------------------------------------------------------------
//<AMI_PHDR_END>
void InitLegacyMouse(KBC* kbc, LEGACYMOUSE* mouse )
{
    EFI_HANDLE hEmulationService = 0;

    mouse->qhead = mouse->qtail = mouse->queue;
    mouse->sink.kbc = kbc;
    mouse->sink.onCommand = Legacymouse_idle;
    mouse->sink.onQueueFree = Legacymouse_pumpQueue;
    mouse->msInput_.Send = LegacymsInput_Send;
    mouse->x = mouse->y = 0;
    mouse->dataPacket.flags = 0x8;
    mouse->dataPacket.x = 0;
    mouse->dataPacket.y = 0;
    mouse->fFreshPacket = 0;
    Legacymouse_initParams(mouse);
    VERIFY_EFI_ERROR(
        gBS->InstallProtocolInterface(&hEmulationService,
        &gEmul6064MsInputProtocolGuid,EFI_NATIVE_INTERFACE,(void*)&mouse->msInput_));
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
