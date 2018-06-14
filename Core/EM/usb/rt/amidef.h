//****************************************************************************
//****************************************************************************
//**                                                                        **
//**             (C)Copyright 1985-2016, American Megatrends, Inc.          **
//**                                                                        **
//**                          All Rights Reserved.                          **
//**                                                                        **
//**                 5555 Oakbrook Pkwy, Norcross, GA 30093                 **
//**                                                                        **
//**                          Phone (770)-246-8600                          **
//**                                                                        **
//****************************************************************************
//****************************************************************************

//**********************************************************************
// $Header: /Alaska/SOURCE/Modules/USB/ALASKA/rt/amidef.h 40    10/28/16 3:57a Wilsonlee $
//
// $Revision: 40 $
//
// $Date: 10/28/16 3:57a $
//
//**********************************************************************
// Revision History
// ----------------
// $Log: /Alaska/SOURCE/Modules/USB/ALASKA/rt/amidef.h $
// 
// 40    10/28/16 3:57a Wilsonlee
// [TAG]  		EIP300142
// [Category]  	Improvement
// [Description]  	Remove USB Int1C module part because we use the other
// method to service xhci.
// [Files]  		usbport.c, amidef.h, amiusbhc.c, UsbLegacy.cif
// 
// 39    10/28/16 1:29a Wilsonlee
// [TAG]  		EIP300142
// [Category]  	Improvement
// [Description]  	Get vector value from memory 0x1c directly and check
// it's not zero.
// [Files]  		usbport.c, amidef.h
// 
// 38    12/16/13 1:41a Ryanchou
// [TAG]  		EIP142509
// [Category]  	Improvement
// [Description]  	Added usage 0x87 and 0x89.
// [Files]  		efiusbkb.c, efiusbkb.h. amidef.h
// 
// 37    5/22/12 10:03a Ryanchou
// [TAG]  		EIP90154
// [Category]  	Improvement
// [Description]  	Remove the USBSB_EnableSmmPeriodicSmi and
// USBSB_DisableSmmPeriodicSmi hooks.
// [Files]  		amidef.h, amiusb.c, usb.c, usbsb.c
// 
// 36    5/04/12 5:20a Wilsonlee
// [TAG]  		EIP89307
// [Category]  	Improvement
// [Description]  	Modify incorrect #pragma pack directive.
// [Files]  		amidef.h, amiusb.c, ehci.c, ohci.c, ohci.h, uhci.h, usb.c,
// usbdef.h, xhci.h, efiusbmass.c, uhcd.c, uhcd.h, usbbus.c, usbbus.h,
// UsbIo.h
// 
// 35    11/08/11 2:01a Ryanchou
// [TAG]  		EIP63188
// [Category]  	Improvement
// [Description]  	External USB controller support.
// [Files]  		amidef.h, amiusb.c, ehci.c, ohci.c, uhcd.c, uhcd.h, uhci.c,
// usbdef.h, usbmisc.c, usbsb.c, xhci.c
// 
// 34    4/06/11 3:26a Ryanchou
// [TAG]  		EIP55275
// [Category]  	Bug Fix
// [Severity]  	Important
// [Symptom]  	EBDA:108 conflict
// [RootCause]  	The EIP48064 save EFI_USB_PROTOCOL pointer in EBDA:108,
// but Keymon filter driver used the same location.
// [Solution]  	Use the EBDA:32 to save EFI_USB_PROTOCOL pointer and add a
// signature in EFI_USB_PROTOCOL.
// [Files]  		amidef.h, AmiUsbController.h, uhcd.c, usbsb.c
// 
// 33    11/22/10 8:44a Ryanchou
// [TAG]  		EIP48064
// [Category]  	Improvement
// [Description]  	The SB template implemented elink
// AcpiEnableCallbackList, the XHCI/EHCI hand off function should be
// invoked via the elink AcpiEnableCallbackList.
// [Files]  		amidef.h, amiusb.c, amiusb.dxs, amiusb.h,
// AmiUsbController.h, usb.sdl, usbrt.mak, usbsb.c
// 
// 32    10/07/10 10:14a Ryanchou
// EIP41379: Move the code that install xHCI hardware SMI handler in
// XHCI_Start function.
// 
// 31    3/25/10 9:47a Olegi
// 
// 30    3/19/10 10:06a Olegi
// 
// 29    11/30/09 6:11p Olegi
// 
// 28    11/30/09 9:08a Olegi
// 
// 27    10/02/09 10:50a Olegi
// Code cleanup.
// 
// 26    10/03/08 3:33p Olegi
// 
// 25    9/05/08 3:45p Olegi
// Definitions related to USB SMI code isolation.
// 
// 24    5/16/08 12:03p Olegi
// Compliance with AMI coding standard.
// 
// 23    7/13/07 11:42a Olegi
// F11 and F12 codes added.
// 
// 22    3/20/07 1:26p Olegi
//
// 21    3/07/07 5:59p Olegi
//
// 20    10/25/06 10:59a Olegi
//
// 19    10/12/06 9:11p Andriyn
//
// 18    10/12/06 5:17p Olegi
//
// 17    10/12/06 5:01p Felixp
// EfiCreateEventLegacyBoot added
//
// 16    10/12/06 4:42p Olegi
//
// 15    5/31/06 6:56p Mirk
// Core 4.5 compliant - DP Length manipulation changes.
//
// 14    5/03/06 10:00a Olegi
//
// 13    4/14/06 6:43p Olegi
// Conversion to be able to use x64 compiler.
//
// 10    1/11/06 1:42p Olegi
//
// 9     11/10/05 11:11a Olegi
//
// 8     8/26/05 12:25p Andriyn
//
// 7     8/15/05 3:59p Olegi
//
// 6     8/05/05 3:38p Andriyn
// Complience with EFI EDK
//
// 5     6/03/05 6:32p Andriyn
// Redifinition of library function for source complience with Aptio
//
// 4     5/20/05 11:05a Andriyn
// reconcile Aptio changes with Alaska
//
// 3     5/17/05 7:51p Andriyn
// USB BUS pre-release
//
// 2     5/10/05 4:13p Andriyn
// USBBUS implementation
//
// 1     3/29/05 10:40a Olegi
//
// 1     3/15/05 9:23a Olegi
// Initial VSS check-in.
//
//**********************************************************************

//<AMI_FHDR_START>
//----------------------------------------------------------------------------
//
//  Name:           AmiDef.h
//
//  Description:    AMI USB driver definitions, framework specific
//
//----------------------------------------------------------------------------
//<AMI_FHDR_END>

// Avoid including multiple instance of this file

#ifndef     __AMI_H
#define     __AMI_H

#include    "token.h"

#define USB_DRIVER_VERSION  (USB_DRIVER_MAJOR_VER << 4) + USB_DRIVER_MINOR_VER

#include    "Efi.h"
#include <AmiDxeLib.h>
#define _FAR_

//  Basic type definitions of various size

#if (__STDC_VERSION__ < 199901L )

    /*  No ANSI C 1999/2000 stdint.h integer width declarations  */

    #if _MSC_EXTENSIONS

        /*  Use Microsoft C compiler integer width declarations  */
#if _64_BIT_EXTENSIONS
        typedef unsigned __int64    UINT64;
        typedef __int64             INT64;
typedef UINT64                  QWORD;
typedef QWORD *                 PQWORD;
typedef QWORD _FAR_ *           FPQWORD;
typedef UINT64 *                    PUINT64;
typedef INT64  *                    PINT64;
typedef UINT64 _FAR_ *          FPUINT64;
typedef INT64 _FAR_ *           FPINT64;
#endif
//        typedef unsigned __int32    UINT32;
//        typedef __int32             INT32;
//        typedef unsigned __int16    UINT16;
//        typedef __int16             INT16;
//        typedef unsigned __int8     UINT8;
//        typedef __int8              INT8;
     #else
#if _64_BIT_EXTENSIONS
#endif
    #endif
#endif

// Return code definition
typedef INT16           RETCODE;

//  64-bit extenstion definition
#if _64_BIT_EXTENSIONS
#endif

#ifndef NULL
#define NULL                    0
#endif

// Private and public definitions
#define PRIVATE             static
#define PUBLIC

// Function IN/OUT definitions
#define IN
#define OUT
#define IN_OUT

// Return codes
#define SUCCESS         0
#define FAILURE         -1

#ifndef TRUE
#define TRUE            1
#endif
#ifndef FALSE
#define FALSE           0
#endif
// Bit equates
#define BIT0                0x01
#define BIT1                0x02
#define BIT2                0x04
#define BIT3                0x08
#define BIT4                0x10
#define BIT5                0x20
#define BIT6                0x40
#define BIT7                0x80
#define BIT8                0x100
#define BIT9                0x200
/* defined in AmiDxeLib
#define BIT10               0x400
#define BIT11               0x800
#define BIT12               0x1000
#define BIT13               0x2000
#define BIT14               0x4000
#define BIT15               0x8000
#define BIT16               0x10000
#define BIT17               0x20000
#define BIT18               0x40000
#define BIT19               0x80000
#define BIT20               0x100000
#define BIT21               0x200000
#define BIT22               0x400000
#define BIT23               0x800000
#define BIT24               0x1000000
#define BIT25               0x2000000
#define BIT26               0x4000000
#define BIT27               0x8000000
#define BIT28               0x10000000
#define BIT29               0x20000000
#define BIT30               0x40000000
#define BIT31               0x80000000
*/
#define SCAN_NULL EFI_SCAN_NULL
#define SCAN_ESC EFI_SCAN_ESC
#define SCAN_F1 EFI_SCAN_F1
#define SCAN_F2 EFI_SCAN_F2
#define SCAN_F3 EFI_SCAN_F3
#define SCAN_F4 EFI_SCAN_F4
#define SCAN_F5 EFI_SCAN_F5
#define SCAN_F6 EFI_SCAN_F6
#define SCAN_F7 EFI_SCAN_F7
#define SCAN_F8 EFI_SCAN_F8
#define SCAN_F9 EFI_SCAN_F9
#define SCAN_F10 EFI_SCAN_F10
#define SCAN_F11 EFI_SCAN_F11
#define SCAN_F12 EFI_SCAN_F12
#define SCAN_INSERT EFI_SCAN_INS
#define SCAN_HOME EFI_SCAN_HOME
#define SCAN_PAGE_UP EFI_SCAN_PGUP
#define SCAN_DELETE EFI_SCAN_DEL
#define SCAN_END EFI_SCAN_END
#define SCAN_PAGE_DOWN EFI_SCAN_PGDN
#define SCAN_RIGHT EFI_SCAN_RIGHT
#define SCAN_LEFT EFI_SCAN_LEFT
#define SCAN_DOWN EFI_SCAN_DN
#define SCAN_UP EFI_SCAN_UP

#ifndef SCAN_PAUSE
#define SCAN_PAUSE                0x0048
#define SCAN_F13                  0x0068
#define SCAN_F14                  0x0069
#define SCAN_F15                  0x006A
#define SCAN_F16                  0x006B
#define SCAN_F17                  0x006C
#define SCAN_F18                  0x006D
#define SCAN_F19                  0x006E
#define SCAN_F20                  0x006F
#define SCAN_F21                  0x0070
#define SCAN_F22                  0x0071
#define SCAN_F23                  0x0072
#define SCAN_F24                  0x0073
#define SCAN_MUTE                 0x007F
#define SCAN_VOLUME_UP            0x0080
#define SCAN_VOLUME_DOWN          0x0081
#define SCAN_BRIGHTNESS_UP        0x0100
#define SCAN_BRIGHTNESS_DOWN      0x0101
#define SCAN_SUSPEND              0x0102
#define SCAN_HIBERNATE            0x0103
#define SCAN_TOGGLE_DISPLAY       0x0104
#define SCAN_RECOVERY             0x0105
#define SCAN_EJECT                0x0106
#endif

#define EFI_BLOCK_IO_PROTOCOL EFI_BLOCK_IO
#define EFI_SIMPLE_TEXT_IN_PROTOCOL SIMPLE_INPUT_INTERFACE

//#define MESSAGING_DEVICE_PATH MESSAGING_DEVICE_PATH_TYPE
//#define MSG_USB_CLASS_DP MSG_USB_CLASS_DEVICE_PATH_SUBTYPE
#define EFI_END_ENTIRE_DEVICE_PATH          END_DEVICE_PATH
#define EFI_END_ENTIRE_DEVICE_PATH_SUBTYPE  END_ENTIRE_SUBTYPE
//#define MSG_SCSI_DP       MSG_SCSI_DEVICE_PATH_SUBTYPE
//#define Pun TargetId

#define EFI_DRIVER_ENTRY_POINT(x)
//#define EFI_LOADED_IMAGE_PROTOCOL EFI_LOADED_IMAGE
#define EfiInitializeSmmDriverLib(ImageHandle, SystemTable) InitAmiLib(ImageHandle, SystemTable)
#define EfiInitializeDriverLib(ImageHandle, SystemTable) InitAmiLib(ImageHandle,SystemTable)
#define gBS pBS
#define gRT pRS
#define EfiDuplicateDevicePath              DPCopy


// Loop forever macro
#define LOOP_FOREVER    while(1)

#if defined(DEBUG_SWITCH) && (DEBUG_SWITCH == 1)
#define EfiDebugVPrint(EFI_D_ERROR, Message, ArgList) PrintDebugMessageVaList(-1, Message, ArgList)

extern  RETCODE         PrintDebugMsg (int, char *, ...);
#define USB_DEBUG       PrintDebugMsg
#define USB_DEBUG_LEVEL DEBUG_LEVEL_3
void DEBUG_DELAY();
#else
extern  RETCODE         PrintDebugMsg (int, char *, ...);
#define USB_DEBUG       1?0:PrintDebugMsg
#define DEBUG_DELAY
#endif

#if GENERIC_USB_CABLE_SUPPORT
#undef USB_DEBUG
#define USB_DEBUG
#endif

#define  MAX_DEBUG_LEVEL        8

#define DEBUG_LEVEL_8           8
#define DEBUG_LEVEL_7           7
#define DEBUG_LEVEL_6           6
#define DEBUG_LEVEL_5           5
#define DEBUG_LEVEL_4           4
#define DEBUG_LEVEL_3           3
#define DEBUG_LEVEL_2           2
#define DEBUG_LEVEL_1           1
#define DEBUG_LEVEL_0           0

#define MICROSECOND     10
#define MILLISECOND     (1000 * MICROSECOND)
#define ONESECOND       (1000 * MILLISECOND)

#define USB_DATA_EBDA_OFFSET		0x104
#define USB_PROTOCOL_EBDA_OFFSET	0x32		//(EIP55275)

#define GET_CPUSAVESTATE_REG(x) (URP_STRUC*)(UINTN)gSmst->CpuSaveState->Ia32SaveState.x
//#define GET_FV_NAME(pImage) &((FV_FILE_PATH_DEVICE_PATH*)(pImage->FilePath))->Name
#define GET_FV_NAME(pImage) &((MEDIA_FW_VOL_FILEPATH_DEVICE_PATH*)(pImage->FilePath))->NameGuid
#define EfiDevicePathNodeLength(a)  (((a)->Length[0]) | ((a)->Length[1] << 8))
//#define EfiNextDevicePathNode(a)    ((EFI_DEVICE_PATH_PROTOCOL *) ( ((UINT8 *) (a)) + \
//                                      EfiDevicePathNodeLength(a)))
#define EfiNextDevicePathNode(a) NEXT_NODE(a)

#define EfiDevicePathType(a)          ( ((a)->Type) & 0x7f )
#define EfiIsDevicePathEndType(a)     (EfiDevicePathType(a) == 0x7f)


#define EfiIsDevicePathEndSubType(a)          ((a)->SubType == 0xFF)
#define EfiIsDevicePathEndInstanceSubType(a)  ((a)->SubType == 1)

#define EfiIsDevicePathEnd(a)         ( EfiIsDevicePathEndType(a) && \
                                        EfiIsDevicePathEndSubType(a) )
#define EfiIsDevicePathEndInstance(a) ( EfiIsDevicePathEndType(a) && \
                                        EfiIsDevicePathEndInstanceSubType(a) )
//#define SetDevicePathNodeLength(a,l) { (a)->Length = (l); }
#define SetDevicePathNodeLength(a,l) ( SET_NODE_LENGTH(a,l) )
//#define DevicePathNodeLength(a)     ( ((a)->Length[0]) | ((a)->Length[1] << 8) )
#define DevicePathNodeLength(a)      ( NODE_LENGTH(a) )
//#define NextDevicePathNode(a)       ( (EFI_DEVICE_PATH_PROTOCOL *) ( ((UINT8 *) (a)) + DevicePathNodeLength(a)))
#define NextDevicePathNode(a)       ( (EFI_DEVICE_PATH_PROTOCOL *) ( ((UINT8 *) (a)) + NODE_LENGTH(a)))
#define SetDevicePathEndNode(a)  {                       \
          (a)->Type = 0x7F;              \
          (a)->SubType = 0xFF; \
          (a)->Length = sizeof(EFI_DEVICE_PATH_PROTOCOL);      \
          }

#define VA_LIST va_list
#define VA_START va_start
#define VA_ARG va_arg
#define VA_END va_end

//
//  CONTAINING_RECORD - returns a pointer to the structure
//      from one of it's elements.
//
#define _CR(Record, TYPE, Field)  \
    ((TYPE *) ( (CHAR8 *)(Record) - (CHAR8 *) &(((TYPE *) 0)->Field)))


//
// Define macros to build data structure signatures from characters.
//
#define EFI_SIGNATURE_16(A,B)             ((A) | (B<<8))
#define EFI_SIGNATURE_32(A,B,C,D)         (EFI_SIGNATURE_16(A,B)     | (EFI_SIGNATURE_16(C,D)     << 16))
#define EFI_SIGNATURE_64(A,B,C,D,E,F,G,H) (EFI_SIGNATURE_32(A,B,C,D) | ((UINT64)(EFI_SIGNATURE_32(E,F,G,H)) << 32))

#define EfiCopyMem(_Destination, _Source, _Length)  gBS->CopyMem ((_Destination), (_Source), (_Length))
#define EfiSetMem(_Destination, _Length, _Value)   gBS->SetMem  ((_Destination), (_Length), (_Value))
#define EfiZeroMem(_Destination, _Length)          gBS->SetMem  ((_Destination), (_Length), 0)

#define EFI_TPL_NOTIFY TPL_NOTIFY
#define EFI_TPL_CALLBACK TPL_CALLBACK
#define EFI_TPL_HIGH_LEVEL TPL_HIGH_LEVEL

#define EFI_CHECK(x) {EFI_STATUS status = (x);if(status!=EFI_SUCCESS)return status;}
#define COUNTOF(x) (sizeof(x)/sizeof((x)[0]))

#define EfiAppendDevicePathNode             DPAddNode
// redefined in core 4.05 #define DPLENGTH(x)                       ((x).Length)

void cp( UINT8 code);

#define EfiCreateEventLegacyBoot CreateLegacyBootEvent

VOID    USB_SmiQueuePut(VOID*);

typedef struct
{
    UINT8   Down;
    UINT8   KeyCode;
} USB_KEY;

#define MAX_KEY_ALLOWED 32

typedef struct
{
    USB_KEY buffer[MAX_KEY_ALLOWED + 1];
    UINT8   bHead;
    UINT8   bTail;
} USB_KB_BUFFER;

EFI_STATUS  USBSB_InstallSmiEventHandlers(VOID);
EFI_STATUS	USBSB_InstallXhciHwSmiHandler(VOID);
EFI_STATUS	USBSB_InstallUsbIntTimerHandler(VOID);
EFI_STATUS	USBSB_UninstallTimerHandlers(VOID);

#endif      // __AMI_H

//****************************************************************************
//****************************************************************************
//**                                                                        **
//**             (C)Copyright 1985-2016, American Megatrends, Inc.          **
//**                                                                        **
//**                          All Rights Reserved.                          **
//**                                                                        **
//**                 5555 Oakbrook Pkwy, Norcross, GA 30093                 **
//**                                                                        **
//**                          Phone (770)-246-8600                          **
//**                                                                        **
//****************************************************************************
//****************************************************************************
