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
// $Header: /Alaska/SOURCE/Modules/KbcEmulation/ALASKA/KBCEMUL/KbcDevEmul.h 7     9/30/11 12:45a Rameshr $
//
// $Revision: 7 $
//
// $Date: 9/30/11 12:45a $
//
//****************************************************************************
// Revision History
// ----------------
// $Log: /Alaska/SOURCE/Modules/KbcEmulation/ALASKA/KBCEMUL/KbcDevEmul.h $
// 
// 7     9/30/11 12:45a Rameshr
// [TAG]  		EIP71408
// [Category]  	Improvement
// [Description]  	Remove the customer name reference from the
// KbcEmulation module.
// [Files]  		KbcDevEmul.h,VirtualKbc.c
// 
// 6     2/10/11 1:01a Rameshr
// [TAG]  		EIP53687
// [Category]  	Improvement
// [Description]  	AMI headers update for KbcEmulation Module 
// [Files]  		KbcEmul.mak,KbcEmul.dxs,KbcEmul.c,KbcEmul.h,KbcEmulLib.h,Kbc
// EmulLib.c,Kbc.h,KbcDevEmul.h,Kbccore.c,Legacykbc.c,Legacykbd.c,LegacyMo
// use.c,VirtualKbc.c,VirtualKbd.c,VirtualMouse.c,Ap4x.h,Ap4x.c,KbcUhci.c,
// KbcUhci.h,KbcEmulIrq.c, KbcOhci.c, Kbcohci.h
// 
// 5     7/08/10 1:56a Rameshr
// Ohci Emulation support Added.
// EIP 39712
// 
// 4     2/03/10 1:14a Rameshr
// Install Netware6.5 SP8 Fail.
// EIP 28411
// Single byte and two Byte command is identified properly and handled.
// 
// 3     6/30/09 11:30a Rameshr
// Coding Standard and File header updated.
// 
// 2     10/30/08 10:49a Rameshraju
// Keyboard & Mouse enable/disable command handled
// 
// 1     12/14/07 10:26a Rameshraju
// Initial Check-in
//****************************************************************************

//<AMI_FHDR_START>
//**********************************************************************
//
// Name:        KbcDevEmul.h
//
// Description:	Devices header file
//
//**********************************************************************
//<AMI_FHDR_END>

#ifndef __INC_VKBC_H__
#define __INC_VKBC_H__

#include "Kbc.h"

#define KBD_MOUSE_INTR_DISABLE              0x75
#define MOUSE_INTR_DISABLE                  0x65
#define MOUSE_INTR_ENABLE                   0x47

//
//Virtual KBC
//
typedef struct _VIRTKBC VIRTKBC;

struct _VIRTKBC{
    KBC     kbc;
    UINT8   ccb_;
    UINT8   kbc_command_;
    UINT8   st_;
    UINT8   outb_;
	BOOLEAN TwoByteCmd;
    BOOLEAN DelaySendingDataCmd;
    BOOLEAN fCcb_loaded;
};

void InitVirtualKBC(VIRTKBC* vkbc, PS2SINK* kbd, PS2SINK* mouse );

//
//Legacy KBC. Keep both _VIRTKBC and _LEGACYKBC synced up till DelaySendingDataCmd
//
typedef struct _LEGACYKBC LEGACYKBC;

struct _LEGACYKBC {
    KBC         kbc_;
    UINT8       ccb_;
    UINT8       kbc_command_;
    UINT8       st_;
    UINT8       outb_;
	BOOLEAN     TwoByteCmd;
    BOOLEAN     DelaySendingDataCmd;
    BOOLEAN     fCcb_loaded;
};
void InitLegacyKBC(LEGACYKBC* kbc, PS2SINK* kbd, PS2SINK* mouse );

//
//Virtual KBD & Legacy KBD
//

typedef struct _VIRTKBD VIRTKBD;
typedef struct _VIRTKBD LEGACYKBD;

#define KBDQUEUE_SIZE 10

typedef struct _VIRTKBD{
    PS2SINK sink;

    EFI_EMUL6064KBDINPUT_PROTOCOL kbdInput_;

    UINT8   queue[KBDQUEUE_SIZE];
    UINT8*  qhead;
    UINT8*  qtail;


    UINT8*  option_ptr;
    UINT8   read_code_action;
    UINT8   typematicRateDelay;
    UINT8   scancodepage;
    BOOLEAN Enabled;
};

void InitVirtualKbd(KBC* , VIRTKBD*  );
void InitLegacyKbd(KBC* , LEGACYKBD*  );

//
//Virtual Mouse & Legacy Mouse
//

#define MOUSE_PACKET_SIZE   3

typedef struct _VIRTMOUSE VIRTMOUSE;
typedef struct _VIRTMOUSE LEGACYMOUSE;


#define MOUSEQUEUE_SIZE 12

typedef struct _VIRTMOUSE{
    PS2SINK sink;

    EFI_EMUL6064MSINPUT_PROTOCOL msInput_;

    UINT8   queue[MOUSEQUEUE_SIZE];
    UINT8*  qhead;
    UINT8*  qtail;

    UINT8*  option_ptr;
    UINT8   samplingRate_;
    UINT8   resolution_;

    int     x, y;
    int     fFreshPacket;
    BOOLEAN Enabled;
    int     streaming;
    PS2MouseData dataPacket;
};

void InitVirtualMouse(KBC* kbc, VIRTMOUSE* mouse );
void InitLegacyMouse(KBC* kbc, LEGACYMOUSE* mouse );


#endif // __INC_VKBC_H__

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