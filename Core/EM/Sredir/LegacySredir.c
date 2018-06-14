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
//**********************************************************************
// $Header: /Alaska/SOURCE/Modules/Legacy Serial Redirection/LegacySredir.c 51    11/27/14 12:38a Srilathasc $
//
// $Revision: 51 $
//
// $Date: 11/27/14 12:38a $
//****************************************************************************
//****************************************************************************
// Revision History
// ----------------
// $Log: /Alaska/SOURCE/Modules/Legacy Serial Redirection/LegacySredir.c $
// 
// 51    11/27/14 12:38a Srilathasc
// [TAG]  		EIP193345
// [Category]  	Improvement
// [Description]  	Sredir bin module needs to be modified to make use ACPI
// timer instead of 8254 timer
// [Files]  		Sredir.asm, LegacySredir.c, csm.sdl, Sredir,bin
// 
// 50    11/18/14 5:22a Anandakrishnanl
// [TAG]  		EIP192802
// [Category]  	Improvement
// [Description]  	Support for legacy redirection by UART polling is added
// for platforms in which serial port does not support IRQ on PIC Mode.
// [Files]  		LegacySredir.c LegacySredir.h,LegacySredir.sdl
// 
// 49    12/20/13 6:53a Divyac
// [TAG]  		EIP147701 
// [Category]  	Bug Fix
// [Severity]  	Important
// [Symptom]  	DOS redirection is not working in Shark Bay platform.
// [RootCause]  	Wrong Value assigned to CTRLH_MAPPING  Macro in
// LegacySredir.c
// [Solution]  	Assigned Value to CTRLH_MAPPING Macro, according to the
// value defined for CTRLH_MAPPING  Equate  in Sredir.asm 
// [Files]  		LegacySredir.c
// 
// 48    12/09/13 5:23a Divyac
// [TAG]  		EIP129549 
// [Category]  	Improvement
// [Description]  	Serial Redirection has dependency on Amilegacy16.bin
// [Files]  		LegacySredir.c, LegacySredir.h, OR_MOD.EQU, SREDIR.ASM
// 
// 47    12/09/13 4:45a Divyac
// [TAG]  		EIP146051 
// [Category]  	Improvement
// [Description]  	Refresh Key needs to be configured via SDL token for
// Legacy Serial Redirection.
// [Files]  		LegacySredir.c, LegacySredir_Setup.C, LegacySredir.h,
// Sredir.bin
// 
// 46    9/17/13 5:31a Rameshr
// [TAG]  		EIP134807
// [Category]  	Bug Fix
// [Severity]  	Important
// [Symptom]  	Redirection doesn't work with MMIO PCI device
// [RootCause]  	CTRLH_MAPPING  and MMIO_WORD_WIDTH both the equate uses
// the same values.
// [Solution]  	Modified CTRLH_MAPPING equate value 
// [Files]  		LegacySredir.c, Sredir.bin
// 
// 45    5/30/13 2:46a Rameshr
// [TAG]  		EIP123584
// [Category]  	Bug Fix
// [Severity]  	Minor
// [Symptom]  	when active PCI console redirectioin support, keyboard not
// response at POST stage
// [RootCause]  	CSM16 region status changed by Legacy Serial Redirection
// driver
// [Solution]  	CSM16 region unlocked and locked again only when the
// Legacy OS booting happens
// [Files]  		Legacysredir.c
// 
// 44    5/29/13 8:51a Srikantakumarp
// [TAG]  		EIP122394
// [Category]  	Bug Fix
// [Severity]  	Normal
// [Symptom]  	0xE0000~0xEFFFF was overwrite by Legacy Serial Redirection
// module.
// [RootCause]  	LegacySerialRedirection driver assumed that
// SerialBootcall.asm will be the first entry in CsmOem16Functions which
// was wrong.
// [Solution]  	Added a Signature check code for SerialBootCall.asm and
// SredirBootFail.asm before it writes to the memory location
// 0xE0000~0xEFFFF.
// [Files]  		LegacySredir.c, SerialBootCall.asm, SredirBootFail.asm
// 
// 43    9/17/12 7:27a Srikantakumarp
// [TAG]  		EIP101094
// [Category]  	Improvement
// [Description]  	Generic change for sdl token to control the ctrl+H key
// [Files]  		LegacySredir.c, LegacySredir.sdl, Sredir.asm
// 
// 42    7/27/12 5:00a Rajeshms
// [TAG]  		EIP95246
// [Category]  	Improvement
// [Description]  	RTS is used to control redirection flow when
// FlowControl is enabled. When RTS is disabled (host not ready to accept
// data) Redirection is disabled and when RTS is enabled (i.e CTS is set)
// Redirection is enabled again. 
// [Files]  		Terminal.sdl, SerialIo.c, LegacySredir.c, SREDIR.ASM,
// INT10REDIR.ASM, GRAPHREDIR.ASM
// 
// 41    3/29/12 11:51p Rajeshms
// [TAG]  		EIP84341
// [Category]  	Improvement
// [Description]  	Added Separate PCI_UART_INPUT_CLOCK token for setting
// the Clock for PCI Serial UART.
// [Files]  		Terminal.sdl, TerminalSetup.c, SerialIo.c, LegacySredir.c,
// LegacySredir_Setup.c
// 
// 40    2/29/12 11:37p Rameshr
// [TAG]  		EIP82480
// [Category]  	Bug Fix
// [Severity]  	Important
// [Symptom]  	System does not boot to Legacy Devices when Launch Video
// OpRom DISABLED
// [RootCause]  	Temp buffer address is not correct
// [Solution]  	Redirection uses the 0x9F000 are temp buffer to save the
// Video data. It should have been calculated in runtime based on the Base
// memory allocated for sredir.bin
// [Files]  		Legacysredir.c, LegacySredir.h
// 
// 39    2/27/12 5:48a Jittenkumarp
// [TAG]  		EIP81401 
// [Category]  	New Feature
// [Description]  	Select Redirection After BIOS POST as BootLoader in
// serial redirection, the behaviour is not same as Core8.
// [Files]  		LegacySredir.c, LegacySredir.mak, LegacySredir.sdl,
// LegacySredir_Setup.c, LegacySredir.h ,SerialBootCall.asm,
// SredirBootFail.asm,GRAPHREDIR.ASM, INT10REDIR.ASM, OR_MOD.EQU,
// SREDIR.ASM
// 
// 38    12/28/11 10:52p Rajeshms
// [TAG]  		EIP65051
// [Category]  	Improvement
// [Description]  	Data passing between EFI to Legacy has been changed in
// Legacy console redirection as we are running out of registers to pass
// parameters from EFI to Legacy.
// [Files]  		LegacySredir.c, LegacySredir.h, LegacySredir_Setup.C,
// SREDIR.ASM, OR_MOD.ASM, OR_MOD.EQU
// 
// 37    12/12/11 2:06a Jittenkumarp
// [TAG]  		EIP75982
// [Category]  	New Feature
// [Description]  	Redirection After BIOS POST item on the setup menu
// [Files]  		Terminal.sd, Terminal.uni, LegacySredir.c,
// LegacySredir_Setup.c
// 
// 36    12/12/11 12:12a Jittenkumarp
// [TAG]  		EIP75169 
// [Category]  	Improvement
// [Description]  	 Added ESC sequence support for Legacy Serial
// Redirection.
// [Files]  		LegacySredir.c, SREDIR.ASM, KEYREDIR.ASM
// 
// 35    11/10/11 3:44a Rameshr
// [TAG]  		EIP64383
// [Category]  	Bug Fix
// [Severity]  	Minor
// [Symptom]  	System will hang when dash redirection disconnect in legacy
// environment
// [RootCause]  	Waiting for the Transmitter Holding Register Empty bit to
// set to send the next data.
// [Solution]  	After retry count is reached, redirection disabled.
// [Files]  		Graphredir.asm , Or_mod.asm , Sredir.asm , Legacysredir.c 
// 
// 34    11/09/11 11:52p Rajeshms
// [TAG]- EIP 63665
// [Category]-IMPROVEMENT
// [Description]- Install Linux(Legacy OS) through remote. Some Linux
// versions are forced to text mode to redirect and some are redirected in
// graphics mode itself. It might not work for all the Linux versions as
// the Linux kernel's behave differently.
// [Files]- Terminal.sdl, Terminal.uni, Terminal.sd, LegacySredir.c,
// LegacySredir.h, LegacySredir_Setup.c, GRAPHREDIR.ASM, INT10REDIR.ASM,
// OR_MOD.ASM, OR_MOD.EQU, SREDIR.ASM
// 
// 33    8/16/11 4:45p Davidd
// [TAG]           EIP55337
// [Category]      New Feature
// [Description]   Add optional code to clear keyboard buffer at
// ReadyToBoot in Legacy Serial Redirection driver
// [Files]         LegacySredir.c
//                 LegacySredir.h
//                 LegacySredir.sdl
//                 Sredir.asm
// 
// 32    8/05/11 4:19a Rameshr
// [TAG] - EIP 66389
// [Category]- BUG FIX
// [Severity]- Minor
// [Symptom] - System hangs at 0xAE when legacy serial redirection is
// enable
// [RootCause]- Before Legacy console redirection allocates the base
// memory, some other driver allocates the base memory. So legacy console
// redirection memory location moved down. But Sredir.bin thinks that seg
// address of the sredir.bin is 0x9cc00. So system is hanging when we call
// 0x9cc00:offset, as this region is not used to copy the sredir.bin 
// [Solution] - insteed of using the segment address from bin( hardcoded
// value), Used the segment address we get it in runtime
// [Files] - Legacysredir.c
// 
// 31    7/13/11 2:38a Rajeshms
// [TAG]- EIP 36444
// [Category]- New Feature
// [Description]- Add Setup option for Various Putty keyPad support in
// Legacy console redirection driver
// [Files]- LegacySredir.c, LegacySredir.h, LegacySredir_Setup.C,
// SREDIR.ASM, KEYREDIR.ASM, OR_MOD.EQU, SREDIR.MAK
// 
// 30    6/17/11 4:42a Rameshr
// [TAG] - EIP 47188
// [Category]- IMPROVEMENT
// [Description]- MMIO COM device access width SDL token support added 
// [Files] - legacysredir.c, LegacySredirSmm.c, LegacySredir_setup.c
// 
// 29    6/14/11 5:37a Rameshr
// [TAG]- EIP 58140
// [Category]- New Feature
// [Description]- Add Setup option for Vt-UTF8 combo key support in Legacy
// console redirection driver 
// [Files]- Sredir.asm, Legacysredir.c, Legacysredir.h,
// Legacysredir_setup.c
// 
// 28    2/11/11 4:58a Rameshr
// [TAG]- EIP 53465
// [Category]-IMPROVEMENT
// [Description]- gLegacySredir variable name used as global and local
// variable. Changed the Local Variable name
// [Files]- LegacySredir.c 
// 
// 27    1/10/11 5:06a Rameshr
// [TAG] - EIP 47188
// [Category]- IMPROVEMENT
// [Description]- MMIO COM device access width SDL token support added 
// [Files] - legacysredir.c, Sredir.asm
// 
// 26    1/04/11 11:40p Rameshr
// [TAG] - EIP 48120
// [Category]- BUG FIX
// [Severity]- Minor
// [Symptom] - Function key Ctrl + i do not work via serial redirection.
// [RootCause]- Crtl+I is mapped to tab key in the redirection module 
// [Solution] - Provided the SDL token for Ctrl+I key mapping. Tab and
// Ctrl+I can be selected through this sdl token 
// [Files] - Legacysredir.c, Legacysredir.sdl, Sredir.asm(Sredir.bin)
// 
// 25    9/24/10 1:37a Rameshr
// [TAG] - EIP 44133
// [Category]- BUG FIX & IMPROVEMENT
// [Severity]- Major
// [Symptom] - Flowcontrol and Terminal type is not working in Legacy
// console redirection 
// [RootCause] - Baud rate value overwrites the Flowcontrol and Terminal
// Type fields.
// [Solution] - BaudRate programming done in EFI driver. So removed the
// baud rate value passing into Sredir.bin
//              MMIO com device width added based on SDL token.
// [Files] - LegacySmmSredir.c , Legacysredir.c, Legacysredir.sdl
// 
// 24    6/04/10 2:01a Rameshr
// Sredir.bin Size increased.
// 
// 23    6/01/10 1:05a Rameshr
// Issue: Sredir.bin always allocated memory in basememory
// Solution: If the redirection is enabled, allocaed the base memory and
// copied the Sredir.bin 
// EIP 37831
// 
// 22    5/03/10 1:55a Rameshr
// Callback function added for read and write function of the Serial Port.
// EIP 37850
// 
// 21    5/03/10 1:21a Rameshr
// Issue:Need to handle different Base Hz values for SerialStatusCode,
// Terminal, and Legacy Serial Redirection.
// Solution: Moved Uart input clock into Core.sdl token and used in all
// the above modules.
// EIP: 37332
// 
// 20    4/13/10 4:13a Rameshr
// Recorder Mode support added
// EIP 36514
// Some of the MMIO COM port has non standard bits implemented. These bits
// are reset to 0 in Sredir.bin
// EIP 37123
// 
// 19    3/05/10 4:20a Rameshr
// MMIO COM device support added.
// EIP 33847
// 
// 18    2/03/10 12:58a Rameshr
// Int10 Workaround added based on SDL token. 
// EIP 33300
// 
// 17    11/26/09 5:16a Rameshr
// Legacy console redirection module size increased. So changing the base
// address.
// EIP:26405
// 
// 16    10/23/09 10:46a Yul
// EIP 24167 and EIP 26405
// Serial redirection selection of 80X24 or 80X25 implemented based on 
// setup question instead of BUILD token
// 
// 15    9/21/09 3:36p Rameshr
// compile Error in legacy sredir when using VS 2008
// EIP 27263
// 
// 14    6/29/09 12:11p Rameshr
// Coding Standard and File header updated.
// 
// 13    4/21/09 12:17p Rameshr
// Updated the Legacy console redirection to get the Databits,Parity and
// Stop bits from the Terminal Driver Setup option
// EIP20874-Legacy serial redirection is using hra coded values for
// Databits as 8, Parity as None and Stop bit as 1
// 
// 12    4/20/09 12:58p Rameshr
// EIP 20251 -Ebda value inside Legacy Serial Redirection need to be
// Dynamic 
// 
// Removed Unwanted code and updated with proper comments on Sredir.bin
// Memory allocation.
// 
// 11    3/09/09 3:09p Rameshr
// Symptom: PXE boot messages are not displayed on local console.
// Solution: Without Disabling the Legacy console redirection, Enable
// redirection is not processed.
// EIP:19089
// 
// 10    12/24/08 3:51p Rameshraju
// 
// 9     12/16/08 2:49a Iminglin
// (EIP17767) The function value of FindLegacySreDirTable for compliance.
// 
// 8     11/20/08 12:50p Rameshraju
// SDL parameters passed from EFI to 16bit code
// Added code to display whole screen before disalbing the redirection.
// This is done based on the SDL token. default set to disabled.
// 
// 7     29/10/08 4:27p Anandakrishnanl
// Added Status Check For GetSetupValuesForLegacySredir so that Legacy
// Serial Redirection Can be Enabled Based  on Setup Options.
// 
// 6     10/24/08 11:21a Rameshraju
// Disable redirection is called only when the enabled redirection call is
// done.
// 
// 5     9/10/08 12:44p Pats
// Reverted method for reserving memory for Sredir.bin to previous method
// (AllocateEbda not used).
// 
// 4     8/26/08 10:01a Pats
// Removed call to GetInterruptAddress function since it is not used.
// 
// 3     8/20/08 6:52p Pats
// Fixed bug of setup values being loaded into uninitialized null pointer.
// Changed EBDA allocation to use AllocateEbda function.
// 
// 2     4/17/07 4:41a Rameshraju
// PCIserial support added
// 
//****************************************************************************
//****************************************************************************
//<AMI_FHDR_START>
//****************************************************************************
//
// Name:	LegacySredir.C
//
// Description:	Serial Redirection Compatibility Support Module entry point and interface functions
//****************************************************************************
//<AMI_FHDR_END>

//
// Disabling the warnings.
//
#pragma warning (disable : 4100 )

#pragma warning (disable : 4306 ) 
#include    "Token.h"
#include    "Protocol/LoadedImage.h"
#include    "Protocol/LegacySredir.h"
#include    "Protocol/LegacyBios.h"
#include    "Protocol/LegacyBiosExt.h"
#include    "AmiDxeLib.h"


#ifndef     SERIAL_WRITE_ERROR_CHECK
#define     SERIAL_WRITE_ERROR_CHECK 1
#ifndef     MAXIMUM_SERIAL_WRITE_ERROR_COUNT
#define     MAXIMUM_SERIAL_WRITE_ERROR_COUNT 10
#endif
#endif

#ifndef     MAX_FAILURES_ALLOWED
#define     MAX_FAILURES_ALLOWED 5
#endif


#define     CONVENTIONAL_MEMORY_TOP     0xA0000  
#define     SREDIR_BIN_SIZE             0x3C00

//
//Parameter passed to sredir.bin
//
#define     DISPLAY_SCREEN              0x0001
#define     INT10_WORKAROUND            0x0002
#define     MMIO_DEVICE                 0x0004   
#define     SERIAL_READWRITE_CALLBACK   0x0008
#define     CTRLI_MAPPING               0x0010
#define     MMIO_BYTE_WIDTH             0x0000
#define     MMIO_WORD_WIDTH             0x0020
#define     MMIO_DWORD_WIDTH            0x0040
#define     SERIAL_ERROR_CHECK          0x0080
#define     ESC_SEQUENCES               0x0100
#define     CTRLH_MAPPING               0x0200

EFI_GUID    gEfiLoadedImageGuid        = EFI_LOADED_IMAGE_PROTOCOL_GUID;
EFI_GUID    gEfiFirmwareVolumeProtocol = EFI_FIRMWARE_VOLUME_PROTOCOL_GUID;

UINT32      Int10hAddress;
UINT32      Int0chAddress;
UINT32      Int14hAddress;
VOID        *EmbeddedRom;
UINTN       EmbeddedRomSize; 

AMI_LEGACYSREDIR_TABLE      *mLegacySreDirHeader;
EFI_EVENT                   SreDir;
BOOLEAN                     RedirectionStatus=FALSE;
UINTN                       gSreDirImageStart=0;
EFI_LEGACY_BIOS_PROTOCOL    *pLegacy=NULL;
BOOLEAN                     IsCopied = FALSE;
BOOLEAN                     IsDataCopied = FALSE;
extern BOOLEAN              IsPciDevice;
BOOLEAN                     LegacyOSBooting=FALSE;

//
// The GetSetupValuesForLegacySredir procedure to get the setup values
//
extern  EFI_STATUS GetSetupValuesForLegacySredir(
    OUT AMI_COM_PARAMETERS *AmiComParameters
);

EFI_STATUS 
InitilizeNonCommonSerialRegsiters(
    IN AMI_COM_PARAMETERS *AmiComParameters
);


EFI_STATUS
EnableLegacySredir (
    IN AMI_LEGACY_SREDIR_PROTOCOL   * This
);

EFI_STATUS
DisableLegacySredir (
    IN AMI_LEGACY_SREDIR_PROTOCOL   * This
);

EFI_STATUS
LegacySreDirInSmmFunction(
    IN EFI_HANDLE                ImageHandle,
    IN EFI_SYSTEM_TABLE          *SystemTable
 );

EFI_STATUS FindLegacySredirRom(
    UINT16 ModuleId, UINT16 VendorId, UINT16 DeviceId,
    VOID **ImageStart, UINT32 *ImageSize
);

EFI_STATUS DataCopiedToCsm16Function(
    UINTN   StructStartAddress,
    AMI_COM_PARAMETERS     *AmiComParameters
);

//
// AMI_LEGACY_SREDIR_PROTOCOL 
//
AMI_LEGACY_SREDIR_PROTOCOL gLegacySredir = {
    EnableLegacySredir,
    DisableLegacySredir
};
#define DLAB_BIT            1   
#define LSR_OFFSET          0x05
#define LCR_OFFSET          0x03
#define DIV_MSB             0x01
#define DIV_LSB             0

//
// ACPI PM timer signature,for 'TM' the ASCII code is 0x544D
// the MSB bit of the signature denotes 24bit/32bit timer
//
#if ACPI_SUPPORT
#if FACP_FLAG_TMR_VAL_EXT
#define TIMER_SIGNATURE_32BIT 0xD44D0000
#else
#define TIMER_SIGNATURE_24BIT 0x544D0000
#endif
#endif

//<AMI_PHDR_START>
//----------------------------------------------------------------------------
// Name:        DataCopiedToCsm16Function
//
// Description: This function copies the segment and offset address of sredir.bin
//
// Input:       UINTN                  StructStartAddress
//              AMI_COM_PARAMETERS     *AmiComParameters
//	
//
// Output:      EFI_SUCCESS
//----------------------------------------------------------------------------
//<AMI_PHDR_END>


EFI_STATUS DataCopiedToCsm16Function(
    IN  UINTN                  StructStartAddress,
    IN  AMI_COM_PARAMETERS     *AmiComParameters
)
{
    EFI_STATUS                      Status;
    UINTN                           ImageSize = 0x10;
    UINT32                          LockUnlockAddr, LockUnlockSize; 
    UINT16                          *Addr;
    UINT32                          Addr16;
    EFI_LEGACY_BIOS_EXT_PROTOCOL    *BiosExtensions = NULL;
    UINT8                           *RpSBCSig = "$SBC";
    UINT8                           *RpSBFSig = "$SBF";
    //
    // Check Data already copied into CSM16 call backfunction
    //
    if(IsDataCopied) {
        return EFI_SUCCESS;
    }

    //
    //Data copied into CSM16 callback function
    //
    IsDataCopied=TRUE;

    Status = pBS->LocateProtocol(
                    &gEfiLegacyBiosExtProtocolGuid,\
                    NULL,\
                    &BiosExtensions);

    if (EFI_ERROR(Status)) 
        return Status;

    Status = BiosExtensions->Get16BitFuncAddress(
                                CSM16_OEM_BEFORE_CALL_BOOT_VECTOR, \
                                &Addr16);

    if (EFI_ERROR(Status)) 
        return Status;

    Status = BiosExtensions->UnlockShadow(
                                (UINT8*)Addr16, \
                                ImageSize, \
                                &LockUnlockAddr, \
                                &LockUnlockSize);

    ASSERT_EFI_ERROR(Status);


    while(Addr16 < 0xf0000)
    {
        if (!MemCmp((UINT8*)Addr16, RpSBCSig, 4))
        {
            Addr16 = Addr16+4;          // Skip the Signature "$SBC"
            Addr = (UINT16*) Addr16;
            *Addr =((StructStartAddress>>4) & 0xF000);
            Addr++;
            *Addr =(UINT16)StructStartAddress;
            Addr++;
            *Addr = (UINT16)(((UINT8 *)&(AmiComParameters->Flag)) - ((UINT8*)(AmiComParameters)));
            break;
        }
        Addr16++;
    }

    Status = BiosExtensions->Get16BitFuncAddress(
                                CSM16_OEM_ON_BOOT_FAIL, \
                                &Addr16);

    if (EFI_ERROR(Status)) 
        return Status;
    


    while(Addr16 < 0xf0000)
    {
        if (!MemCmp((UINT8*)Addr16, RpSBFSig, 4))
        {
            Addr16 = Addr16+4;          // Skip the Signature "$SBF"
            Addr = (UINT16*) Addr16;
            *Addr =((StructStartAddress>>4) & 0xF000);
            Addr++;
            *Addr =(UINT16)StructStartAddress;
            Addr++;
            *Addr = (UINT16)(((UINT8 *)&(AmiComParameters->Flag)) - ((UINT8*)(AmiComParameters))) ;
            break;            
        }
        Addr16++;
    }
    BiosExtensions->LockShadow(LockUnlockAddr, LockUnlockSize);

    return EFI_SUCCESS;
}

//<AMI_PHDR_START>
//----------------------------------------------------------------------------
// Name:        CopySredirBinIntoBaseMemory
//
// Description: This function copies the Sredir.bin into Base Memory
//
// Input:       This
//              Indicates the AMI_LEGACY_SREDIR_PROTOCOL instance.
//
//
// Output:      EFI_SUCCESS
//----------------------------------------------------------------------------
//<AMI_PHDR_END>

EFI_STATUS
CopySredirBinIntoBaseMemory (
    IN AMI_LEGACY_SREDIR_PROTOCOL   * This
)
{

    VOID                        *SreDirImageStart = NULL;
    UINT32                      SreDirImageSize    = 0;
    UINT16                      EbdaSeg = (UINT16)(*(UINT16*)0x40E);
    UINT8                       *EbdaAddress = (UINT8*)((UINTN)EbdaSeg<<4);
    UINT32                      EbdaSize = (*EbdaAddress)<<10;
    UINT32                      NewEbdaAdd;
    UINT32                      NewEbdaSeg;
    EFI_STATUS                  Status;


    //
    // Check Sredir.bin already copied into Memory
    //
    if(IsCopied) {
        return EFI_SUCCESS;
    }

    //
    //Sredir.bin copied into Base Memory
    //
    IsCopied=TRUE;

    //
    // Sredir.bin is placed in below A0000. It will not be reported as EBDA memory. 
    // So sredir place will not be changed when there is allocateEbda.
    //
    if(EbdaSeg== 0) { 
        return EFI_NOT_FOUND;
    }

    //
    //New EBDA Address will be EbdaAddress - Sredir.bin
    //
    NewEbdaAdd = (EbdaSeg<<4)-SREDIR_BIN_SIZE;        //To allocate memory for sredir.bin
    NewEbdaSeg = NewEbdaAdd>>4;

    //
    //We are taking memory for the Sredir.bin from the base memory. So adjust the Base Memory
    //
    *(UINT16*)0x413 = ((*(UINT16*)0x413) - (SREDIR_BIN_SIZE >> 10));

    //
    //Update the New EBDA address
    //
    *(UINT16*)0x40e = (UINT16)NewEbdaSeg;

    //
    //Move the OLD ebda data to new EBDA area. We have not changed the EBDA Size here. This makes
    //Sredir.bin area will not be moved any where.it means Sredir.bin is not placed under EBDA area.
    //
    pBS->CopyMem((VOID*)NewEbdaAdd,(VOID*)(EbdaSeg<<4),EbdaSize);

   Status = FindLegacySredirRom(SREDIR_MODULEID, SREDIR_VENDORID, SREDIR_DEVICEID,&SreDirImageStart, &SreDirImageSize);
    if (EFI_ERROR(Status)) {
        return Status;
    }
    
    //
    // Copy the Sredir.bin Base Memory.
    //
    pBS->CopyMem((VOID*)(NewEbdaAdd+EbdaSize), SreDirImageStart, SreDirImageSize);
    gSreDirImageStart = (UINTN)(NewEbdaAdd+EbdaSize);
   
    
    return EFI_SUCCESS;

}

//<AMI_PHDR_START>
//----------------------------------------------------------------------------
// Name:        InitilizeBuadRate
//
// Description: This Function is used to Initilize the Baud Rate of the COM port 
//
// Input:       AMI_COM_PARAMETERS AmiComParameters
//
//
// Output:      Com port Baud Rate Initilized.
//----------------------------------------------------------------------------
//<AMI_PHDR_END>

EFI_STATUS
InitilizeBuadRate(
    OUT AMI_COM_PARAMETERS *AmiComParameters
)
{

    UINT8   Data8;
    UINT16  Divisor;
    UINTN   Remainder;
    UINTN   UartInputClock;

    if( IsPciDevice ) {
#ifdef PCI_UART_INPUT_CLOCK
        UartInputClock = PCI_UART_INPUT_CLOCK;
#else
    //
    // Set the default value((24000000/13)MHz input clock)
    // if the PCI_UART_INPUT_CLOCK SDL token is not present.
    //
        UartInputClock=1843200;
#endif
    } else {
#ifdef UART_INPUT_CLOCK
        UartInputClock=UART_INPUT_CLOCK;
#else
    //
    // Set the default value((24000000/13)MHz input clock)
    // if the UART_INPUT_CLOCK SDL token is not present.
    //
        UartInputClock=1843200;
#endif
    }

    //
    // Compute the baud rate divisor.
    //
    Divisor = (UINT32) Div64 (UartInputClock,
                                ((UINT32)AmiComParameters->Baudrate * 16), 
                                &Remainder);
    if ( Remainder ) {
        Divisor += 1;
    }
    
    if ((Divisor == 0) || (Divisor & 0xffff0000)) {
        return EFI_INVALID_PARAMETER;
    }

    //
    // Check for the MMIO device. If it's MMIO device do MMIO access to 
    // Read and Write to the COM port Regsiters. Otherwise use IO access
    // to Read and Write to Com port Registers.
    //    
    if(AmiComParameters->MMIOBaseAddress != 0) {
        //
        // Programm Serial port. 
        // Set Line Control Register (LCR)
        //
        Data8 = DLAB_BIT << 7;

#if COM_MMIO_WIDTH == 4
        *(UINT32*)(AmiComParameters->MMIOBaseAddress+(LCR_OFFSET*COM_MMIO_WIDTH))=(UINT32)Data8;
#else
    #if COM_MMIO_WIDTH == 2
            *(UINT16*)(AmiComParameters->MMIOBaseAddress+(LCR_OFFSET*COM_MMIO_WIDTH))=(UINT16)Data8;
    #else
            *(UINT8*)(AmiComParameters->MMIOBaseAddress+(LCR_OFFSET*COM_MMIO_WIDTH))=(UINT8)Data8;
    #endif
#endif  
    
        //
        //Program the Baud Rate
        //

#if COM_MMIO_WIDTH == 4
        *(UINT32*)(AmiComParameters->MMIOBaseAddress+(DIV_LSB*COM_MMIO_WIDTH))=(UINT32)Divisor & 0xFF;
        *(UINT32*)(AmiComParameters->MMIOBaseAddress+(DIV_MSB*COM_MMIO_WIDTH))=(UINT32)Divisor >> 8;
#else
    #if COM_MMIO_WIDTH == 2
            *(UINT16*)(AmiComParameters->MMIOBaseAddress+(DIV_LSB*COM_MMIO_WIDTH))=(UINT16)Divisor & 0xFF;
            *(UINT16*)(AmiComParameters->MMIOBaseAddress+(DIV_MSB*COM_MMIO_WIDTH))=(UINT16)Divisor >> 8;

    #else
            *(UINT8*)(AmiComParameters->MMIOBaseAddress+(DIV_LSB*COM_MMIO_WIDTH))=(UINT8)Divisor & 0xFF;
            *(UINT8*)(AmiComParameters->MMIOBaseAddress+(DIV_MSB*COM_MMIO_WIDTH))=(UINT8)(Divisor >> 8);
    #endif
#endif  

        //
        // Clear DLAB bit in LCR
        //
        Data8 &= ~((UINT8)DLAB_BIT << 7);

#if COM_MMIO_WIDTH == 4
        *(UINT32*)(AmiComParameters->MMIOBaseAddress+(LCR_OFFSET*COM_MMIO_WIDTH))=(UINT32)Data8;
#else
    #if COM_MMIO_WIDTH == 2
            *(UINT16*)(AmiComParameters->MMIOBaseAddress+(LCR_OFFSET*COM_MMIO_WIDTH))=(UINT16)Data8;
    #else
            *(UINT8*)(AmiComParameters->MMIOBaseAddress+(LCR_OFFSET*COM_MMIO_WIDTH))=(UINT8)Data8;
    #endif
#endif  

    } else {
        //
        // Programm Serial port. 
        // Set Line Control Register (LCR)
        //
        Data8 = DLAB_BIT << 7;
        IoWrite8(AmiComParameters->BaseAddress + LCR_OFFSET, Data8 );
    
        //
        //Program the Baud Rate
        //
        IoWrite8(AmiComParameters->BaseAddress + DIV_LSB, Divisor & 0xFF);
        IoWrite8(AmiComParameters->BaseAddress + DIV_MSB, Divisor >> 8);
    
        //
        // Clear DLAB bit in LCR
        //
        Data8 &= ~((UINT8)DLAB_BIT << 7);
        IoWrite8(AmiComParameters->BaseAddress + LCR_OFFSET, Data8 );
    }

    return EFI_SUCCESS;
}

//<AMI_PHDR_START>
//----------------------------------------------------------------------------
// Name:        EnableLegacySredir
//
// Description: This function is used for enabling the legacy Serial Redirection
//              This function contains calls for Intialising Serial ports and 
//              hooking the interrupts which are required for purpose of Redirection
//
// Input:       This
//              Indicates the AMI_LEGACY_SREDIR_PROTOCOL instance.
//
//
// Output:      EFI_SUCCESS
//----------------------------------------------------------------------------
//<AMI_PHDR_END>

EFI_STATUS
EnableLegacySredir (
    IN AMI_LEGACY_SREDIR_PROTOCOL   * This
)
{
    EFI_STATUS                      Status = EFI_SUCCESS;
    EFI_IA32_REGISTER_SET           RegSet;
    AMI_COM_PARAMETERS              AmiComParameters;
    UINT32                          SdlParameters=0;
    AMI_COM_PARAMETERS              *SredirSetupComParameters;
    UINTN                           StructStartAddress = NULL;
    
    if(RedirectionStatus) {
        return EFI_NOT_FOUND;
    }

    if(pLegacy==NULL) {
        Status = pBS->LocateProtocol(&gEfiLegacyBiosProtocolGuid, NULL, &pLegacy);
        if (EFI_ERROR(Status)) {
            return Status;
        }
    }

    //
    //Getting Setup values from terminal module
    //
    Status = GetSetupValuesForLegacySredir(&AmiComParameters);

    if(EFI_ERROR(Status)){
        return Status;
    }
    //
    //Copy the Sredir.bin into Base Memory
    //
    Status=CopySredirBinIntoBaseMemory(This);

    if(EFI_ERROR(Status)){
        return Status;
    }

    //
    //Serial Redirection starting Address
    //
    mLegacySreDirHeader = (AMI_LEGACYSREDIR_TABLE*)gSreDirImageStart;

    if (mLegacySreDirHeader == NULL) return EFI_NOT_FOUND;

#if DISPLAY_WHOLE_SCREEN
    SdlParameters |= DISPLAY_SCREEN;
#endif
#if TRAP_INT10_WORKAROUND
    SdlParameters |= INT10_WORKAROUND;
#endif
#if SERIAL_READ_WRITE_CALLBACK
    SdlParameters |= SERIAL_READWRITE_CALLBACK;
#endif
#if CTRLI_KEY_MAPPING
    SdlParameters |= CTRLI_MAPPING;
#endif
#if CTRLH_KEY_MAPPING
    SdlParameters |= CTRLH_MAPPING;
#endif
#if SERIAL_WRITE_ERROR_CHECK
    SdlParameters |= SERIAL_ERROR_CHECK;
#endif
#if OEM_ESC_SEQUENCES
    SdlParameters |= ESC_SEQUENCES;
#endif
#if COM_MMIO_WIDTH == 1
    SdlParameters |= MMIO_BYTE_WIDTH;
#endif
#if COM_MMIO_WIDTH == 2
    SdlParameters |= MMIO_WORD_WIDTH;
#endif
#if COM_MMIO_WIDTH == 4
    SdlParameters |= MMIO_DWORD_WIDTH;
#endif


    Status=InitilizeBuadRate(&AmiComParameters);

    if(EFI_ERROR(Status)){
        return Status;
    }

    //
    //Initilize the Non Standard Serial Port Regsiters.
    //
    Status = InitilizeNonCommonSerialRegsiters(&AmiComParameters);

    if(EFI_ERROR(Status)){
        return Status;
    }

    if(AmiComParameters.MMIOBaseAddress != 0) {
        SdlParameters |= MMIO_DEVICE;
        AmiComParameters.BaseAddress = 0;
        AmiComParameters.SwSMIValue = LEGACY_SREDIR_SWSMI;
#if defined(SW_SMI_IO_ADDRESS)
        AmiComParameters.SwSMIPort = SW_SMI_IO_ADDRESS;
#endif
    } 
    

    AmiComParameters.SdlParameters = SdlParameters;

    AmiComParameters.SredirBinSize=SREDIR_BIN_SIZE;
    AmiComParameters.RefreshScreenKey = REFRESH_SCREEN_KEY;
    AmiComParameters.UartPollingRedirection = UART_POLLING_REDIRECTION;

    //
    // Transfer the Setup Values and Com Parameters from EFI to Legacy.
    //

    SredirSetupComParameters = (AMI_COM_PARAMETERS  *)(gSreDirImageStart + (mLegacySreDirHeader->SreDirEfiToLegacyOffset));

    pBS->CopyMem((VOID*)SredirSetupComParameters, (VOID*)&AmiComParameters, sizeof(AMI_COM_PARAMETERS));

    StructStartAddress = (UINTN )SredirSetupComParameters;

    if(LegacyOSBooting) {
        Status=DataCopiedToCsm16Function(StructStartAddress, &AmiComParameters);

        if(EFI_ERROR(Status)){
            return Status;
        }
    }

    pBS->SetMem(&RegSet, sizeof (EFI_IA32_REGISTER_SET), 0);
    RegSet.X.AX = LEGACY_SreDirInitializeSerialPort; 

    RegSet.X.BX = MAXIMUM_SERIAL_WRITE_ERROR_COUNT;
    RegSet.X.CX = MAX_FAILURES_ALLOWED;
#if ACPI_SUPPORT
    #if FACP_FLAG_TMR_VAL_EXT
        RegSet.E.EDX = TIMER_SIGNATURE_32BIT;
    #else
        RegSet.E.EDX = TIMER_SIGNATURE_24BIT;
    #endif
#if ACPI_TIMER_IN_LEGACY_SUPPORT
     RegSet.X.DX = PM_TMR_BLK_ADDRESS;
#else
    RegSet.X.DX = 0;
#endif
#endif
  
    Status = pLegacy->FarCall86(pLegacy, 
             (UINT16)(gSreDirImageStart>>4), 
             mLegacySreDirHeader->SreDirOffset, 
             &RegSet, 
             NULL, 
             0);

    if(EFI_ERROR(Status)) {
        return Status;
    }
    
    pBS->SetMem(&RegSet, sizeof (EFI_IA32_REGISTER_SET), 0);
    RegSet.X.AX = LEGACY_SerialRedirection;  


    Status = pLegacy->FarCall86(pLegacy, 
             (UINT16)(gSreDirImageStart>>4), 
             mLegacySreDirHeader->SreDirOffset, 
             &RegSet, 
             NULL, 
             0);

    if(EFI_ERROR(Status)) {
        return Status;
    }

/*
    //
    // Intel wants to have interface to get the Original Int10, Int0c and Int14
    // Address. By default this code is disabled.
    //
    pBS->SetMem(&RegSet, sizeof (EFI_IA32_REGISTER_SET), 0);

    RegSet.X.AX = LEGACY_GetInterruptAddress;      //returns Int10,Int0c,Int14 original
                                                //vector address in EAX,EBX and ECX

    Status = pLegacy->FarCall86(pLegacy, 
             (UINT16)(gSreDirImageStart>>4), 
             mLegacySreDirHeader->SreDirOffset, 
             &RegSet, 
             NULL, 
             0);
         
    Int10hAddress = RegSet.E.EAX;
    Int0chAddress = RegSet.E.EBX;
    Int14hAddress = RegSet.E.ECX;
*/
    RedirectionStatus=TRUE;
    return Status;
}


//<AMI_PHDR_START>
//----------------------------------------------------------------------------
// Name:        DisableLegacySredir
//
// Description: This function is used to disable the Legacy Serial redirection
//              This function contains calls for functions which are used to 
//              release the interrupts which are used for Serial Redirection
//
// Input:       This
//              Indicates the AMI_LEGACY_SREDIR_PROTOCOL instance.
//
//
// Output:      EFI_SUCCESS
//
//----------------------------------------------------------------------------
//<AMI_PHDR_END>

EFI_STATUS
DisableLegacySredir (
    IN AMI_LEGACY_SREDIR_PROTOCOL   * This
)
{
    EFI_STATUS                  Status = EFI_SUCCESS;
    EFI_IA32_REGISTER_SET       RegSet;

    if(!RedirectionStatus) {
        return EFI_NOT_FOUND;
    }

    if(pLegacy==NULL) {
        Status = pBS->LocateProtocol(&gEfiLegacyBiosProtocolGuid, NULL, &pLegacy);
        if (EFI_ERROR(Status)) { 
            return Status;
        }
    }
 
    //
    //Serial Redirection starting Address
    //
    mLegacySreDirHeader = (AMI_LEGACYSREDIR_TABLE*)gSreDirImageStart;

    if (mLegacySreDirHeader == NULL) {
        return EFI_NOT_FOUND;
    }
 
    pBS->SetMem(&RegSet, sizeof (EFI_IA32_REGISTER_SET), 0);
    RegSet.X.AX = LEGACY_ReleaseSerialRedirection;  

    Status = pLegacy->FarCall86(pLegacy, 
             (UINT16)(gSreDirImageStart>>4), 
             mLegacySreDirHeader->SreDirOffset, 
             &RegSet, 
             NULL, 
             0);

    RedirectionStatus=FALSE;

    return Status;
}


//<AMI_PHDR_START>
//---------------------------------------------------------------------------
//
// Name:          FindLegacySredirRom
//
// Description:   This function searches for ROM within the data previously loaded
//          from the main FV image and returns its pointer and size.
//
// Input:         Module Id
//                Vendor Id
//                Device Id
//                Image Start Address
//                Image Size
//
// Output:        EFI_SUCCESS or EFI_NOT_FOUND
//
//---------------------------------------------------------------------------
//<AMI_PHDR_END>

EFI_STATUS FindLegacySredirRom(
    UINT16 ModuleId, UINT16 VendorId, UINT16 DeviceId,
    VOID **ImageStart, UINT32 *ImageSize
)
{
#pragma pack(push,1)
    typedef struct{
        UINT16 ModuleId, VendorId, DeviceId;
        UINT32 Size;
        } OPROM_HEADER;
#pragma pack(pop)

    OPROM_HEADER *Header;
        for(  Header = (OPROM_HEADER*)EmbeddedRom
                ; (UINT8*)Header<(UINT8*)EmbeddedRom+EmbeddedRomSize
                ; Header = (OPROM_HEADER*)((UINT8*)(Header+1)+Header->Size)
            )
        {
                if (    Header->ModuleId==ModuleId 
                        && Header->VendorId==VendorId
                        && Header->DeviceId==DeviceId
                   )
                {
                        *ImageStart = Header+1;
                        *ImageSize=Header->Size;
                        return EFI_SUCCESS;
                }
        }
        return EFI_NOT_FOUND;
}

//<AMI_PHDR_START>
//---------------------------------------------------------------------------
//
// Name:          Legacy_OS_SerialRedirection
//
// Description:   This function is used for Legacy Serial Redirection
//    
// Input:         EFI_Hanlde - Image Handle
//                EFI_System_Table - Pointer to System Table
//
// Output:        EFI_SUCCESS or EFI_NOT_FOUND
//
//---------------------------------------------------------------------------
//<AMI_PHDR_END>
EFI_STATUS Legacy_OS_SerialRedirection (
    IN EFI_EVENT        Event,
    IN VOID             *Context
)   
{

    EFI_STATUS                          Status;
    AMI_LEGACY_SREDIR_PROTOCOL          *LegacySredir=NULL;

    Status=pBS->LocateProtocol(&gAmiLegacySredirProtocolGuid, NULL, &LegacySredir);

    if(EFI_ERROR(Status)) {
        return Status;
    }

    LegacyOSBooting=TRUE;
    Status = LegacySredir->EnableLegacySredir(LegacySredir);

    return Status;

}

#if CLEAR_LEGACYSREDIR_KB_BUFFER_AT_READYTOBOOT
//<AMI_PHDR_START>
//---------------------------------------------------------------------------
//
// Name:        ClearKbCharBuffer
//
// Description:    Function to clear the Keyboard character buffer
//                (in the 16-bit Serial Redirection module)
//
// Input:       IN EFI_EVENT   Event
//              IN VOID        *Context
//
// Output:        None
//
//---------------------------------------------------------------------------
//<AMI_PHDR_END>
VOID
ClearKbCharBuffer (
    IN EFI_EVENT    Event,
    IN VOID         *Context
)
{
    EFI_IA32_REGISTER_SET       RegSet;

    //
    // Serial Redirection starting Address
    //
    mLegacySreDirHeader = (AMI_LEGACYSREDIR_TABLE*)gSreDirImageStart;

    if (mLegacySreDirHeader != NULL) {
        pBS->SetMem(&RegSet, sizeof (EFI_IA32_REGISTER_SET), 0);
        RegSet.X.AX = LEGACY_ClearKbCharBuffer;  

        pLegacy->FarCall86(pLegacy, 
                         mLegacySreDirHeader->SreDirSegment, 
                         mLegacySreDirHeader->SreDirOffset, 
                         &RegSet, 
                         NULL, 
                         0);
    }

    pBS->CloseEvent(Event);
}
#endif

//<AMI_PHDR_START>
//---------------------------------------------------------------------------
// Name:          LegacySreDirNotInSmmFunction
//
// Description:   Legacy Serial Redirection Non Smm entry point
//
// Input:         Standard EFI Image entry - EFI_IMAGE_ENTRY_POINT
//                EFI System Table - Pointer to System Table
//
// Output:        EFI_STATUS OR EFI_NOT_FOUND
//
//---------------------------------------------------------------------------
//<AMI_PHDR_END>

EFI_STATUS
LegacySreDirNotInSmmFunction(
    IN EFI_HANDLE                ImageHandle,
    IN EFI_SYSTEM_TABLE          *SystemTable
        )
{ 
    EFI_STATUS                         Status;
    EFI_LOADED_IMAGE_PROTOCOL       *LoadedImage;
    EFI_GUID                        gFile;
    EFI_FIRMWARE_VOLUME_PROTOCOL    *pFV;
    UINT32                          Authentication;
    EFI_HANDLE                      NewHandle;
#if CLEAR_LEGACYSREDIR_KB_BUFFER_AT_READYTOBOOT
    EFI_EVENT                        ReadyToBootEvent;
#endif


    Status = pBS->HandleProtocol(ImageHandle, &gEfiLoadedImageGuid, &LoadedImage);
    
    if (EFI_ERROR(Status)) {
        return Status;
    }

    //
    // Now we have EFI_DEVICE_PATH *LoadedImage->FilePath
    //
    gFile = ((MEDIA_FW_VOL_FILEPATH_DEVICE_PATH*)(LoadedImage->FilePath))->NameGuid;

    //
    // Get the Firmware Volume Protocol
    //
    Status = pBS->HandleProtocol (
                  LoadedImage->DeviceHandle, 
                  &gEfiFirmwareVolumeProtocol, 
                  &pFV
                  );

    if (EFI_ERROR(Status)) {
        return Status;
    }

    //
    // Read section with Legacy ROMs
    //
    EmbeddedRom = NULL;    // make ReadSection allocate memory
    EmbeddedRomSize = 0;
    Status = pFV->ReadSection (
                  pFV,
                  &gFile,
                  EFI_SECTION_RAW,
                  0,
                  &EmbeddedRom,
                  &EmbeddedRomSize,
                  &Authentication);
    if (EFI_ERROR(Status)) {
        return Status;
    }
    
    NewHandle = NULL;
    Status = pBS->InstallProtocolInterface (
                  &NewHandle,
                  &gAmiLegacySredirProtocolGuid,
                  EFI_NATIVE_INTERFACE,
                  &gLegacySredir
                  );
    if (EFI_ERROR(Status)) {
        return Status;
    }

#if CLEAR_LEGACYSREDIR_KB_BUFFER_AT_READYTOBOOT
    //
    // Register the ReadyToBoot event function to clear the Keyboard
    // character buffer (in the 16-bit Serial Redirection module)
    //
#if defined(EFI_EVENT_SIGNAL_READY_TO_BOOT) && (EFI_SPECIFICATION_VERSION < 0x20000)
    pBS->CreateEvent(
                    EFI_EVENT_SIGNAL_READY_TO_BOOT,
                    TPL_NOTIFY,
                    ClearKbCharBuffer,
                    NULL,
                    &ReadyToBootEvent
                    );
#else
    CreateReadyToBootEvent(TPL_CALLBACK,
                           ClearKbCharBuffer,
                           NULL,
                           &ReadyToBootEvent
                           );
#endif
#endif

#if defined(EFI_EVENT_SIGNAL_READY_TO_BOOT) && (EFI_SPECIFICATION_VERSION < 0x20000)
    Status = pBS->CreateEvent(
        EFI_EVENT_SIGNAL_LEGACY_BOOT,
        TPL_CALLBACK,
        Legacy_OS_SerialRedirection,
        NULL,
        &SreDir
    );
#else
      Status = CreateLegacyBootEvent(
                  TPL_CALLBACK,
                  Legacy_OS_SerialRedirection,
                  NULL,
                  &SreDir
        );
#endif
    ASSERT_EFI_ERROR(Status);
    return Status;
}

//<AMI_PHDR_START>
//---------------------------------------------------------------------------
//
// Name:          LegacySredirEntryPoint
//
// Description:   Legacy Serial Redirection driver entry point
//
// Input:         Standard EFI Image entry - EFI_IMAGE_ENTRY_POINT
//                EFI System Table - Pointer to System Table
//
// Output:        EFI_STATUS OR EFI_NOT_FOUND
//
//---------------------------------------------------------------------------
//<AMI_PHDR_END>

EFI_STATUS
LegacySredirEntryPoint(
    IN EFI_HANDLE                ImageHandle,
    IN EFI_SYSTEM_TABLE          *SystemTable
        )
{ 
    InitAmiLib(ImageHandle, SystemTable);
    return InitSmmHandler(ImageHandle, SystemTable, LegacySreDirInSmmFunction, LegacySreDirNotInSmmFunction);

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
//**********************************************************************
