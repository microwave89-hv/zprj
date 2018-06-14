//**********************************************************************
//**********************************************************************
//**                                                                  **
//**        (C)Copyright 1985-2015, American Megatrends, Inc.         **
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
// $Header: /Alaska/SOURCE/Modules/HddSecurity/IdeSmm/IDESMM.c 24    4/29/15 3:41a Anbuprakashp $
//
// $Revision: 24 $
//
// $Date: 4/29/15 3:41a $
//**********************************************************************
// Revision History
// ----------------
// $Log: /Alaska/SOURCE/Modules/HddSecurity/IdeSmm/IDESMM.c $
// 
// 24    4/29/15 3:41a Anbuprakashp
// [TAG]  		EIP215937
// [Category]  	Bug Fix
// [Severity]  	Important
// [Symptom]  	System hang while SmmCommunication SMI trigger after enable
// SmmChkEn bit
// [RootCause]  	Bootservice call is used inside IDESMM driver
// [Solution]  	Avoided using BootService call inide IDESMM driver
// [Files]  		IDESMM.c
// 
// 23    4/22/15 4:01a Anbuprakashp
// [TAG]  		EIP212319
// [Category]  	Bug Fix
// [Severity]  	Normal
// [Symptom]  	System hang while SW_SMI_AHCI_LOCATE_AHCI_SMM SMI trigger
// after enable SmmChkEn bit
// [RootCause]  	Bootservice call used inside IdeSmm driver which causes
// the Exception
// [Solution]  	Changes made not to use BootService calls inside IdeSmm
// driver
// [Files]  		IdeSecurity.h
// IdeSecurity.c
// IDESMM.c
// 
// 22    12/09/14 1:41a Anbuprakashp
// [TAG]  		EIP193600
// [Category]  	Improvement
// [Description]  	Security Enhancement for SMIHandler in HddSecurity
// module
// [Files]  		IDESMM.mak, IDESMM.h, IDESMM.c
// 
// 21    8/11/14 6:54a Anbuprakashp
// [TAG]  		EIP178239
// [Category]  	Improvement
// [Description]  	S3 Resume fails when HDD password is set where platform
// have more than one AHCI controller
// [Files]  		AhciSmm.c,AhciSmm.sdl,IDESMM.c
// 
// 20    12/18/13 4:07a Srikantakumarp
// [TAG]    EIP127356
// [Category]    Improvement
// [Description]    Flash NVRAM seems to cause HDD can't be unlocked when
// S3 resume.
// [Files]    IdeSecurity.c, IDESMM.c, HddPassword.c, AhciBus.c, AhciBus.h
// 
// 19    1/08/13 12:39a Rameshr
// [TAG]  		EIP109495
// [Category]  	Improvement
// [Description]  	HddSecurity driver needs to be updated for PI
// specification 1.2
// [Files]  		IdeSmm.c, IdeSmm.dxs, IdeSmm.h, IdeSmm.cif
// 
// 18    8/22/11 2:06a Anandakrishnanl
// [TAG]  		EIP67738
// [Category]  	Bug Fix
// [Severity]  	Normal
// [Symptom]  	IdeSmm.c File has been changed in the previous version to
// remove AHCI Controller Init programming that issue controller reset in
// S3. This causes various AMD platforms to not resume from S3 properly.
// [RootCause]  	IdeSmm.c File has been changed in the previous version to
// remove AHCI Controller Init programming that issue controller reset in
// S3. This causes various AMD platforms to not resume from S3 properly.
// [Solution]  	Reverted the Idesmm.c file to previous version that will
// bring back the Ahci Controller initialization by issuing Controller
// reset
// [Files]  		IDESMM.C
// 
// 17    12/22/10 11:52a Krishnakumarg
// [TAG] - EIP 46081
// [Category] - Action Item
// [Description] - 64 bit PCI config space exception in AHCI driver.
// [Files] - IDESmm.c
// 
// 16    10/11/10 11:02a Krishnakumarg
// [TAG]- EIP 43249
// [Category]-IMPROVEMENT
// [Description]- Non-Ascii character in comments causing build problem in
// japanese XP
// [Files]- IdeSecurity.c,IDESMM.c, InstallIdeSmi, Ata.c, Atapi.c,
// IDEBusComponentName.c, IdeBusMaster.c, IdeHPA.c, IdePowerManagement.c
// 
// 15    9/20/10 4:19a Rameshr
// [TAG]- EIP 44182
// [Category]-IMPROVEMENT
// [Description]- Unable to build the project with HDDSecurity module and
// without AHCI module.
// [Files]- IdeSecurity.h, IdeSmm.c
// 
// 14    9/13/10 1:40a Rameshr
// [TAG]- EIP 43299
// [Category]-IMPROVEMENT
// [Description]- About IdeSecurity module. It use soft smi port 0xb2
// directly.It will need to re-modify on all of AMD project.
// 1) Added the SDL token for Sw SMI port address.
// 2) Used Pciio protocol to get the device location and passed this
// information to SMM driver.
// [Files]- IdeSecurity.c, IdeSmm.c, PideBus.h
// 
// 13    6/01/10 7:07p Krishnakumarg
// Removed Tab spaces.
// 
// 12    1/15/10 10:14a Yul
// Coding Standard
//
// 11    11/02/09 6:04p Davidd
// - Correct S3 resume hanging problem when IDE_PASSWORD_LENGTH is set to
// some value other than 32 (EIP 27989).
// - Correct S3 resume hanging problem in AHCI mode (EIP 29827).
//
// 10    6/05/09 2:47p Rameshr
// x64 mode compilation error Resolved.
// Eip:22710
//
// 9     5/11/09 9:39a Rameshr
// Symptom: Unable to clear the HDD password.
// Solution: SmmProtocols located on the remove HDD password SMI also.
// EIP: 21668
//
// 8     4/28/09 6:56p Rameshr
// HDD password support in RAID mode
// EIP:20421
//
// 7     3/31/09 6:52p Davidd
// Added Device Configuration Freeze Lock programming.
//
// 6     3/05/09 11:34a Rameshr
// RemovedHddpassword doesn't work for Ahci mode- EIP 19935.
//
// 5     4/11/08 4:26p Rameshraju
// s3 Resume time improved when is security not enabled.
//
// 2     3/24/08 6:37p Fasihm
// Updated some missed protocols inside the build switchs.
//
// 4     24/03/08 6:34p Anandakrishnanl
// Removed unwanted comment.
//
// 3     24/03/08 6:31p Anandakrishnanl
// Corrected the SMM Thunk Protocols to Extended Thunk Protocols.
//
// 1     3/11/08 2:40p Fasihm
// Changed the structure names to match with the new SMM module labeled.
// Will have to remove this after updating the IdeSecurity module with
// this change.
//
// 2     10/03/08 6:47p Anandakrishnanl
// Removed FreezeLock related code from SMI for improving the S3 resume
// time.
//
// 1     28/02/08 6:40p Anandakrishnanl
// Created new HddSecurity module.  Isolated IdeSecurity and IdeSmm from
// IdeBus driver to be compatable with the AHCI Bus driver.
//
// 1     2/20/08 8:13p Fasihm
// Added the code to fix the SATA freeze problem.
//
// 8     22/06/07 12:44p Anandakrishnanl
// HardDisk Security Support Module Added.
// Need ACPI Module and SB Module and under Core\Include we updated
// Setup.h.
// Also New IdeBus bin module.
//
// 7     13/04/07 3:06p Anandakrishnanl
// Ide Bus Module - Update source files to comply with AMI coding
// standard"!!!
//
// 6     12/18/06 11:53a Srinin
// Fixed issues with unlocking HDD password during S3 resume.
//
// 5     8/24/06 5:08p Felixp
//
// 4     8/24/06 5:07p Felixp
// x64 support (warnings/errors fixed)
//
// 3     8/24/06 9:31a Felixp
// x64 support (asm code removed)
//
// 2     1/04/06 9:36a Srinin
// Access to Boot services during Runtime removed.
//
// 1     12/14/05 2:57p Srinin
//
//
//
//**********************************************************************

//<AMI_FHDR_START>
//---------------------------------------------------------------------------
//
// Name:        IdeSMM.C
//
// Description:	Provide functions to unlock HDD password during S3 resume
//
//---------------------------------------------------------------------------
//<AMI_FHDR_END>

#include "IDESMM.h"

#if ( defined(AhciSrc_SUPPORT) && (AhciSrc_SUPPORT != 0) )
EFI_GUID              gAhciSmmProtocolGuid      = AHCI_SMM_PROTOCOL_GUID;
UINT8                 *AhciSecurityBuffer = NULL;
AHCI_BUS_SMM_PROTOCOL *mAhciSmm             = NULL;
#endif

#if defined(PI_SPECIFICATION_VERSION)&&(PI_SPECIFICATION_VERSION>=0x0001000A)&&(CORE_COMBINED_VERSION>=0x4028B)
#define RETURN(status) {return status;}
#else
#define RETURN(status) {return ;}
#endif

EFI_GUID              gSecurityModeProtocolGuid = IDE_SECURITY_INTERFACE_GUID;
DLIST                 gPasswordList;

COMMAND_BUFFER        *mCmdBuffer;
UINT8                 *mDataBuffer        = NULL;
UINT8                 *mDataSmmBuffer     = NULL;
UINT8                 *SecurityBuffer     = NULL;
BOOLEAN               AhciInit            = FALSE;

SECURITY_PROTOCOL     *IdeSecurityInterface = NULL;

#if defined(PI_SPECIFICATION_VERSION)&&(PI_SPECIFICATION_VERSION>=0x0001000A)&&(CORE_COMBINED_VERSION >= 0x4028B)
    EFI_SMM_SYSTEM_TABLE2           *gSmst;
#else
    EFI_SMM_SYSTEM_TABLE            *gSmst;
#endif

#define PCI_CFG_ADDR( bus, dev, func, reg ) \
    ((VOID*)(UINTN) (PCIEX_BASE_ADDRESS\
                     + ((bus) << 20) + ((dev) << 15) + ((func) << 12) + reg))

#define AHCI_BAR    0x24
#define PCI_SCC     0x000A        // Sub Class Code Register


#if defined(EFI64) || defined(EFIx64)
static UINT64 DivU64x32(
    IN UINT64           Dividend,
    IN UINTN            Divisor,
    OUT UINTN*Remainder OPTIONAL )
{
    UINT64 Result = Dividend / Divisor;

    if ( Remainder )
    {
        *Remainder = Dividend % Divisor;
    }
    return Result;
}

#else

static UINT64 DivU64x32(
    IN UINT64           Dividend,
    IN UINTN            Divisor,   //Can only be 31 bits.
    OUT UINTN*Remainder OPTIONAL )
{
    UINT64 Result;
    UINT32 Rem;

    _asm
    {
        mov eax, dword ptr Dividend[0]
        mov edx, dword ptr Dividend[4]
        mov esi, Divisor
        xor     edi, edi                    ; Remainder
        mov     ecx, 64                     ; 64 bits
Div64_loop:
        shl     eax, 1                      ;Shift dividend left. This clears bit 0.
        rcl     edx, 1
        rcl     edi, 1                      ;Shift remainder left. Bit 0 = previous dividend bit 63.

        cmp     edi, esi                    ; If Rem >= Divisor, don't adjust
        cmc                                 ; else adjust dividend and subtract divisor.
        sbb     ebx, ebx                    ; if Rem >= Divisor, ebx = 0, else ebx = -1.
        sub     eax, ebx                    ; if adjust, bit 0 of dividend = 1
        and     ebx, esi                    ; if adjust, ebx = Divisor, else ebx = 0. 
        sub     edi, ebx                    ; if adjust, subtract divisor from remainder.
        loop    Div64_loop

        mov     dword ptr Result[0], eax
        mov     dword ptr Result[4], edx
        mov     Rem, edi
    }

        if (Remainder) *Remainder = Rem;

        return Result;
}

#endif

//<AMI_PHDR_START>
//----------------------------------------------------------------------------
// Procedure:   Stall
//
// Description: Stalls for the Required Amount of MicroSeconds
//
// Input:
//          UINTN   Usec    // Number of microseconds to delay
//
// Output:      None
//
// Modified:
//      
// Referrals: 
//
// Notes:
//
//----------------------------------------------------------------------------
//<AMI_PHDR_END>
VOID 
Stall (
    UINTN           Usec
 )
{
   UINTN   Counter, i;
   UINT32  Data32, PrevData;
  UINTN   Remainder;

  Counter = (UINTN)DivU64x32 ((Usec * 10), 3, &Remainder);

  if (Remainder != 0) {
    Counter++;
  }

  //
  // Call WaitForTick for Counter + 1 ticks to try to guarantee Counter tick
  // periods, thus attempting to ensure Microseconds of stall time.
  //
  if (Counter != 0) {

    PrevData = IoRead32(PM_BASE_ADDRESS + 8);
    for (i=0; i < Counter; ) {
       Data32 = IoRead32(PM_BASE_ADDRESS + 8);    
        if (Data32 < PrevData) {        // Reset if there is a overlap
            PrevData=Data32;
            continue;
        }
        i += (Data32 - PrevData);        
        PrevData = Data32;
    }
  }
}

//<AMI_PHDR_START>
//----------------------------------------------------------------------------
// Procedure:   ZeromemorySmm
//
// Description: Clears the buffer
//
// Input:       void    *Buffer,
//              UINTN   Size
//
// Output:      None
//
// Modified:
//      
// Referrals: 
//
// Notes:
//
//----------------------------------------------------------------------------
//<AMI_PHDR_END>
void
ZeroMemorySmm (
    void                            *Buffer,
    UINTN                           Size
 )
{
    UINT8   *Ptr;
    Ptr = Buffer;
    while (Size--) {
        *(Ptr++) = 0;
    }
}

//<AMI_PHDR_START>
//----------------------------------------------------------------------------
// Procedure:   SMMWaitforBitClear
//
// Description: Waits for the given bit to be clear
//
// Input:   HDD_PASSWORD            *pHddPassword,
//          UINT8                   BitClear,
//          UINT32                  Timeout
//
// Output:  EFI_STATUS
//
// Modified:
//      
// Referrals: 
//
// Notes:
//
//----------------------------------------------------------------------------
//<AMI_PHDR_END>
EFI_STATUS
SMMWaitforBitClear (
    HDD_PASSWORD                    *pHddPassword,
    UINT8                           BitClear,
    UINT32                          Timeout
 )
{
    UINT8           Delay;
    UINT8           Data8;

    for ( ; Timeout > 0; Timeout--) {
        for ( Delay = 100; Delay > 0; Delay--) {
            Data8 = IoRead8(pHddPassword->DeviceControlReg);
            if (!(Data8 & BitClear)) return EFI_SUCCESS;
            Stall(10);                      // 10 Usec
        }
    }
    return EFI_TIMEOUT;
}

//<AMI_PHDR_START>
//----------------------------------------------------------------------------
// Procedure:   SMMWaitforBitSet
//
// Description: Checks for a particular Bit to be set for a given amount 
//              of time
//
// Input:   HDD_PASSWORD            *pHddPassword,
//          UINT8                   BitSet,
//          UINT32                  Timeout
//
// Output:  EFI_STATUS
//
// Modified:
//      
// Referrals: 
//
// Notes:
//
//----------------------------------------------------------------------------
//<AMI_PHDR_END>

EFI_STATUS
SMMWaitforBitSet (
    HDD_PASSWORD                    *pHddPassword,
    UINT8                           BitSet,
    UINT32                          TimeOut
 )
{
    UINT8           Delay;
    UINT8           Data8;

    for ( ; TimeOut > 0; TimeOut--) {
        for ( Delay = 100; Delay > 0; Delay--) {
            Data8 = IoRead8(pHddPassword->DeviceControlReg);
            if (Data8 & BitSet) return EFI_SUCCESS;
            Stall(10);                      // 10 Usec
        }
    }
    return EFI_TIMEOUT;
}

//<AMI_PHDR_START>
//----------------------------------------------------------------------------
// Procedure:   SMMWaitForCmdCompletion
//
// Description: Waits for BSY bit to get clear
//
// Input:   HDD_PASSWORD    *pHddPassword 
//
// Output:  EFI_STATUS
//
// Modified:
//      
// Referrals: 
//
// Notes:   Wait for BSY bit to get clear. Check for any errors.
//
//----------------------------------------------------------------------------
//<AMI_PHDR_END>
EFI_STATUS
SMMWaitForCmdCompletion (
    HDD_PASSWORD                    *pHddPassword
 )
{
    UINT8           Data8;
    EFI_STATUS      Status;

//  Read ATL_STATUS and ignore the result. Just a delay
    Data8 = IoRead8(pHddPassword->DeviceControlReg);
    
//  Check for BSY bit to be clear
    Status = SMMWaitforBitClear (   pHddPassword, 
                                    BSY, 
                                    DMA_ATAPI_COMMAND_COMPLETE_TIMEOUT);

    if (EFI_ERROR(Status)) return EFI_DEVICE_ERROR;

//  Check for errors. 
    Data8 = IoRead8(pHddPassword->BaseAddress + 7);

    if (Data8 & (ERR | DF)) return EFI_DEVICE_ERROR;  

    return EFI_SUCCESS;
}

#if ( defined(AhciSrc_SUPPORT) && (AhciSrc_SUPPORT != 0) )

//<AMI_PHDR_START>
//----------------------------------------------------------------------------
// Procedure:   SMMAhciSecurityUnlockCommand
//
// Description: This Function unlocks HDD password during S3 resume in 
//              Ahci Mode Using Int 13.
//
// Input:   HDD_PASSWORD    *pHddPassword 
//
// Output:  EFI_STATUS
//
// Modified:
//      
// Referrals: 
//
// Notes:
//
//----------------------------------------------------------------------------
//<AMI_PHDR_END>
EFI_STATUS
SMMAhciSecurityUnlockCommand (
    HDD_PASSWORD                    *pHddPassword
 )
{
    UINT8              i;
    UINT64             AhciBar = 0;
    UINT8              SccReg;
    BOOLEAN            ControllerinAhciMode = FALSE;
    UINT32             GlobalControl;
    COMMAND_STRUCTURE  CommandStructure;
    UINT32             NoofPorts=0;

    if(mAhciSmm == NULL || !AhciSecurityBuffer) {
        return EFI_NOT_FOUND;
    }

    //    1. Check if Controller is in AHCI Mode.
    //    2. Read ABAR Offset and Get HbaAddress.
    //    3. Disable AHCI_ENABLE. 
    //    4. Issue Controller Reset. 
    //    5. Wait for HBA Reset to Complete.
    //    6. Enable AHCI_ENABLE.

    AhciBar = *(UINT32*)PCI_CFG_ADDR( pHddPassword->BusNo,
                                      pHddPassword->DeviceNo,
                                      pHddPassword->FunctionNo,
                                      AHCI_BAR);
    AhciBar &= 0xFFFFFFF0;

    // Store AhciBase address of HDD Drive before calling AhciSmmInitPortOnS3Resume() function
    // of the "AHCI_BUS_SMM_PROTOCOL"
    mAhciSmm->AhciBaseAddress=AhciBar;

    // Find Number of Ports from BIT0:BIT4 of the HBA_CAP register
    NoofPorts = ((MMIO_READ32(AhciBar + HBA_CAP)) & HBA_CAP_NP_MASK) + 1;

    // Check if AHCI MMIO address space resides in SMRAM region. If yes, don't proceed.
    if( AmiValidateMmioBuffer( (VOID*)mAhciSmm->AhciBaseAddress, HBA_PORTS_START + (NoofPorts * HBA_PORTS_REG_WIDTH) ) ) {
        return EFI_NOT_FOUND;
    }

    if(!AhciInit) {
        SccReg = *(UINT8*)PCI_CFG_ADDR(pHddPassword->BusNo,
                                       pHddPassword->DeviceNo,
                                       pHddPassword->FunctionNo,
                                       PCI_SCC);    // Get Scc Register;

        if((SccReg & 0x06) || (SccReg & 0x04)) { 
            ControllerinAhciMode = TRUE;
        }

        if(ControllerinAhciMode) {

            GlobalControl = MMIO_READ32(AhciBar + 0x04);

            GlobalControl &= 0x7FFFFFFF;
            MMIO_WRITE32(AhciBar + 0x04, GlobalControl);

            GlobalControl = 0x01;
            MMIO_WRITE32(AhciBar + 0x04, GlobalControl);

            Stall(5000);   // 5 milli Sec Delay

            GlobalControl = 0x80000000;
            MMIO_WRITE32(AhciBar + 0x04, GlobalControl);

            Stall(1000000);   // 1 Sec Delay
        }
        AhciInit=TRUE;
    }

    //  Clear the Buffer
    ZeroMemorySmm (AhciSecurityBuffer, 512);
    AhciSecurityBuffer[0] = pHddPassword->Control & 1;;
    if(AhciSecurityBuffer[0]) {
    //Copy 32 Bytes of Password
        for (i = 0; i < IDE_PASSWORD_LENGTH; i++) {
            ((UINT8 *)AhciSecurityBuffer)[i + 2] = pHddPassword->MasterPassword[i];
        }
    } else {
    //Copy 32 Bytes of Password
        for (i = 0; i < IDE_PASSWORD_LENGTH; i++) {
                ((UINT8 *)AhciSecurityBuffer)[i + 2] = pHddPassword->UserPassword[i];
        }
    }
    //
    //Resuming from S3. So bring back the AHCI controller to working state
    //
    mAhciSmm->AhciSmmInitPortOnS3Resume(mAhciSmm,pHddPassword->PortNumber);
    
    //
    //Setup the Unlock command 
    //
    ZeroMemorySmm(&CommandStructure, sizeof(COMMAND_STRUCTURE));
    CommandStructure.SectorCount = 1;
    CommandStructure.LBALow = 0;
    CommandStructure.LBAMid = 0;
    CommandStructure.LBAHigh = 0;
    CommandStructure.Device = 0x40;
    CommandStructure.Command = SECURITY_UNLOCK;
    CommandStructure.Buffer = AhciSecurityBuffer;
    CommandStructure.ByteCount = 512;
    //
    //Issue the unlock command
    //
    mAhciSmm->AhciSmmExecutePioDataCommand( mAhciSmm,
                                            &CommandStructure,
                                            pHddPassword->PortNumber,
                                            0xFF,
                                            ATA,
                                            TRUE);
 
#if DISABLE_SOFT_SET_PREV 
    ZeroMemorySmm (&CommandStructure, sizeof(COMMAND_STRUCTURE));
    CommandStructure.Features = DISABLE_SATA2_SOFTPREV;         // Disable Software Preservation
    CommandStructure.SectorCount = 6;
    CommandStructure.Command = SET_FEATURE_COMMAND;

    mAhciSmm->AhciSmmExecuteNonDataCommand( mAhciSmm,
                                            CommandStructure,
                                            pHddPassword->PortNumber,
                                            0xFF,
                                            ATA
                                            );
#endif

    //
    //Issue the Security Freeze lock command
    //
    ZeroMemorySmm(&CommandStructure, sizeof(COMMAND_STRUCTURE)); 
    CommandStructure.Command = SECURITY_FREEZE_LOCK;
    mAhciSmm->AhciSmmExecuteNonDataCommand( mAhciSmm,
                                            CommandStructure,
                                            pHddPassword->PortNumber,
                                            0xFF,
                                            ATA
                                            );

    //
    //Issue the Device config Freeze lock command 
    //
    ZeroMemorySmm (&CommandStructure, sizeof(COMMAND_STRUCTURE));
    CommandStructure.Command = DEV_CONFIG_FREEZE_LOCK;
    CommandStructure.Features = DEV_CONFIG_FREEZE_LOCK_FEATURES;
    mAhciSmm->AhciSmmExecuteNonDataCommand( mAhciSmm,
                                            CommandStructure,
                                            pHddPassword->PortNumber,
                                            0xFF,
                                            ATA
                                            );

    return EFI_SUCCESS;

}
#endif

//<AMI_PHDR_START>
//----------------------------------------------------------------------------
// Procedure:   SMMSecurityUnlockCommand
//
// Description: This Function unlocks HDD password during S3 resume.
//
// Input:   HDD_PASSWORD    *pHddPassword 
//
// Output:  EFI_STATUS
//
// Modified:
//      
// Referrals: 
//
// Notes:
//
//----------------------------------------------------------------------------
//<AMI_PHDR_END>
EFI_STATUS
SMMSecurityUnlockCommand (
    HDD_PASSWORD                    *pHddPassword
 )
{
    EFI_STATUS                      Status;
    UINT8                           Data8;
    UINT8                           i;
    UINT16                          Reg;

    //  Disable Interrupt
    IoWrite8(pHddPassword->DeviceControlReg, 2);

    //  Select the drive
    IoWrite8(pHddPassword->BaseAddress + 6, pHddPassword->Device << 4);

    //  Wait for BSY to go low
    Status = SMMWaitforBitClear (pHddPassword, BSY, S3_BUSY_CLEAR_TIMEOUT);
    if (EFI_ERROR(Status)) return EFI_DEVICE_ERROR;

    //  Clear the Buffer
    ZeroMemorySmm (SecurityBuffer, 512);

    SecurityBuffer[0] = pHddPassword->Control & 1;;

    if(SecurityBuffer[0]) {

        // Copy 32 Bytes of Password
   
        for (i = 0; i < IDE_PASSWORD_LENGTH; i++) {
            ((UINT8 *)SecurityBuffer)[i + 2] = pHddPassword->MasterPassword[i];
        }
    } else {

        // Copy 32 Bytes of Password
        for (i = 0; i < IDE_PASSWORD_LENGTH; i++) {
                ((UINT8 *)SecurityBuffer)[i + 2] = pHddPassword->UserPassword[i];
        }
    }

    Status = SMMIdeNonDataCommand (pHddPassword, 
                                    0,
                                    0,
                                    0,
                                    0,
                                    0, 
                                    SECURITY_UNLOCK); 
    if (EFI_ERROR(Status)) return EFI_DEVICE_ERROR;

    //  Wait for Command completion
    Status = SMMWaitForCmdCompletion (pHddPassword);
    if (EFI_ERROR(Status)) return EFI_DEVICE_ERROR;

    //  Check for DRQ
    Status = SMMWaitforBitSet(pHddPassword, DRQ, DRQ_TIMEOUT);
    if (EFI_ERROR(Status)) return EFI_DEVICE_ERROR;

    Reg = pHddPassword->BaseAddress;

    //  Status = IdeWriteMultipleWord (pHddPassword->BaseAddress, 256, &SecurityBuffer);
    IoWrite(
        CpuIoWidthFifoUint16,
        Reg,
        256,
        SecurityBuffer
    );

    //  Check for errors
    Status = SMMWaitForCmdCompletion (pHddPassword);
    if (EFI_ERROR(Status)) return EFI_DEVICE_ERROR;

    //  Check for errors. 
    Data8 = IoRead8 ( pHddPassword->BaseAddress + 7);
    if(Data8 & 0x21) {          // ERR OR DF bit set ?
        return EFI_DEVICE_ERROR;  
    }

//IA32_DEBUG
#if DISABLE_SOFT_SET_PREV || FORCE_HDD_PASSWORD_PROMPT
    Status = SMMIdeNonDataCommand (pHddPassword, 
                                    DISABLE_SATA2_SOFTPREV,
                                    6,
                                    0,
                                    0,
                                    0, 
                                    SET_FEATURE_COMMAND);

            //  Check for errors
            Status = SMMWaitForCmdCompletion (pHddPassword);
            if (EFI_ERROR(Status)) return Status;
#endif

    Status = SMMIdeNonDataCommand (pHddPassword, 
                                    DEV_CONFIG_FREEZE_LOCK_FEATURES,
                                    0,
                                    0,
                                    0,
                                    0, 
                                    DEV_CONFIG_FREEZE_LOCK);

    //  Check for errors
    Status = SMMWaitForCmdCompletion (pHddPassword);
    return Status;
}

//<AMI_PHDR_START>
//----------------------------------------------------------------------------
// Procedure:   SMMIdeNonDataCommand
//
// Description: Issues Set Feature command (Non Data)
//
// Input:       HDD_PASSWORD    *pHddPassword
//              UINT8           Command
//
// Output:      EFI_STATUS
//
// Modified:
//      
// Referrals: 
//
// Notes:
//
//----------------------------------------------------------------------------
//<AMI_PHDR_END>
EFI_STATUS 
SMMIdeNonDataCommand (
    HDD_PASSWORD                        *pHddPassword,
    IN UINT8                            Features,
    IN UINT8                            SectorCount,
    IN UINT8                            LBALow,
    IN UINT8                            LBAMid,
    IN UINT8                            LBAHigh,
    IN UINT8                            Command
) 
{

    EFI_STATUS                      Status;
    UINT8                           Data8;

//  Select the drive
    IoWrite8(pHddPassword->BaseAddress + 6, pHddPassword->Device << 4);

//  Check for Controller presence
    Data8 = IoRead8(pHddPassword->DeviceControlReg);
    if (Data8 == 0xFF) {
        ASSERT(Data8 == 0xFF);
        return EFI_DEVICE_ERROR;
    }

//  Before Writing to Sector Count Reg, BSY and DRQ bit should be zero
    Status = SMMWaitforBitClear(pHddPassword, BSY, S3_BUSY_CLEAR_TIMEOUT);
    if (EFI_ERROR(Status)) return EFI_DEVICE_ERROR;

//  Check for DRDY
    Status = SMMWaitforBitSet(pHddPassword, DRDY, DRDY_TIMEOUT);
    if (EFI_ERROR(Status)) return EFI_TIMEOUT;

//  Issue command

    IoWrite8 ( pHddPassword->BaseAddress + 1, Features);
    IoWrite8 ( pHddPassword->BaseAddress + 2, SectorCount);
    IoWrite8 ( pHddPassword->BaseAddress + 3, LBALow);
    IoWrite8 ( pHddPassword->BaseAddress + 4, LBAMid);
    IoWrite8 ( pHddPassword->BaseAddress + 5, LBAHigh);
    IoWrite8 ( pHddPassword->BaseAddress + 7, Command);

    return EFI_SUCCESS;

}
//<AMI_PHDR_START>
//----------------------------------------------------------------------------
// Procedure:   LocateSMMServices
//
// Description: This function Locates the AhciSmm protocl from the Smm
//
// Input:       None
//
// Output:      None
//
// Modified:
//      
// Referrals: 
//
// Notes:	
//
//----------------------------------------------------------------------------
//<AMI_PHDR_END>
EFI_STATUS LocateSMMServices(
    IN  EFI_GUID    *VariableGuid,
    IN  VOID **VariablePointer
)
{
    UINTN                       Index;

    for (Index = 0; Index < gSmst->NumberOfTableEntries; ++Index) {
        if (guidcmp(&gSmst->SmmConfigurationTable[Index].VendorGuid,VariableGuid) == 0) {
            break;
        }
    }

    if (Index != gSmst->NumberOfTableEntries) {
        *VariablePointer = gSmst->SmmConfigurationTable[Index].VendorTable;
        return EFI_SUCCESS;
    }

    return EFI_NOT_FOUND;
}

//<AMI_PHDR_START>
//----------------------------------------------------------------------------
// Procedure:   LocateIdeSmmProtocols
//
// Description: This function Locates the protocols and saves in global pointe
//
// Input:       None
//
// Output:      None
//
// Modified:
//      
// Referrals: 
//
// Notes:
//
//----------------------------------------------------------------------------
//<AMI_PHDR_END>
VOID LocateIdeSmmProtocols()
{

#if ( defined(AhciSrc_SUPPORT) && (AhciSrc_SUPPORT != 0) )
    if(mAhciSmm == NULL && gSmst ) {
        LocateSMMServices(&gAhciSmmProtocolGuid,(VOID **)&mAhciSmm);
    }
#endif
    return;  
}

//<AMI_PHDR_START>
//----------------------------------------------------------------------------
// Procedure:   SaveHDDPassword
//
// Description: This function saves the HDD password and other information 
//              necessary to unlock HDD password during S3 Resume.
//
// Input:       DispatchHandle      Handle to the Dispatcher
//              DispatchContext     SW SMM dispatcher context
//
// Output:      None
//
// Modified:
//      
// Referrals: 
//
// Notes:
//
//----------------------------------------------------------------------------
//<AMI_PHDR_END>
#if defined(PI_SPECIFICATION_VERSION)&&(PI_SPECIFICATION_VERSION>=0x0001000A)&&(CORE_COMBINED_VERSION >= 0x4028B)
EFI_STATUS SaveHDDPassword (
	IN EFI_HANDLE       DispatchHandle,
	IN CONST VOID       *DispatchContext OPTIONAL,
	IN OUT VOID         *CommBuffer OPTIONAL,
	IN OUT UINTN        *CommBufferSize OPTIONAL
#else
VOID SaveHDDPassword (
    IN EFI_HANDLE                   DispatchHandle,
    IN EFI_SMM_SW_DISPATCH_CONTEXT  *DispatchContext
#endif
)
{

    HDD_PASSWORD    *pHddPassword=NULL, *StoredHDDList;
    DLINK           *dlink;
    UINT8           i;
    BOOLEAN         UserOrMaster = FALSE;
    BOOLEAN         CheckFlag;
    EFI_STATUS      Status=EFI_SUCCESS;

#if defined(PI_SPECIFICATION_VERSION)&&(PI_SPECIFICATION_VERSION>=0x00010014)
    pHddPassword = (HDD_PASSWORD *)CommBuffer;
#else
    Status = pBS->LocateProtocol(&gSecurityModeProtocolGuid, NULL, &IdeSecurityInterface);
    if(!EFI_ERROR(Status)) {
        pHddPassword = IdeSecurityInterface->pHDDPasswordBuffer;
    }
#endif

    if (!pHddPassword) {  
        RETURN(Status); 
    }

    //  Check if signature is present or not
    if ((UINT32) pHddPassword->Signature != '$HDD') {
        RETURN(Status);
    }

    //  Check whether info about the HDD is already present
    dlink = gPasswordList.pHead;
    for ( ; dlink; dlink = dlink->pNext) {
        StoredHDDList = OUTTER(dlink, LinkList, HDD_PASSWORD);
        CheckFlag = FALSE;
        if(StoredHDDList->ModeFlag) {
            if (StoredHDDList->PortNumber ==    pHddPassword->PortNumber) {
                CheckFlag = TRUE;
            }
        } else {
            if ((StoredHDDList->BaseAddress ==  pHddPassword->BaseAddress) && 
                (StoredHDDList->Device ==   pHddPassword->Device)) {
                CheckFlag = TRUE;
            }
        }

        if (CheckFlag) {
            UserOrMaster = (BOOLEAN)((pHddPassword->Control) & 0x01);

            if(UserOrMaster){
                //  Match has been found. Just copy the Password buffer
                for (i = 0; i < sizeof (pHddPassword->MasterPassword); i++) { 
                    StoredHDDList->MasterPassword[i] = pHddPassword->MasterPassword[i];
                }
            } else {
                // Match has been found. Just copy the Password buffer
                for (i = 0; i < sizeof (pHddPassword->UserPassword); i++) { 
                    StoredHDDList->UserPassword[i] = pHddPassword->UserPassword[i];
                }
            }
            RETURN(Status);
        }
    }

    //  Allocate memory needed while unlocking the Password. Done only once. 
    //  Same buffer will be reused.
    if (SecurityBuffer == NULL)  {
        pSmst->SmmAllocatePool(0, 512, &SecurityBuffer);
    }

    //  Match has not been found. Allocate memory and copy the buffer.
    if (pSmst->SmmAllocatePool(0, sizeof(HDD_PASSWORD), &StoredHDDList) != EFI_SUCCESS) { 
        RETURN(Status);
    }
    for (i = 0; i < sizeof (HDD_PASSWORD); i++) ((UINT8 *)StoredHDDList)[i] = ((UINT8 *)pHddPassword)[i];
    DListAdd(&gPasswordList, &StoredHDDList->LinkList); 

    RETURN(Status);
}

//<AMI_PHDR_START>
//----------------------------------------------------------------------------
// Procedure:   UnlockHDDPassword
//
// Description: This Function unlocks HDD password during S3 resume.
//
// Input:       DispatchHandle      Handle to the Dispatcher
//              DispatchContext     SW SMM dispatcher context
//
// Output:      None
//
// Modified:
//      
// Referrals: 
//
// Notes:   
//
//----------------------------------------------------------------------------
//<AMI_PHDR_END>
#if defined(PI_SPECIFICATION_VERSION)&&(PI_SPECIFICATION_VERSION>=0x0001000A)&&(CORE_COMBINED_VERSION >= 0x4028B)
EFI_STATUS UnlockHDDPassword (
	IN EFI_HANDLE       DispatchHandle,
	IN CONST VOID       *DispatchContext OPTIONAL,
	IN OUT VOID         *CommBuffer OPTIONAL,
	IN OUT UINTN        *CommBufferSize OPTIONAL
#else
VOID UnlockHDDPassword (
    IN EFI_HANDLE                   DispatchHandle,
    IN EFI_SMM_SW_DISPATCH_CONTEXT  *DispatchContext
#endif
)
{
    HDD_PASSWORD    *StoredHDDList;
    DLINK           *dlink;
    EFI_STATUS      Status=EFI_SUCCESS;

    dlink = gPasswordList.pHead;
    for ( ; dlink; dlink = dlink->pNext) {
        StoredHDDList = OUTTER(dlink, LinkList, HDD_PASSWORD);
        if (StoredHDDList->Signature == '$HDD') {
            if(!StoredHDDList->ModeFlag) {
                SMMSecurityUnlockCommand (StoredHDDList);
            } else {
#if ( defined(AhciSrc_SUPPORT) && (AhciSrc_SUPPORT != 0) )
                SMMAhciSecurityUnlockCommand (StoredHDDList);
#endif
            }
        }
    }
    AhciInit=FALSE;

    RETURN(Status);
}

//<AMI_PHDR_START>
//----------------------------------------------------------------------------
// Procedure:   RemoveHDDPassword
//
// Description: This Function removes HDD password from the internal database
//
// Input:       DispatchHandle      Handle to the Dispatcher
//              DispatchContext     SW SMM dispatcher context
//
// Output:      None
//
// Modified:
//      
// Referrals: 
//
// Notes:
//
//----------------------------------------------------------------------------
//<AMI_PHDR_END>
#if defined(PI_SPECIFICATION_VERSION)&&(PI_SPECIFICATION_VERSION>=0x0001000A)&&(CORE_COMBINED_VERSION >= 0x4028B)
EFI_STATUS RemoveHDDPassword (
	IN EFI_HANDLE       DispatchHandle,
	IN CONST VOID       *DispatchContext OPTIONAL,
	IN OUT VOID         *CommBuffer OPTIONAL,
	IN OUT UINTN        *CommBufferSize OPTIONAL
#else
VOID RemoveHDDPassword (
    IN EFI_HANDLE                   DispatchHandle,
    IN EFI_SMM_SW_DISPATCH_CONTEXT  *DispatchContext
#endif
)
{
    HDD_PASSWORD    *pHddPassword, *StoredHDDList;
    DLINK           *dlink;
    EFI_STATUS      Status=EFI_SUCCESS;

#if defined(PI_SPECIFICATION_VERSION)&&(PI_SPECIFICATION_VERSION>=0x00010014)
    pHddPassword = (HDD_PASSWORD *)CommBuffer;
#else
    Status = pBS->LocateProtocol(&gSecurityModeProtocolGuid, NULL, &IdeSecurityInterface);
    if(!EFI_ERROR(Status)) {
        pHddPassword = IdeSecurityInterface->pHDDPasswordBuffer;
    }
#endif

    if (!pHddPassword) { 
        RETURN(Status); 
    }

//  Check if signature is present or not
    if ((UINT32) pHddPassword->Signature != '$HDD') {
        RETURN(Status);
    }

//  Check whether info about the HDD is already present
    dlink = gPasswordList.pHead;
    for ( ; dlink; dlink = dlink->pNext) {
        StoredHDDList = OUTTER(dlink, LinkList, HDD_PASSWORD);
        if(StoredHDDList->ModeFlag) {
            if (StoredHDDList->PortNumber == pHddPassword->PortNumber) {
                DListDelete(&gPasswordList, &StoredHDDList->LinkList);
            }
        } else {
            if ((StoredHDDList->BaseAddress == pHddPassword->BaseAddress) && 
                (StoredHDDList->Device == pHddPassword->Device)) {
                DListDelete(&gPasswordList, &StoredHDDList->LinkList);
            }
        }

    }
    RETURN(Status);
}

//<AMI_PHDR_START>
//----------------------------------------------------------------------------
// Procedure:   IdeSmmMiscSmiPassword 
//
// Description: This Function Freeze locks HDD, Issues Disable/Enable Software
//              Settings preservation Feature for Security Supported HDDs.
// Input:       DispatchHandle      Handle to the Dispatcher
//              DispatchContext     SW SMM dispatcher context
//
// Output:      None
//
//----------------------------------------------------------------------------
//<AMI_PHDR_END>
#if defined(PI_SPECIFICATION_VERSION)&&(PI_SPECIFICATION_VERSION>=0x0001000A)&&(CORE_COMBINED_VERSION >= 0x4028B)
EFI_STATUS IdeSmmMiscSmiPassword (
	IN EFI_HANDLE       DispatchHandle,
	IN CONST VOID       *DispatchContext OPTIONAL,
	IN OUT VOID         *CommBuffer OPTIONAL,
	IN OUT UINTN        *CommBufferSize OPTIONAL
#else
VOID IdeSmmMiscSmiPassword (
    IN EFI_HANDLE                   DispatchHandle,
    IN EFI_SMM_SW_DISPATCH_CONTEXT  *DispatchContext
#endif
)
{
    EFI_STATUS      Status;
    HDD_PASSWORD    *StoredHDDList;
    DLINK           *dlink;

    dlink = gPasswordList.pHead;
    for ( ; dlink; dlink = dlink->pNext) {
        StoredHDDList = OUTTER(dlink, LinkList, HDD_PASSWORD);
        if (StoredHDDList->Signature == '$HDD') {

            Status = SMMIdeNonDataCommand (StoredHDDList, 
                                    0,
                                    0,
                                    0,
                                    0,
                                    0, 
                                    SECURITY_FREEZE_LOCK);

            //	Check for errors
            Status = SMMWaitForCmdCompletion (StoredHDDList);
            if (EFI_ERROR(Status)) { 
                RETURN(Status);
            }

#if DISABLE_SOFT_SET_PREV || FORCE_HDD_PASSWORD_PROMPT

            Status = SMMIdeNonDataCommand (StoredHDDList, 
                                    DISABLE_SATA2_SOFTPREV,
                                    6,
                                    0,
                                    0,
                                    0, 
                                    SET_FEATURE_COMMAND);

            //	Check for errors
            Status = SMMWaitForCmdCompletion (StoredHDDList);
            if (EFI_ERROR(Status)) { 
                RETURN(Status);
            }
#endif
        }
    }

    RETURN(Status);
}


//<AMI_PHDR_START>
//----------------------------------------------------------------------------
// Procedure:   LocateAhciSMM
//
// Description: This function Locates the AhciSMM driver and save pointer globally.
//
// Input:       DispatchHandle      Handle to the Dispatcher
//              DispatchContext     SW SMM dispatcher context
//
// Output:      None
//
// Modified:
//      
// Referrals: 
//
// Notes:   
//
//----------------------------------------------------------------------------
//<AMI_PHDR_END>
#if defined(PI_SPECIFICATION_VERSION)&&(PI_SPECIFICATION_VERSION>=0x0001000A)&&(CORE_COMBINED_VERSION >= 0x4028B)
EFI_STATUS LocateAhciSMM (
	IN EFI_HANDLE       DispatchHandle,
	IN CONST VOID       *DispatchContext OPTIONAL,
	IN OUT VOID         *CommBuffer OPTIONAL,
	IN OUT UINTN        *CommBufferSize OPTIONAL
#else
VOID LocateAhciSMM (
    IN EFI_HANDLE                   DispatchHandle,
    IN EFI_SMM_SW_DISPATCH_CONTEXT  *DispatchContext
#endif
)
{
    EFI_STATUS      Status=EFI_SUCCESS;

#if defined(PI_SPECIFICATION_VERSION)&&(PI_SPECIFICATION_VERSION>=0x00010014)
    // Unlock command Buffer
    AhciSecurityBuffer = (UINT8 *)(*(UINTN *)CommBuffer);
#else
    if(!AhciSecurityBuffer) {
        Status = pBS->AllocatePool ( EfiReservedMemoryType,
                                     512,
                                     (VOID**)&AhciSecurityBuffer );
    }
#endif

    LocateIdeSmmProtocols();
    RETURN(Status);
}


//<AMI_PHDR_START>
//----------------------------------------------------------------------------
// Procedure:   IdeSmmInSmmFunction
//
// Description: Called from InstallSmiHandler
//
// Input:
//
//
// Output:      None
//
// Modified:
//      
// Referrals: 
//
// Notes:
//
//----------------------------------------------------------------------------
//<AMI_PHDR_END>
EFI_STATUS IdeSmmInSmmFunction(
    IN EFI_HANDLE                ImageHandle,
    IN EFI_SYSTEM_TABLE          *SystemTable
 )
{
    EFI_STATUS  Status;
    EFI_HANDLE  Handle;
    EFI_SMM_SW_REGISTER_CONTEXT  Unlock_HDD_Password = {SW_SMI_HDD_UNLOCK_PASSWORD};
    EFI_SMM_SW_REGISTER_CONTEXT  IdeSmm_MiscSmi_Password = {SW_SMI_HDD_MISC_SMM_FEATURES};

#if defined(PI_SPECIFICATION_VERSION)&&(PI_SPECIFICATION_VERSION>=0x0001000A)&&(CORE_COMBINED_VERSION >= 0x4028B)
    EFI_SMM_BASE2_PROTOCOL          *pSmmBase2;
    EFI_SMM_SW_DISPATCH2_PROTOCOL   *pSwDispatch = NULL;

#else
    EFI_SMM_BASE_PROTOCOL            *pSmmBase;
    EFI_SMM_SW_DISPATCH_PROTOCOL     *pSwDispatch = NULL;
#endif

#if defined(PI_SPECIFICATION_VERSION)&&!(PI_SPECIFICATION_VERSION>=0x00010014)
    EFI_SMM_SW_REGISTER_CONTEXT     Save_HDD_Password = {SW_SMI_HDD_PASSWORD_SAVE};
    EFI_SMM_SW_REGISTER_CONTEXT     Remove_HDD_Password = {SW_SMI_HDD_PASSWORD_REMOVE};
    EFI_SMM_SW_REGISTER_CONTEXT     Locate_Ahci_SMM = {SW_SMI_AHCI_LOCATE_AHCI_SMM};
#endif

    InitAmiBufferValidationLib(ImageHandle, SystemTable);
    Status = InitAmiSmmLib( ImageHandle, SystemTable );

#if defined(PI_SPECIFICATION_VERSION)&&(PI_SPECIFICATION_VERSION>=0x0001000A)&&(CORE_COMBINED_VERSION >= 0x4028B)

    Status = pBS->LocateProtocol(&gEfiSmmBase2ProtocolGuid, NULL, &pSmmBase2);
    
    if (EFI_ERROR(Status)) { 
        return Status;
    }

    //
    // We are in SMM, retrieve the pointer to SMM System Table
    //
    Status = pSmmBase2->GetSmstLocation( pSmmBase2, &gSmst);
    if (EFI_ERROR(Status)) {  
        return EFI_UNSUPPORTED;
    }

    Status  = gSmst->SmmLocateProtocol( &gEfiSmmSwDispatch2ProtocolGuid, \
                                        NULL, \
                                        &pSwDispatch );

#else

    Status = pBS->LocateProtocol(&gEfiSmmBaseProtocolGuid, NULL, &pSmmBase);
    if (EFI_ERROR(Status)) {
        return Status;
    }

    Status = pSmmBase->GetSmstLocation(pSmmBase,&gSmst);
    if (EFI_ERROR(Status)) { 
        return Status;
    }

    Status = pBS->LocateProtocol(&gEfiSmmSwDispatchProtocolGuid, NULL, &pSwDispatch);
#endif

    if (EFI_ERROR(Status)) {
        ASSERT_EFI_ERROR(Status);
        return Status;
    }

    DListInit(&gPasswordList);

#if defined(PI_SPECIFICATION_VERSION)&&(PI_SPECIFICATION_VERSION>=0x00010014)

    Status = gSmst->SmiHandlerRegister(
                        (VOID *)SaveHDDPassword,
                        &gSaveHddPasswordGuid,
                        &Handle
                        );

    if (EFI_ERROR(Status)) {
        ASSERT_EFI_ERROR(Status);
        return Status;
    }

    Status = gSmst->SmiHandlerRegister(
                        (VOID *)RemoveHDDPassword,
                        &gRemoveHddPasswordGuid,
                        &Handle
                        );

    if (EFI_ERROR(Status)) {
        ASSERT_EFI_ERROR(Status);
        return Status;
    }

    Status = gSmst->SmiHandlerRegister(
                        (VOID *)LocateAhciSMM,
                        &gLocateIdeAhciSmmProtocolGuid,
                        &Handle
                        );

    if (EFI_ERROR(Status)) {
        ASSERT_EFI_ERROR(Status);
    }

#else
    Status = pSwDispatch->Register(
                            pSwDispatch,
                            SaveHDDPassword,
                            &Save_HDD_Password,
                            &Handle
                            );

    if (EFI_ERROR(Status)) {
        ASSERT_EFI_ERROR(Status);
        return Status;
    }

    Status = pSwDispatch->Register(
                            pSwDispatch,
                            RemoveHDDPassword,
                            &Remove_HDD_Password,
                            &Handle
                            );

    if (EFI_ERROR(Status)) {
        ASSERT_EFI_ERROR(Status);
        return Status;
    }

    Status = pSwDispatch->Register(
                        pSwDispatch,
                        LocateAhciSMM ,
                        &Locate_Ahci_SMM ,
                        &Handle
                        );

    if (EFI_ERROR(Status)) {
        ASSERT_EFI_ERROR(Status);
        return Status;
    }

#endif

    Status = pSwDispatch->Register(
                            pSwDispatch,
                            UnlockHDDPassword,
                            &Unlock_HDD_Password,
                            &Handle
                            );

    if (EFI_ERROR(Status)) {
        ASSERT_EFI_ERROR(Status);
        return Status;	
    }


    Status = pSwDispatch->Register(
                            pSwDispatch,
                            IdeSmmMiscSmiPassword ,
                            &IdeSmm_MiscSmi_Password ,
                            &Handle
                            );

    if (EFI_ERROR(Status)) {
        ASSERT_EFI_ERROR(Status);
        return Status;
    }

    return EFI_SUCCESS;
}


//<AMI_PHDR_START>
//----------------------------------------------------------------------------
// Procedure:   IdeHDDPasswordSMMInit
//
// Description: Initializes HDD Password SMM Drivers.
//
// Input:
//
// Output:
//      EFI_STATUS
//
// Modified:
//
// Referrals:
//
// Notes:
//  Here is the control flow of this function:
//----------------------------------------------------------------------------
//<AMI_PHDR_END>

EFI_STATUS 
IdeHDDPasswordSMMInit(
    IN EFI_HANDLE       ImageHandle,
    IN EFI_SYSTEM_TABLE *SystemTable
 )
{
    InitAmiLib(ImageHandle,SystemTable);
    return InitSmmHandler(ImageHandle, SystemTable, IdeSmmInSmmFunction, NULL);
}

//**********************************************************************
//**********************************************************************
//**                                                                  **
//**        (C)Copyright 1985-2015, American Megatrends, Inc.         **
//**                                                                  **
//**                       All Rights Reserved.                       **
//**                                                                  **
//**         5555 Oakbrook Pkwy, Suite 200, Norcross, GA 30093        **
//**                                                                  **
//**                       Phone: (770)-246-8600                      **
//**                                                                  **
//**********************************************************************
//**********************************************************************

