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
//**********************************************************************
// $Header: /Alaska/SOURCE/Modules/AHCI/AhciSmm/AhciSmm.c 12    11/24/14 11:56p Kapilporwal $
//
// $Revision: 12 $
//
// $Date: 11/24/14 11:56p $
//**********************************************************************
// Revision History
// ----------------
// $Log: /Alaska/SOURCE/Modules/AHCI/AhciSmm/AhciSmm.c $
// 
// 12    11/24/14 11:56p Kapilporwal
// [TAG]  		EIP191939
// [Category]  	Improvement
// [Description]  	Issue about BIG_REAL_MODE_MMIO_ACCESS of AHCI module
// [Files]  		AI13.bin
// AHCIACC.ASM
// AhciInt13Dxe.c
// AhciInt13Dxe.dxs
// AhciInt13Smm.c
// AhciInt13Smm.cif
// AhciInt13Smm.dxs
// AhciInt13Smm.h
// AhciInt13Smm.mak
// AhciInt13Smm.sdl
// AInt13.c
// Aint13.cif
// AInt13.h
// AhciSmm.c
// AhciSmm.h
// AhciSmmProtocol.h
// 
// 11    8/11/14 6:47a Anbuprakashp
// [TAG]  		EIP178239
// [Category]  	Improvement
// [Description]  	S3 Resume fails when HDD password is set where platform
// have more than one AHCI controller
// [Files]  		AhciSmm.c,AhciSmm.sdl,IDESMM.c
// 
// 10    8/17/12 3:14a Srikantakumarp
// [TAG]  		EIP95863
// [Category]  	Bug Fix
// [Symptom]  	AhciSmm doesnt save and restore the upper 32bits of FBU and
// CLBU
// [RootCause]  	As Windows uses the 64bit address for FIS Base Address
// and Command List Base Address, and AHCISMM driver doesn't take care of
// the upper 32bit value of those which cause the failure in AhciSMM
// driver.
// [Solution]  	Save and Restore the upper 32bits of FBU and CLBU in
// AhciSmm Driver.
// [Files]  		AhciController.c, AhciSmm.c
// 
// 9     11/14/11 3:13a Rameshr
// [TAG]  		EIP73137
// [Category]  	Improvement
// [Description]  	Modified the code to use correct status regsiter and
// bits to check the device status.
// [Files]  		AhciSmm.c
// 
// 8     3/15/11 4:12a Rameshr
// [TAG]- EIP 51884
// [Category]- New Feature
// [Description]- Added packet command function in AhciSMM for sending
// command in SMM handler
// [Files]- AhciSmm.c, AhciSmm.h, AhciSmmProtocols.h
// 
// 7     2/11/11 4:11a Rameshr
// [TAG]  		EIP53704
// [Category]  	Improvement
// [Description]  	AMI headers update for Alaska Ahci Driver
// [Files]  		AhciSmm.mak
// AhciSmm.dxs
// AhciSmm.c
// AhciSmm.h
// 
// 6     5/07/10 2:32p Krishnakumarg
// Updated the date in AMI header
// 
// 5     5/07/10 12:37p Krishnakumarg
// Update for coding standard
// 
// 4     11/13/09 6:05a Rameshr
// AhciBaseAddress initilization moved from entryfunction to
// AhciSmmInitPortOnS3Resume.
// EIP: 29827
// 
// 3     11/02/09 6:15p Davidd
// Correct S3 resume hanging problem in AHCI mode (EIP 29827).
// 
// 2     6/05/09 2:45p Rameshr
// x64 mode compilation error Resolved.
// Eip:22710
// 
// 1     4/28/09 6:39p Rameshr
// Initial Check-in
// 
// 
//**********************************************************************

//<AMI_FHDR_START>
//--------------------------------------------------------------------------
//
// Name: AHCISmm.c	
//
// Description: AHCISmm funtion implementation.
//
//--------------------------------------------------------------------------
//<AMI_FHDR_END>

//---------------------------------------------------------------------------
// Include files
//---------------------------------------------------------------------------
//**********************************************************************

#include <Dxe.h>
#include <AmiDxeLib.h>
#include <Token.h>
#include <Protocol\IdeControllerInit.h>
#include "Protocol\PciIo.h"
#include "Protocol\PDiskInfo.h"
#include "Protocol\PIDEController.h"
#include "protocol\BlockIo.h"
#include "Protocol\PIDEBus.h"
#include <Protocol\AhciSmmProtocol.h>
#include <Protocol\PAhciBus.h>
#include "AhciSmm.h"
#include <Protocol\SmmBase.h>
#include <AmiSmm.h>
#include "AhciController.h"

#define SCC_AHCI_CONTROLLER         0x06
#define SCC_RAID_CONTROLLER         0x04
#define PCI_SCC                     0x000A        // Sub Class Code Register


EFI_GUID    gAhciSmmProtocolGuid=AHCI_SMM_PROTOCOL_GUID;
UINT32      gCommandListBaseAddress;
UINT32      gFisBaseAddress;
UINT32      gCommandListBaseAddress2;
UINT32      gFisBaseAddress2;

AHCI_BUS_SMM_PROTOCOL   AhciSmm;
BOOLEAN     gPortReset = FALSE;             // Avoid Re-entry
UINT8       *SenseData=NULL;


#if defined(EFI64) || defined(EFIx64)
static UINT64
DivU64x32 (
  IN UINT64   Dividend,
  IN UINTN    Divisor,
  OUT UINTN   *Remainder OPTIONAL
  )
{
    UINT64  Result = Dividend/Divisor;
    if (Remainder) *Remainder=Dividend%Divisor;
    return Result;
}

#else
static UINT64 
DivU64x32 (
    IN UINT64   Dividend,
    IN UINTN    Divisor,    //Can only be 31 bits.
    OUT UINTN   *Remainder OPTIONAL
    )
{
    UINT64  Result;
    UINT32  Rem;
    _asm
    {
        mov     eax, dword ptr Dividend[0]
        mov     edx, dword ptr Dividend[4]
        mov     esi, Divisor
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
SmmStall (
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
    return;
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
// Procedure:   WaitforPMMemSet
//
// Description: Wait for memory to be set to the test value.
//
// Input:       
//              SATA_DEVICE_INTERFACE   *SataDevInterface,
//              PMPort
//              Register
//              MaskValue        - The mask value of memory
//              TestValue        - The test value of memory
//              WaitTimeInMs     - The time out value for wait memory set
//
// Output:      EFI_SUCCESS      - HBA reset successfully.
//              EFI_DEVICE_ERROR - HBA failed to complete hardware reset.
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
WaitforPMMemSet (
    IN AHCI_BUS_SMM_PROTOCOL   *SataDevInterface,
    IN UINT8                   PMPort,
    IN UINT8                   Register,
    IN UINT32                  AndMask,
    IN UINT32                  TestValue,
    IN UINT32                  WaitTimeInMs
)
{
    UINT32  Data32;

    while(WaitTimeInMs!=0){ 
        ReadWritePMPort (SataDevInterface, PMPort, Register, &Data32, FALSE);
        if((Data32 & AndMask) == TestValue) {return EFI_SUCCESS;}
        SmmStall (1000);  //  1Msec
        WaitTimeInMs--;
   }
   return EFI_DEVICE_ERROR;
}


//<AMI_PHDR_START>
//----------------------------------------------------------------------------
// Procedure:   WaitForMemSet
//
// Description: Wait for memory to be set to the test value.
//
// Input:       MemTestAddr      - The memory address to test
//              MaskValue        - The mask value of memory
//              TestValue        - The test value of memory
//              WaitTimeInMs     - The time out value for wait memory set
//
// Output:      EFI_SUCCESS      - HBA reset successfully.
//              EFI_DEVICE_ERROR - HBA failed to complete hardware reset.
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
WaitForMemSet (
    IN UINT32 BaseAddr,
    IN UINT8  Port,
    IN UINT8  Register,
    IN UINT32 AndMask,
    IN UINT32 TestValue,
    IN UINT32 WaitTimeInMs
)
{
    UINT8  Delay;
    while(WaitTimeInMs!=0){ 
        for ( Delay = 10; Delay > 0; Delay--) {
            if(((HBA_PORT_REG32(BaseAddr, Port, Register)) & AndMask) == TestValue) {return EFI_SUCCESS;}
            SmmStall (100);  // 100 usec * 10 = 1Msec
        }
        WaitTimeInMs--;
   }
   return EFI_DEVICE_ERROR;
}

//<AMI_PHDR_START>
//----------------------------------------------------------------------------
// Procedure:   WaitForMemClear
//
// Description: Wait for memory to be set to the test value.
//
// Input:       MemTestAddr      - The memory address to test
//              MaskValue        - The mask value of memory
//              WaitTimeInMs     - The time out value for wait memory set
//
// Output:      EFI_SUCCESS      - HBA reset successfully.
//	            EFI_DEVICE_ERROR - HBA failed to complete hardware reset.
//
// Modified:
//      
//
// Referrals: 
//
// Notes:
//
//----------------------------------------------------------------------------
//<AMI_PHDR_END> 
EFI_STATUS 
WaitForMemClear (
    IN UINT32 BaseAddr,
    IN UINT8  Port,
    IN UINT8  Register,
    IN UINT32 AndMask,
    IN UINT32 WaitTimeInMs
)
{
    UINT8  Delay;
    while(WaitTimeInMs!=0){ 
        for ( Delay = 10; Delay > 0; Delay--) {
            if(!((HBA_PORT_REG32(BaseAddr, Port, Register)) & AndMask)) {return EFI_SUCCESS;}
            SmmStall (100);  // 100 usec * 10 = 1Msec
        }
        WaitTimeInMs--;
   }
   return EFI_DEVICE_ERROR;
}

//<AMI_PHDR_START>
//----------------------------------------------------------------------------
// Procedure:   ReadSCRRegister
//
// Description: 
//
// Input:           
//  IN AHCI_BUS_PROTOCOL                   *AhciBusInterface, 
//  IN SATA_DEVICE_INTERFACE               *SataDevInterface, 
//  IN UINT8                               Port, 
//  IN UINT8                               PMPort,
//  IN UINT8                               Register (0 : SStatus 1: SError 2: SControl)
//
// Output:      
//      UINT32
// Modified:
//
// Referrals: 
//
// Notes:
//  1. Check if the device is connected directly to the port
//  2. if yes, read to the AHCI Controller else write to the Port Multiplier register. 
//
//----------------------------------------------------------------------------
//<AMI_PHDR_END> 
UINT32
ReadSCRRegister (
    IN AHCI_BUS_SMM_PROTOCOL   *SataDevInterface,
    IN UINT8                    Port, 
    IN UINT8                    PMPort, 
    IN UINT8                    Register
)
{

    UINT32  Data32 = 0;
    UINT32  Reg = HBA_PORTS_SSTS;

    if (PMPort != 0xFF) {
        ReadWritePMPort (SataDevInterface, PMPort, Register, &Data32, FALSE);
    }
    else {
        if (Register == 1) Reg = HBA_PORTS_SCTL;
        if (Register == 2) Reg = HBA_PORTS_SERR;
        Data32 = HBA_PORT_REG32 (SataDevInterface->AhciBaseAddress, Port, Reg);
    }

    return Data32;
}

//<AMI_PHDR_START>
//----------------------------------------------------------------------------
// Procedure:   WriteSCRRegister
//
// Description: Write to SCONTROL/Serror/SStatus register
//
// Input:           
//  IN AHCI_BUS_PROTOCOL                   *AhciBusInterface, 
//  IN SATA_DEVICE_INTERFACE               *SataDevInterface, 
//  IN UINT8                               Port, 
//  IN UINT8                               PMPort,
//  IN UINT8                               Register, (0 : SStatus 1: SError 2: SControl)
//  IN UINT32                              Data32	
//  
// Output:      
//  EFI_STATUS
//
// Modified:
//      
// Referrals: 
//
// Notes:
//  1. Check if the device is connected directly to the port
//  2. if yes, write to the AHCI Controller else write to the Port Multiplier register
//
//
//----------------------------------------------------------------------------
//<AMI_PHDR_END> 
EFI_STATUS
WriteSCRRegister (
    IN AHCI_BUS_SMM_PROTOCOL   *SataDevInterface,
    IN UINT8                    Port, 
    IN UINT8                    PMPort, 
    IN UINT8                    Register,
    IN UINT32                   Data32
)
{

    UINT32  Reg = HBA_PORTS_SSTS;

    if (PMPort != 0xFF) {
        ReadWritePMPort (SataDevInterface, PMPort, Register, &Data32, TRUE);
    }
    else {
        if (Register == 2) Reg = HBA_PORTS_SCTL;
        if (Register == 1) Reg = HBA_PORTS_SERR;
        HBA_PORT_REG32_OR (SataDevInterface->AhciBaseAddress, Port, Reg, Data32); 
    }

    return EFI_SUCCESS;
}

//<AMI_PHDR_START>
//----------------------------------------------------------------------------
// Procedure:   WaitforCommandComplete
//
// Description: Wait till cmd completes
//
// Input:           
//    IN SATA_DEVICE_INTERFACE               *SataDevInterface,
//    IN COMMAND_TYPE                        CommandType,
//    IN UINTN                               TimeOut
//
// Output:      
//	EFI_STATUS
//
// Modified:
//
// Referrals: 
//
// Notes:
//  1. Check for SError bits. If set return error.
//  2. For PIO IN/Out and Packet IN/OUT command wait till PIO Setup FIS is received
//  3. If D2H register FIS is received, exit the loop.
//  4. Check for SError and TFD bits.
//
//----------------------------------------------------------------------------
//<AMI_PHDR_END>
EFI_STATUS
WaitforCommandComplete  (
    IN AHCI_BUS_SMM_PROTOCOL               *SataDevInterface,
    IN COMMAND_TYPE                        CommandType,
    IN UINTN                               TimeOut    
)
{

    UINT32      AhciBaseAddr = (UINT32)SataDevInterface->AhciBaseAddress;
    UINT8       Port = SataDevInterface->PortNumber;
    UINT32      Data32_SERR, Data32_IS, i;
    BOOLEAN     PxSERR_ERROR = FALSE, PIO_SETUP_FIS = FALSE;
    volatile AHCI_RECEIVED_FIS   *FISReceiveAddress = (AHCI_RECEIVED_FIS   *)SataDevInterface->PortFISBaseAddr;
    UINTN       TimeOutCount = TimeOut;

    for(i = 0; i < TimeOutCount * 2; i++, SmmStall(500)) { // 500usec

        //
        //  Check for Error bits
        //
        Data32_SERR = HBA_PORT_REG32 (AhciBaseAddr, Port, HBA_PORTS_SERR);
        if (Data32_SERR & HBA_PORTS_ERR_CHK) {
            PxSERR_ERROR = TRUE;
            break;
        }

        //
        //  Check for Error bits
        //
        Data32_IS = HBA_PORT_REG32 (AhciBaseAddr, Port, HBA_PORTS_IS);
        if (Data32_IS & HBA_PORTS_IS_ERR_CHK) {
            PxSERR_ERROR = TRUE;
            break;
        }
        
        switch (CommandType) {

            case PIO_DATA_IN_CMD:
            case PIO_DATA_OUT_CMD:
            case PACKET_PIO_DATA_IN_CMD:
            case PACKET_PIO_DATA_OUT_CMD:

                //
                // check if PIO setup received
                //
                if(FISReceiveAddress->Ahci_Psfis[0] == FIS_PIO_SETUP) {
                    FISReceiveAddress->Ahci_Psfis[0] = 0;
                    TimeOutCount = TimeOut;    
                    PIO_SETUP_FIS = TRUE;                         
                }
                break;
            default: 
                break;
            
        }

        //
        // check if D2H register FIS is received
        //
        if(FISReceiveAddress->Ahci_Rfis[0] == FIS_REGISTER_D2H) break;

        //
        // For PIO Data in D2H register FIS is not received. So rely on BSY bit
        //
        if ((CommandType == PIO_DATA_IN_CMD) &&  PIO_SETUP_FIS &&
                    !((HBA_PORT_REG32 (AhciBaseAddr, Port, HBA_PORTS_TFD) & 
                    (HBA_PORTS_TFD_BSY | HBA_PORTS_TFD_DRQ)))){
            break;
        }
    }

    if (PxSERR_ERROR) {

        //
        // clear the status and return error
        //
        HBA_PORT_REG32_OR (AhciBaseAddr, Port, HBA_PORTS_SERR, HBA_PORTS_ERR_CLEAR); 
        HBA_PORT_REG32_OR (AhciBaseAddr, Port, HBA_PORTS_IS, HBA_PORTS_IS_CLEAR);
        return EFI_DEVICE_ERROR;    
    } 
   
    //
    // check if CI register is zero
    //
    if (HBA_PORT_REG32 (AhciBaseAddr, Port, HBA_PORTS_CI)){
        return EFI_DEVICE_ERROR;                
    }

    //
    // check for status bits
    //
    if (HBA_PORT_REG32 (AhciBaseAddr, Port, HBA_PORTS_TFD) & (HBA_PORTS_TFD_ERR | HBA_PORTS_TFD_DRQ)){
        return EFI_DEVICE_ERROR;                
    }

    return EFI_SUCCESS;

}

//<AMI_PHDR_START>
//----------------------------------------------------------------------------
// Procedure:   StartController
//
// Description: 
//
// Input:           
//    IN AHCI_BUS_PROTOCOL                   *AhciBusInterface, 
//    IN SATA_DEVICE_INTERFACE               *SataDevInterface,
//    IN UINT32                              CIBitMask
//
// Output:      
//  EFI_STATUS
// Modified:
//
// Referrals: 
//
// Notes:   
//  1. Clear Status register
//  2. Enable FIS and CR running bit
//  3. Enable Start bit
//  4. Update CI bit mask
//
//----------------------------------------------------------------------------
//<AMI_PHDR_END> 
EFI_STATUS
StartController (
    IN AHCI_BUS_SMM_PROTOCOL               *SataDevInterface,
    IN UINT32                               CIBitMask
)
{

    UINT32      AhciBaseAddr = (UINT32)(SataDevInterface->AhciBaseAddress);
    UINT8       Port = SataDevInterface->PortNumber;

    //
    // Clear Status
    //
    HBA_PORT_REG32_OR (AhciBaseAddr, Port, HBA_PORTS_SERR, HBA_PORTS_ERR_CLEAR); 
    HBA_PORT_REG32_OR (AhciBaseAddr, Port, HBA_PORTS_IS, HBA_PORTS_IS_CLEAR); 

    //
    // Enable FIS Receive
    //
    HBA_PORT_REG32_OR (AhciBaseAddr, Port, HBA_PORTS_CMD, HBA_PORTS_CMD_FRE);

    //
    // Wait till FIS is running
    //
    WaitForMemSet(AhciBaseAddr, Port, HBA_PORTS_CMD,
                                    HBA_PORTS_CMD_FR,
                                    HBA_PORTS_CMD_FR,
                                    HBA_FR_CLEAR_TIMEOUT);

    //
    // Clear FIS Receive area
    //
    ZeroMemorySmm ((VOID *)SataDevInterface->PortFISBaseAddr, RECEIVED_FIS_SIZE);

    //
    // Enable ST
    //
    HBA_PORT_REG32_OR (AhciBaseAddr, Port, HBA_PORTS_CMD, HBA_PORTS_CMD_ST);

    //
    // Enable Command Issued
    //
    HBA_PORT_REG32_OR (AhciBaseAddr, Port, HBA_PORTS_CI, CIBitMask);             

    return EFI_SUCCESS;

}


//<AMI_PHDR_START>
//----------------------------------------------------------------------------
// Procedure:   HandlePortComReset
//
// Description: Check if COM Reset is successful or not
//
// Input:           
//  IN AHCI_BUS_PROTOCOL                   *AhciBusInterface, 
//  IN SATA_DEVICE_INTERFACE               *SataDevInterface,
//  IN UINT8                               Port, 
//  IN UINT8                               PMPort, 
//  
// Output:      
//	EFI_STATUS      
//
// Modified:
//
// Referrals: ReadSCRRegister, WriteSCRRegister
//
// Notes:   
//  1. Check if Link is active. If not return error.
//  2. If Link is present, wait for PhyRdy Change bit to be set.
//  3. Clear SError register
//  4. Wait for D2H register FIS
//  5. Check the Status register for errors.
//  6. If COMRESET is success wait for sometime if the device is ATAPI or GEN1
//
//----------------------------------------------------------------------------
//<AMI_PHDR_END> 
EFI_STATUS
HandlePortComReset(
    IN AHCI_BUS_SMM_PROTOCOL               *SataDevInterface,
    IN UINT8                               Port,
    IN UINT8                               PMPort
)
{

    EFI_STATUS Status = EFI_SUCCESS;
    BOOLEAN     DeviceDetected = FALSE;
    UINT32      Data32, i, Delay, SStatusData;
    UINT32      AhciBaseAddr = (UINT32)(SataDevInterface->AhciBaseAddress);
    volatile AHCI_RECEIVED_FIS  *FISAddress;

    //
    //  Check if detection is complete
    //
    for (i = 0; i < HBA_PRESENCE_DETECT_TIMEOUT; i++){   // Total delay 10msec
        SStatusData = ReadSCRRegister (SataDevInterface, Port, PMPort, 0); // SStatus
        SStatusData &= HBA_PORTS_SSTS_DET_MASK;            
        if ((SStatusData == HBA_PORTS_SSTS_DET_PCE) || (SStatusData == HBA_PORTS_SSTS_DET)) { 
            DeviceDetected = TRUE;
            break; 
        }
        SmmStall (1000);                               // 1msec
    }

    if (DeviceDetected) {

        //
        // Wait till PhyRdy Change bit is set
        //
        if (PMPort == 0xFF) {
            Status = WaitForMemSet(AhciBaseAddr, Port, HBA_PORTS_SERR,
                            HBA_PORTS_SERR_EX,
                            HBA_PORTS_SERR_EX,
                            ATAPI_BUSY_CLEAR_TIMEOUT);
        }
        else {
            Status = WaitforPMMemSet (SataDevInterface, PMPort, PSCR_1_SERROR, 
                        HBA_PORTS_SERR_EX, HBA_PORTS_SERR_EX, ATAPI_BUSY_CLEAR_TIMEOUT);
        }

        //
        // Clear Status register
        //
        FISAddress =  * ((AHCI_RECEIVED_FIS **)(HBA_PORT_REG_BASE(Port) + AhciBaseAddr + HBA_PORTS_FB));
        for (i = 0; i < ATAPI_BUSY_CLEAR_TIMEOUT; ) {
            WriteSCRRegister (SataDevInterface, Port, PMPort, 1, HBA_PORTS_ERR_CLEAR); //SError

            if(FISAddress->Ahci_Rfis[0] == FIS_REGISTER_D2H){
                break;
            }

            //
            // 1msec Strange. Delay is needed for read to succeed.
            //
            SmmStall (1000);                               // 1msec (1000);

            //
            // For device behind PM Port, there is a delay in 
            // writing to the register. So count can be decreased.
            //
            if (PMPort != 0xFF) {i+= 100;}	
            else { i++; }
        } 

                  
        for ( Delay = 0; Delay < (ATAPI_BUSY_CLEAR_TIMEOUT * 10); Delay++) {
            if(!((HBA_PORT_REG32 (AhciBaseAddr, Port, HBA_PORTS_TFD)) & HBA_PORTS_TFD_BSY)) {break;}
            if((HBA_PORT_REG32 (AhciBaseAddr, Port, HBA_PORTS_IS)) & (BIT30 + BIT29 + BIT28 + BIT27 + BIT26)) {break;}
                SmmStall (1000);                               // 1msec (100);  // 100 usec * 10 = 1Msec
        }

        //
        // check for errors
        //
        Data32 = HBA_PORT_REG32 (AhciBaseAddr, Port, HBA_PORTS_TFD); 
        if (Data32 & (HBA_PORTS_TFD_BSY | HBA_PORTS_TFD_ERR)) Status = EFI_DEVICE_ERROR;

        Data32 = HBA_PORT_REG32 (AhciBaseAddr, Port, HBA_PORTS_IS); 
        if (Data32 & (BIT30 + BIT29 + BIT28 + BIT27 + BIT26)) Status = EFI_DEVICE_ERROR;

        HBA_PORT_REG32_OR (AhciBaseAddr, Port, HBA_PORTS_IS, HBA_PORTS_IS_CLEAR); 

    } else {
        Status = EFI_DEVICE_ERROR;
    }

    return Status;
}

//<AMI_PHDR_START>
//----------------------------------------------------------------------------
// Procedure:   GeneratePortReset
//
// Description: Issue a Port Reset
//
// Input:           
//  IN AHCI_BUS_PROTOCOL                   *AhciBusInterface
//  IN SATA_DEVICE_INTERFACE               *SataDevInterface, 
//  IN UINT8                               CurrentPort, 
//  IN UINT8                               Speed,
//  IN UINT8                               PowerManagement
//
// Output:      
//  EFI_STATUS
//
// Modified:
//
// Referrals: ReadWritePMPort, HandlePortComReset
//
// Notes:   
//  1. Issue port reset by setting DET bit in SControl register
//  2. Call HandlePortComReset to check the status of the reset.
//
//----------------------------------------------------------------------------
//<AMI_PHDR_END> 
EFI_STATUS
GeneratePortReset (
    AHCI_BUS_SMM_PROTOCOL               *SataDevInterface, 
    UINT8                               Port,
    UINT8                               PMPort,
    UINT8                               Speed,
    UINT8                               PowerManagement
)
{

    EFI_STATUS  Status;
    UINT32      AhciBaseAddr = (UINT32) SataDevInterface->AhciBaseAddress;
    volatile AHCI_RECEIVED_FIS  *FISAddress = *((AHCI_RECEIVED_FIS  **)(HBA_PORT_REG_BASE(Port) + AhciBaseAddr + HBA_PORTS_FB));
    UINT32      Data32;

    if (!FISAddress){
        return EFI_DEVICE_ERROR;   // FIS receive address is not programmed.
    }

    if (gPortReset){
        return EFI_SUCCESS;
    }

    gPortReset = TRUE;

    //
    // Disable Start bit
    //
    HBA_PORT_REG32_AND (AhciBaseAddr, Port, HBA_PORTS_CMD, ~HBA_PORTS_CMD_ST);

    //
    // Wait till CR is cleared
    //
    Status = WaitForMemClear(AhciBaseAddr, Port, HBA_PORTS_CMD,
                            HBA_PORTS_CMD_CR,
                            HBA_CR_CLEAR_TIMEOUT);

    //
    // Clear Status register
    //
    HBA_PORT_REG32_OR (AhciBaseAddr, Port, HBA_PORTS_SERR, HBA_PORTS_ERR_CLEAR); 
    if (PMPort != 0xFF) {
        Data32 = HBA_PORTS_ERR_CLEAR;
        ReadWritePMPort (SataDevInterface, PMPort, PSCR_1_SERROR, &Data32, TRUE);
    }
    HBA_PORT_REG32_OR (AhciBaseAddr, Port, HBA_PORTS_IS, HBA_PORTS_IS_CLEAR); 
    
    //
    // Enable FIS Receive Enable
    //
    HBA_PORT_REG32_OR (AhciBaseAddr, Port, HBA_PORTS_CMD, HBA_PORTS_CMD_FRE);

    //
    // Wait till FIS is running and then clear the data area
    //
    WaitForMemSet(AhciBaseAddr, Port, HBA_PORTS_CMD,
                                    HBA_PORTS_CMD_FR,
                                    HBA_PORTS_CMD_FR,
                                    HBA_FR_CLEAR_TIMEOUT);

        
    FISAddress->Ahci_Rfis[0] = 0;

    if (PMPort == 0xFF) {

        //
        // Issue Port COMRESET
        //
       HBA_PORT_REG32_AND_OR (AhciBaseAddr, Port, HBA_PORTS_SCTL, 0xFFFFF000, 
                    HBA_PORTS_SCTL_DET_INIT + (Speed << 4) + (PowerManagement << 8));     
        SmmStall (1000);                               // 1msec
        HBA_PORT_REG32_AND (AhciBaseAddr, Port, HBA_PORTS_SCTL, ~HBA_PORTS_SCTL_DET_MASK);
    }
    else {
        Data32 = HBA_PORTS_SCTL_DET_INIT + (Speed << 4) + (PowerManagement << 8);
        ReadWritePMPort (SataDevInterface, PMPort, PSCR_2_SCONTROL, &Data32, TRUE);
        SmmStall (1000);                               // 1msec
        Data32 = (Speed << 4) + (PowerManagement << 8);
        ReadWritePMPort (SataDevInterface, PMPort, PSCR_2_SCONTROL, &Data32, TRUE);
    }
    
    Status = HandlePortComReset(SataDevInterface, Port, PMPort);

    //
    //  Disable FIS Receive Enable
    //
    HBA_PORT_REG32_AND (AhciBaseAddr, Port, HBA_PORTS_CMD, ~HBA_PORTS_CMD_FRE);

    gPortReset = FALSE;     

    if (EFI_ERROR(Status)) {
        return EFI_DEVICE_ERROR;
    }

    return EFI_SUCCESS;    

}


//<AMI_PHDR_START>
//----------------------------------------------------------------------------
// Procedure:   StopController
//
// Description: Stop FIS and CR
//
// Input:           
//    IN AHCI_BUS_PROTOCOL                   *AhciBusInterface, 
//    IN SATA_DEVICE_INTERFACE               *SataDevInterface
//
// Output:      
//  EFI_STATUS
//
// Modified:
//
// Referrals: GeneratePortReset
//
// Notes:
//  1. clear ST bit and wait till CR bits gets reset
//  2. if not generate Port reset
//  3. Clear FIS running bit.
//  4. Clear status register
//
//----------------------------------------------------------------------------
//<AMI_PHDR_END> 
EFI_STATUS
StopController(
    IN AHCI_BUS_SMM_PROTOCOL               *SataDevInterface,
    IN BOOLEAN                              StartOrStop
) 
{

    UINT8       Port = SataDevInterface->PortNumber;
    UINT8       PMPort = SataDevInterface->PMPortNumber;
    UINT32      AhciBaseAddr = (UINT32)(SataDevInterface->AhciBaseAddress);
    EFI_STATUS  Status;
    UINT32      PortFISBaseAddr = SataDevInterface->PortFISBaseAddr;
    UINT32      CommandListBaseAddress = SataDevInterface->PortCommandListBaseAddr;

    if(StartOrStop) {
        gCommandListBaseAddress=HBA_PORT_REG32(AhciBaseAddr,Port,HBA_PORTS_CLB);
        gFisBaseAddress=HBA_PORT_REG32(AhciBaseAddr,Port,HBA_PORTS_FB);
        HBA_PORT_WRITE_REG32(AhciBaseAddr,Port,HBA_PORTS_CLB,CommandListBaseAddress);
        HBA_PORT_WRITE_REG32(AhciBaseAddr,Port,HBA_PORTS_FB,PortFISBaseAddr);

        //
        // Saving the Upper 32 bits of FIS and Command List Registers
        //
        gCommandListBaseAddress2=HBA_PORT_REG32(AhciBaseAddr,Port,HBA_PORTS_CLBU);
        gFisBaseAddress2=HBA_PORT_REG32(AhciBaseAddr,Port,HBA_PORTS_FBU);
        HBA_PORT_WRITE_REG32(AhciBaseAddr,Port,HBA_PORTS_CLBU,0);
        HBA_PORT_WRITE_REG32(AhciBaseAddr,Port,HBA_PORTS_FBU,0);
    }

    //
    // Clear Start
    //
    HBA_PORT_REG32_AND (AhciBaseAddr, Port, HBA_PORTS_CMD, ~(HBA_PORTS_CMD_ST));

    //
    // Make sure CR is 0 with in 500msec
    //
    Status = WaitForMemClear(AhciBaseAddr, Port, HBA_PORTS_CMD,
                            HBA_PORTS_CMD_CR,
                            HBA_CR_CLEAR_TIMEOUT);

    if (EFI_ERROR(Status)) { 
        Status = GeneratePortReset(SataDevInterface, Port, PMPort,
                                        HBA_PORTS_SCTL_SPD_NSNR, HBA_PORTS_SCTL_IPM_DIS);
    };

    if (EFI_ERROR(Status)) {
        goto StopController_ErrorExit;
    }

    if (EFI_ERROR(Status)){
        return Status;
    }

    //
    //  Clear FIS receive enable.
    //
    HBA_PORT_REG32_AND (AhciBaseAddr, Port, 
                                    HBA_PORTS_CMD, ~(HBA_PORTS_CMD_FRE));
    //
    // Make sure FR is 0 with in 500msec
    //
    Status = WaitForMemClear(AhciBaseAddr, Port, HBA_PORTS_CMD,
                            HBA_PORTS_CMD_FR,
                            HBA_FR_CLEAR_TIMEOUT);

    if (EFI_ERROR(Status)) {
        goto StopController_ErrorExit;
    }

    //
    // Clear Status register
    //
    HBA_PORT_REG32_OR (AhciBaseAddr, Port, HBA_PORTS_SERR, HBA_PORTS_ERR_CLEAR); 
    HBA_PORT_REG32_OR (AhciBaseAddr, Port, HBA_PORTS_IS, HBA_PORTS_IS_CLEAR); 

    if(!StartOrStop) {
        HBA_PORT_WRITE_REG32(AhciBaseAddr,Port,HBA_PORTS_CLB,gCommandListBaseAddress);
        HBA_PORT_WRITE_REG32(AhciBaseAddr,Port,HBA_PORTS_FB,gFisBaseAddress);

        //
        // Restoring the Upper 32 bits of FIS and Command List Registers
        //

        HBA_PORT_WRITE_REG32(AhciBaseAddr,Port,HBA_PORTS_CLBU,gCommandListBaseAddress2);
        HBA_PORT_WRITE_REG32(AhciBaseAddr,Port,HBA_PORTS_FBU,gFisBaseAddress2);
    }

    return  EFI_SUCCESS;  

StopController_ErrorExit:
    
        HBA_PORT_WRITE_REG32(AhciBaseAddr,Port,HBA_PORTS_CLB,gCommandListBaseAddress);
        HBA_PORT_WRITE_REG32(AhciBaseAddr,Port,HBA_PORTS_FB,gFisBaseAddress);
		
        //
        // Restoring the Upper 32 bits of FIS and Command List Registers
        //
        HBA_PORT_WRITE_REG32(AhciBaseAddr,Port,HBA_PORTS_CLBU,gCommandListBaseAddress2);
        HBA_PORT_WRITE_REG32(AhciBaseAddr,Port,HBA_PORTS_FBU,gFisBaseAddress2);

    return Status;
  
}

//<AMI_PHDR_START>
//----------------------------------------------------------------------------
// Procedure:   ReadytoAcceptCmd
//
// Description: Check if the device is ready to accept cmd.
//
// Input:           
//  IN SATA_DEVICE_INTERFACE               *SataDevInterface,
//
// Output:
//  EFI_STATUS      
//
// Modified:
//      
// Referrals: GeneratePortReset, ReadWritePMPort
//
// Notes:
//  1. Check the device is ready to accept the command. BSY and DRQ 
//     should be de-asserted.
//  2. If set, generate Port reset
//  3. In case Port Multiplier is connected to the port, enable all 
//     the ports of the Port Multiplier.
//
//----------------------------------------------------------------------------
//<AMI_PHDR_END> 
EFI_STATUS
ReadytoAcceptCmd (
    IN AHCI_BUS_SMM_PROTOCOL               *SataDevInterface
)
{

    EFI_STATUS              Status = EFI_SUCCESS;
    UINT32                  AhciBaseAddr = (UINT32)(SataDevInterface->AhciBaseAddress);
    UINT8                   Port = SataDevInterface->PortNumber;
    UINT8                   PMPort = SataDevInterface->PMPortNumber;
    UINT32                  Data32 = 0, Init_SStatus = 0;

    //
    // Is the Device ready to accept the command
    //
    if (HBA_PORT_REG8 (AhciBaseAddr, Port, HBA_PORTS_TFD) & (HBA_PORTS_TFD_BSY | HBA_PORTS_TFD_DRQ)){
        Data32 = HBA_PORT_REG32 (AhciBaseAddr, Port, HBA_PORTS_SCTL);
        Data32 &= 0xFF0;

        //
        // make sure the status we read is for the right port
        //
        Status = GeneratePortReset(SataDevInterface, Port, 0xFF,
                          (UINT8)((Data32 & 0xF0) >> 4), (UINT8)(Data32 >> 8));
        if (EFI_ERROR(Status)) return Status;

    } 
    return Status;
}

//<AMI_PHDR_START>
//----------------------------------------------------------------------------
// Procedure:   BuildCommandList
//
// Description: Builds command list
//
// Input:           
//  IN SATA_DEVICE_INTERFACE            *SataDevInterface,  
//  IN AHCI_COMMAND_LIST                *CommandList,
//  IN UINT32                           CommandTableBaseAddr
//
// Output:      
//  EFI_STATUS
//
// Modified:
//      
// Referrals: 
//
// Notes:   
//  1. Update CommandList bits
//  2. Not all fields like Ahci_Cmd_A are updated.
//  3. Port number is set to 0xF (Control port) if PM Port number is 0xFF. 
//
//----------------------------------------------------------------------------
//<AMI_PHDR_END> 
EFI_STATUS
BuildCommandList (
    IN AHCI_BUS_SMM_PROTOCOL            *SataDevInterface, 
    IN AHCI_COMMAND_LIST                *CommandList,
    IN UINT32                           CommandTableBaseAddr
)
{
    UINT8                   PMPort = SataDevInterface->PMPortNumber;
 
    ZeroMemorySmm (CommandList, sizeof(AHCI_COMMAND_LIST));
    CommandList->Ahci_Cmd_A = SataDevInterface->DeviceType == ATAPI ? 1 : 0;      // set elsewhere 
    CommandList->Ahci_Cmd_P = 0;       
    CommandList->Ahci_Cmd_R = 0;       
    CommandList->Ahci_Cmd_B = 0;       
    CommandList->Ahci_Cmd_Rsvd1 = 0;       
    CommandList->Ahci_Cmd_PMP = PMPort == 0xFF ? 0x0 : SataDevInterface->PMPortNumber;       
    CommandList->Ahci_Cmd_PRDTL = 0;       
    CommandList->Ahci_Cmd_PRDBC = 0;       
    CommandList->Ahci_Cmd_CTBA = CommandTableBaseAddr;       
    CommandList->Ahci_Cmd_CTBAU = 0;

    return EFI_SUCCESS;

}

//<AMI_PHDR_START>
//----------------------------------------------------------------------------
// Procedure:   CopyMemSmm
//
// Description: Copy Length bytes from Source to Destination.
//
// Input:           
//  IN VOID         *Destination,  
//  IN VOID         *Source,
//  IN UINTN        Length
//
// Output:      
//	None
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
CopyMemSmm (
  IN VOID   *Destination,
  IN VOID   *Source,
  IN UINTN  Length
  )
/*++

Routine Description:

  Copy Length bytes from Source to Destination.

Arguments:

  Destination - Target of copy

  Source      - Place to copy from

  Length      - Number of bytes to copy

Returns:

  None

--*/
{
  CHAR8 *Destination8;
  CHAR8 *Source8;

  if (Source < Destination) {
    Destination8  = (CHAR8 *) Destination + Length - 1;
    Source8       = (CHAR8 *) Source + Length - 1;
    while (Length--) {
      *(Destination8--) = *(Source8--);
    }
  } else {
    Destination8  = (CHAR8 *) Destination;
    Source8       = (CHAR8 *) Source;
    while (Length--) {
      *(Destination8++) = *(Source8++);
    }
  }
}

//<AMI_PHDR_START>
//----------------------------------------------------------------------------
// Procedure:   BuildAtapiCMD
//
// Description: 
//
// Input:           
//  IN SATA_DEVICE_INTERFACE                *SataDevInterface,  
//  IN COMMAND_STRUCTURE                    CommandStructure
//  IN AHCI_COMMAND_LIST                    *CommandList,
//  IN AHCI_COMMAND_TABLE                   *Commandtable
//
// Output:      
//	EFI_STATUS
//
// Modified:
//
// Referrals: 
//
// Notes:
//  1. Copy Packet data to command table
//  2. Set Atapi bit in Command List    
//
//----------------------------------------------------------------------------
//<AMI_PHDR_END> 
EFI_STATUS
BuildAtapiCMD(
    IN AHCI_BUS_SMM_PROTOCOL               *SataDevInterface, 
    IN COMMAND_STRUCTURE                   CommandStructure,
    IN AHCI_COMMAND_LIST                    *CommandList,
    IN AHCI_COMMAND_TABLE                   *Commandtable
)
{

    CopyMemSmm(&(Commandtable->AtapiCmd),&(CommandStructure.AtapiCmd),sizeof(AHCI_ATAPI_COMMAND));

    if (Commandtable->CFis.Ahci_CFis_Cmd == PACKET_COMMAND){ // Is it a packet command?         
        CommandList->Ahci_Cmd_A = 1;
    }

    return EFI_SUCCESS;

}

//<AMI_PHDR_START>
//----------------------------------------------------------------------------
// Procedure:   BuildPRDT
//
// Description: Build PRDT table
//
// Input:           
//  IN SATA_DEVICE_INTERFACE                *SataDevInterface,  
//  IN COMMAND_STRUCTURE                    CommandStructure
//  IN AHCI_COMMAND_LIST                    *CommandList,
//  IN AHCI_COMMAND_TABLE                   *Commandtable
//
// Output:      
//  EFI_STATUS
//
// Modified:
//
// Referrals: 
//
// Notes:
//  1. Build as many PRDT table entries based on ByteCount.
//  2. Set the I flag for the lasr PRDT table.
//  3. Update PRDT table lenght in CommandList
//  
//
//----------------------------------------------------------------------------
//<AMI_PHDR_END> 
EFI_STATUS
BuildPRDT (
    IN AHCI_BUS_SMM_PROTOCOL                *SataDevInterface, 
    IN COMMAND_STRUCTURE                    CommandStructure,
    IN AHCI_COMMAND_LIST                    *CommandList,
    IN AHCI_COMMAND_TABLE                   *Commandtable
)
{

    UINT32                  ByteCount = CommandStructure.ByteCount;
    UINT16                  Prdtlength = 0;
    AHCI_COMMAND_PRDT       *PrdtTable = &(Commandtable->PrdtTable);

    for (;ByteCount; (UINT8 *)PrdtTable += sizeof(AHCI_COMMAND_PRDT)){
        PrdtTable->Ahci_Prdt_DBA = (UINT32)CommandStructure.Buffer;
        PrdtTable->Ahci_Prdt_DBC = ByteCount >= PRD_MAX_DATA_COUNT ? (PRD_MAX_DATA_COUNT - 1) : (ByteCount - 1);
        ByteCount -= (PrdtTable->Ahci_Prdt_DBC + 1);
        PrdtTable->Ahci_Prdt_I = 0;
        Prdtlength+= sizeof(AHCI_COMMAND_PRDT);
        (UINT8 *)CommandStructure.Buffer += PrdtTable->Ahci_Prdt_DBC + 1;
    }

    //
    //  Set I flag only for the last entry.
    //
    (UINT8 *)PrdtTable -= sizeof(AHCI_COMMAND_PRDT);
    PrdtTable->Ahci_Prdt_I = 1;
    CommandList->Ahci_Cmd_PRDTL = Prdtlength / sizeof(AHCI_COMMAND_PRDT);

    return EFI_SUCCESS;

}

//<AMI_PHDR_START>
//----------------------------------------------------------------------------
// Procedure:   BuildCommandFIS
//
// Description: Build Command FIS
//
// Input:           
//  IN SATA_DEVICE_INTERFACE                *SataDevInterface,  
//  IN COMMAND_STRUCTURE                    CommandStructure,
//  IN AHCI_COMMAND_LIST                    *CommandList,
//  IN AHCI_COMMAND_TABLE                   *Commandtable
//
// Output:      
//	EFI_STATUS
//
// Modified:
//
// Referrals: 
//
// Notes:   
//  1. Update Command FIS data area.
//  2. Update the Command FIS lenght in Command List table  
//
//----------------------------------------------------------------------------
//<AMI_PHDR_END> 
EFI_STATUS
BuildCommandFIS (
    IN AHCI_BUS_SMM_PROTOCOL                *SataDevInterface, 
    IN COMMAND_STRUCTURE                    CommandStructure,
    IN AHCI_COMMAND_LIST                    *CommandList,
    IN AHCI_COMMAND_TABLE                   *Commandtable
)
{

    ZeroMemorySmm (Commandtable, sizeof(AHCI_COMMAND_TABLE));

    Commandtable->CFis.Ahci_CFis_Type = FIS_REGISTER_H2D;
    Commandtable->CFis.AHci_CFis_PmPort = SataDevInterface->PMPortNumber == 0xFF ? 0x0 : SataDevInterface->PMPortNumber;

    Commandtable->CFis.Ahci_CFis_Cmd = CommandStructure.Command;

    Commandtable->CFis.Ahci_CFis_Features = CommandStructure.Features;
    Commandtable->CFis.Ahci_CFis_FeaturesExp = CommandStructure.FeaturesExp;

    Commandtable->CFis.Ahci_CFis_SecNum = CommandStructure.LBALow;
    Commandtable->CFis.Ahci_CFis_SecNumExp = CommandStructure.LBALowExp;

    Commandtable->CFis.Ahci_CFis_ClyLow = CommandStructure.LBAMid;
    Commandtable->CFis.Ahci_CFis_ClyLowExp = CommandStructure.LBAMidExp;

    Commandtable->CFis.Ahci_CFis_ClyHigh = CommandStructure.LBAHigh;
    Commandtable->CFis.Ahci_CFis_ClyHighExp = CommandStructure.LBAHighExp;

    Commandtable->CFis.Ahci_CFis_SecCount = (UINT8)(CommandStructure.SectorCount);
    Commandtable->CFis.Ahci_CFis_SecCountExp = (UINT8)(CommandStructure.SectorCount >> 8);

    Commandtable->CFis.Ahci_CFis_DevHead = CommandStructure.Device;
    Commandtable->CFis.Ahci_CFis_Control = CommandStructure.Control;    

    CommandList->Ahci_Cmd_CFL = FIS_REGISTER_H2D_LENGTH / 4;

    return EFI_SUCCESS;

}

//<AMI_PHDR_START>
//----------------------------------------------------------------------------
// Procedure:   ReadWritePMPort
//
// Description: Read/Write routine to PM ports
//
// Input:           
//  IN SATA_DEVICE_INTERFACE       *SataDevInterface,
//  IN UINT8                        Port,
//  IN UINT8                        RegNum,
//  IN OUT UINT32                   *Data
//  IN BOOLEAN                      READWRITE       // TRUE for Write
//
// Output:      
//  EFI_STATUS
//
// Modified:
//
// Referrals: StopController, ReadytoAcceptCmd, BuildCommandList, BuildCommandFIS, BuildAtapiCMD
//            BuildPRDT, StartController, WaitforCommandComplete 
//
// Notes:   
//  1. Update Command Structure for READ/Write Port Multiplier command
//  2. Issue command
//  3. Check for errors.
//  4. Read the out data in case of READ.
//
//----------------------------------------------------------------------------
//<AMI_PHDR_END>
EFI_STATUS
ReadWritePMPort (
    IN AHCI_BUS_SMM_PROTOCOL       *SataDevInterface,
    IN UINT8                        Port,
    IN UINT8                        RegNum,
    IN OUT UINT32                   *Data,
    IN BOOLEAN                      READWRITE
)
{
    EFI_STATUS                  Status;
    COMMAND_STRUCTURE           CommandStructure;
    AHCI_RECEIVED_FIS           *PortFISBaseAddr = (AHCI_RECEIVED_FIS *)(SataDevInterface->PortFISBaseAddr);
    AHCI_COMMAND_LIST           *CommandList = (AHCI_COMMAND_LIST *) SataDevInterface->PortCommandListBaseAddr;
    AHCI_COMMAND_TABLE          *Commandtable = (AHCI_COMMAND_TABLE *)SataDevInterface->PortCommandTableBaseAddr;

    ZeroMemorySmm (&CommandStructure, sizeof(COMMAND_STRUCTURE));

    CommandStructure.Command = READ_PORT_MULTIPLIER;

    if (READWRITE) {
        CommandStructure.SectorCount = (UINT16) (*Data & 0xFF);
        CommandStructure.LBALow = (UINT8) (*Data >> 8);
        CommandStructure.LBAMid = (UINT8)(*Data >> 16);
        CommandStructure.LBAHigh = (UINT8)(*Data >> 24);
        CommandStructure.Command = WRITE_PORT_MULTIPLIER;
    }

    CommandStructure.Device = Port;
    CommandStructure.Features = RegNum;

    Status = StopController(SataDevInterface,TRUE);
    if (EFI_ERROR(Status)) return Status;

    Status = ReadytoAcceptCmd(SataDevInterface);
    if (EFI_ERROR(Status)) {
        StopController(SataDevInterface,FALSE);
        return Status;
    }

    BuildCommandList(SataDevInterface, CommandList, SataDevInterface->PortCommandTableBaseAddr);
    BuildCommandFIS(SataDevInterface, CommandStructure, CommandList, Commandtable);

    //
    // Data-in
    //
    CommandList->Ahci_Cmd_W = 0; 
      
    // 
    // Update of Command Register
    //
    Commandtable->CFis.Ahci_CFis_C = 1;

    //
    // Update the Port Address
    //
    CommandList->Ahci_Cmd_PMP = CONTROL_PORT;
    Commandtable->CFis.AHci_CFis_PmPort = CONTROL_PORT; 

    StartController(SataDevInterface, BIT00);

    Status = WaitforCommandComplete(SataDevInterface, NON_DATA_CMD, TIMEOUT_1SEC);

    //    
    //  Stop Controller
    //
    StopController(SataDevInterface,FALSE);

    if (!READWRITE) {
        *Data = 0;
        if (!EFI_ERROR(Status)) {
            *Data = PortFISBaseAddr->Ahci_Rfis[12] | 	
                    (PortFISBaseAddr->Ahci_Rfis[4] << 8) | 	
                    (PortFISBaseAddr->Ahci_Rfis[5] << 16) | 	
                    (PortFISBaseAddr->Ahci_Rfis[6] << 24);	
        }
    }
    
    return Status;

}

//<AMI_PHDR_START>
//----------------------------------------------------------------------------
// Procedure:   AhciSmmExecuteDmaDataCommand
//
// Description: Exectue the DMA data command
//
// Input:           
//  IN AHCI_BUS_SMM_PROTOCOL               *SataDevInterface,  
//  IN COMMAND_STRUCTURE                   CommandStructure,
//  UINT8                                   PortNumber,
//  UINT8                                   PMPortNumber, 
//  DEVICE_TYPE                             DeviceType,
//  BOOLEAN                                 READWRITE 
//
// Output:      
//  EFI_STATUS
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
AhciSmmExecuteDmaDataCommand (
        AHCI_BUS_SMM_PROTOCOL               *SataDevInterface, 
        COMMAND_STRUCTURE                   *CommandStructure,
        UINT8                               PortNumber,
        UINT8                               PMPortNumber, 
        DEVICE_TYPE                         DeviceType,
        BOOLEAN                             READWRITE
)
{

    EFI_STATUS              Status;
    AHCI_COMMAND_LIST       *CommandList = (AHCI_COMMAND_LIST *) SataDevInterface->PortCommandListBaseAddr;
    AHCI_COMMAND_TABLE      *Commandtable = (AHCI_COMMAND_TABLE *)SataDevInterface->PortCommandTableBaseAddr;

    SataDevInterface->PortNumber=PortNumber;
    SataDevInterface->PMPortNumber=PMPortNumber;
    SataDevInterface->DeviceType=DeviceType;

    Status = StopController(SataDevInterface,TRUE);
    if (EFI_ERROR(Status)) return Status;

    Status = ReadytoAcceptCmd(SataDevInterface);
    if (EFI_ERROR(Status)) {
        StopController(SataDevInterface,FALSE);
        return Status;
    }
    BuildCommandList(SataDevInterface, CommandList, SataDevInterface->PortCommandTableBaseAddr);
    BuildCommandFIS(SataDevInterface, *CommandStructure, CommandList, Commandtable);
    BuildAtapiCMD(SataDevInterface, *CommandStructure, CommandList, Commandtable);
    BuildPRDT(SataDevInterface, *CommandStructure, CommandList, Commandtable);

    // Data-in
    if (READWRITE) {
        CommandList->Ahci_Cmd_W = 1;
    }
    else {
        CommandList->Ahci_Cmd_W = 0;
    }
    Commandtable->CFis.Ahci_CFis_C = 1;

    StartController(SataDevInterface, BIT00);

    Status = WaitforCommandComplete(SataDevInterface, DMA_DATA_IN_CMD, 
                    SataDevInterface->DeviceType == ATA? DMA_ATA_COMMAND_COMPLETE_TIMEOUT \
                    : DMA_ATAPI_COMMAND_COMPLETE_TIMEOUT );
    
    if (!EFI_ERROR(Status)){
        //Check if the required BYTES have been received
        if (CommandList->Ahci_Cmd_PRDBC != CommandStructure->ByteCount){
            Status = EFI_DEVICE_ERROR;
        }
    }
    //  Stop Controller
    StopController(SataDevInterface,FALSE);

    CommandStructure->ByteCount = CommandList->Ahci_Cmd_PRDBC;

    return Status;    

}

//<AMI_PHDR_START>
//----------------------------------------------------------------------------
// Procedure:   AhciSmmExecutePioDataCommand
//
// Description: Exectue the PIO data command
//
// Input:           
//  IN AHCI_BUS_SMM_PROTOCOL               *SataDevInterface,  
//  IN COMMAND_STRUCTURE                   CommandStructure,
//  UINT8                                   PortNumber,
//  UINT8                                   PMPortNumber, 
//  DEVICE_TYPE                             DeviceType,
//  BOOLEAN                                 READWRITE 
//
// Output:      
//  EFI_STATUS
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
AhciSmmExecutePioDataCommand (
    AHCI_BUS_SMM_PROTOCOL               *SataDevInterface, 
    COMMAND_STRUCTURE                   *CommandStructure,
    UINT8                               PortNumber,
    UINT8                               PMPortNumber, 
    DEVICE_TYPE                         DeviceType,
    BOOLEAN                             READWRITE 
    )
{
    EFI_STATUS              Status;
    AHCI_COMMAND_LIST       *CommandList = (AHCI_COMMAND_LIST *) SataDevInterface->PortCommandListBaseAddr;
    AHCI_COMMAND_TABLE      *Commandtable = (AHCI_COMMAND_TABLE *)SataDevInterface->PortCommandTableBaseAddr;

    SataDevInterface->PortNumber=PortNumber;
    SataDevInterface->PMPortNumber=PMPortNumber;
    SataDevInterface->DeviceType=DeviceType;

    Status = StopController(SataDevInterface,TRUE);
    if (EFI_ERROR(Status)) return Status;

	Status = ReadytoAcceptCmd(SataDevInterface);
    if (EFI_ERROR(Status)) {
        StopController(SataDevInterface,FALSE);
        return Status;
    }

    BuildCommandList(SataDevInterface, CommandList, SataDevInterface->PortCommandTableBaseAddr);
    BuildCommandFIS(SataDevInterface, *CommandStructure, CommandList, Commandtable);
    BuildAtapiCMD(SataDevInterface, *CommandStructure, CommandList, Commandtable);
    BuildPRDT(SataDevInterface, *CommandStructure, CommandList, Commandtable);

    if (READWRITE) {
        CommandList->Ahci_Cmd_W = 1;        
    } else {
        CommandList->Ahci_Cmd_W = 0;        
    }
    Commandtable->CFis.Ahci_CFis_C = 1;

    StartController(SataDevInterface, BIT00);


    Status = WaitforCommandComplete(SataDevInterface, PIO_DATA_IN_CMD, 
                    SataDevInterface->DeviceType == ATA? DMA_ATA_COMMAND_COMPLETE_TIMEOUT \
                    : DMA_ATAPI_COMMAND_COMPLETE_TIMEOUT );

    CommandStructure->ByteCount = CommandList->Ahci_Cmd_PRDBC;

    //
    //  Stop Controller
    //
    StopController(SataDevInterface,FALSE);

    return Status; 
}

//<AMI_PHDR_START>
//----------------------------------------------------------------------------
// Procedure:   AhciSmmExecuteNonDataCommand
//
// Description: Exectue the Non Data command 
//
// Input:           
//  IN AHCI_BUS_SMM_PROTOCOL               *SataDevInterface,  
//  IN COMMAND_STRUCTURE                   CommandStructure,
//  UINT8                                   PortNumber,
//  UINT8                                   PMPortNumber, 
//  DEVICE_TYPE                             DeviceType,
//
// Output:      
//  EFI_STATUS
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
AhciSmmExecuteNonDataCommand (
    AHCI_BUS_SMM_PROTOCOL               *SataDevInterface, 
    COMMAND_STRUCTURE                   CommandStructure,
    UINT8                               PortNumber,
    UINT8                               PMPortNumber, 
    DEVICE_TYPE                         DeviceType
)
{

    EFI_STATUS           Status;
    AHCI_COMMAND_LIST    *CommandList = (AHCI_COMMAND_LIST *) SataDevInterface->PortCommandListBaseAddr;
    AHCI_COMMAND_TABLE   *Commandtable = (AHCI_COMMAND_TABLE *)SataDevInterface->PortCommandTableBaseAddr;

    SataDevInterface->PortNumber=PortNumber;
    SataDevInterface->PMPortNumber=PMPortNumber;
    SataDevInterface->DeviceType=DeviceType;

    Status = StopController(SataDevInterface,TRUE);
    if (EFI_ERROR(Status)){
        return Status;
    }

    Status = ReadytoAcceptCmd(SataDevInterface);
    if (EFI_ERROR(Status)) {
        StopController(SataDevInterface,FALSE);
        return Status;
    }

    BuildCommandList(SataDevInterface, CommandList, SataDevInterface->PortCommandTableBaseAddr);
    BuildCommandFIS(SataDevInterface, CommandStructure, CommandList, Commandtable);

    //
    // Data-in
    //
    CommandList->Ahci_Cmd_W = 0; 
      
    // 
    // Update of Command Register
    //
    Commandtable->CFis.Ahci_CFis_C = 1;

    StartController(SataDevInterface, BIT00);

    Status = WaitforCommandComplete(SataDevInterface, NON_DATA_CMD, ATAPI_BUSY_CLEAR_TIMEOUT );

    //    
    // Stop Controller
    //
    StopController(SataDevInterface,FALSE);

    return Status;    
}
//<AMI_PHDR_START>
//----------------------------------------------------------------------------
// Procedure:   HandleAtapiError
//
// Description: Check for ATAPI Errors
//
// Input:           
//    IN AHCI_BUS_SMM_PROTOCOL               *SataDevInterface,
//
// Output:      
//  EFI_STATUS  
//
// Modified:
//      
// Referrals: ExecutePacketCommand
//
// Notes:   
//  1. Execute ATAPI Request Sense command.
//  2. Check for Device getting ready, Media Change, No Media and other errors. Update AtapiDevice->Atapi_Status
//
//----------------------------------------------------------------------------
//<AMI_PHDR_END>
EFI_STATUS
HandleAtapiError (
    IN AHCI_BUS_SMM_PROTOCOL               *SataDevInterface
 )
{

    EFI_STATUS              Status;
    UINT8                   Data8 = 0;
    COMMAND_STRUCTURE       CommandStructure;
    UINT32                  AhciBaseAddr = (UINT32)(SataDevInterface->AhciBaseAddress);
    UINT8                   Port = SataDevInterface->PortNumber;
    ATAPI_DEVICE            *AtapiDevice = &SataDevInterface->AtapiDevice;

    AtapiDevice->Atapi_Status = DEVICE_ERROR;

    ZeroMemorySmm (SenseData, 256);
    ZeroMemorySmm (&CommandStructure, sizeof(COMMAND_STRUCTURE));

    CommandStructure.AtapiCmd.Ahci_Atapi_Command[0] = ATAPI_REQUEST_SENSE;
    CommandStructure.AtapiCmd.Ahci_Atapi_Command[4] = 0xff;

    CommandStructure.ByteCount =  256;
    CommandStructure.Buffer = SenseData;

    Status = AhciSmmExecutePacketCommand(SataDevInterface, &CommandStructure, 0,
                                        Port,SataDevInterface->PMPortNumber,ATAPI);

    if (EFI_ERROR(Status)) {
        Data8 = HBA_PORT_REG8 (AhciBaseAddr, Port, HBA_PORTS_TFD);
    }

    // Check for DF and CHK
    if (Data8 & (DF | CHK)) { 
        goto exit_HandleAtapiError_with_Reset;
    }

    if (!EFI_ERROR(Status)){

        AtapiDevice->Atapi_Status = DEVICE_ERROR;
        Status = EFI_DEVICE_ERROR;              // Default Value    

        if (((SenseData[2] & 0xf) == 2) && (SenseData[12] == 0x3a)) {
            Status = EFI_NO_MEDIA;
            AtapiDevice->Atapi_Status = MEDIUM_NOT_PRESENT;
        }
        if (((SenseData[2] & 0xf) == 2) && (SenseData[12] == 0x04) && (SenseData[13] == 0x01)) {
            Status = EFI_MEDIA_CHANGED;
            AtapiDevice->Atapi_Status = BECOMING_READY;
        }
    
        if (((SenseData[2] & 0xf) == 6) && (SenseData[12] == 0x28)){
                Status = EFI_MEDIA_CHANGED;
                AtapiDevice->Atapi_Status = MEDIA_CHANGED;
        }

        if (((SenseData[2] & 0xf) == 7) && (SenseData[12] == 0x27)){
                Status = EFI_WRITE_PROTECTED;
                AtapiDevice->Atapi_Status = WRITE_PROTECTED_MEDIA;
        }

        if (((SenseData[2] & 0xf) == 6) && (SenseData[12] == 0x29)){
                AtapiDevice->Atapi_Status = POWER_ON_OR_DEVICE_RESET;
        }

        if (((SenseData[2] & 0xf) == 5) && (SenseData[0] == 0x70)){
                AtapiDevice->Atapi_Status = ILLEGAL_REQUEST;
        }
    }    

exit_HandleAtapiError_with_Reset:
        return Status;

}

//<AMI_PHDR_START>
//----------------------------------------------------------------------------
// Procedure:   AhciSmmExecutePacketCommand
//
// Description: Execute a Atapi Packet command
//
// Input:           
//  IN SATA_DEVICE_INTERFACE               *SataDevInterface,  
//  IN COMMAND_STRUCTURE                   *CommandStructure
//  IN BOOLEAN                              READWRITE
//  UINT8                                   PortNumber,
//  UINT8                                   PMPortNumber, 
//  DEVICE_TYPE                             DeviceType
//
// Output:      
//  EFI_STATUS
//
// Modified:
//      
// Referrals: StopController, ReadytoAcceptCmd, BuildCommandList, BuildCommandFIS, BuildAtapiCMD
//            BuildPRDT, StartController, WaitforCommandComplete 
//
// Notes:   
//  1. Stop the Controller
//  2. Check if the device is ready to accept a Command. 
//  3. Build Command list
//  4. Start the Controller.
//  5. Wait till command completes. Check for errors.
//
//----------------------------------------------------------------------------
//<AMI_PHDR_END> 
EFI_STATUS 
AhciSmmExecutePacketCommand (
    AHCI_BUS_SMM_PROTOCOL                   *SataDevInterface, 
    IN COMMAND_STRUCTURE                    *CommandStructure,
    IN BOOLEAN                              READWRITE,
    UINT8                                   PortNumber,
    UINT8                                   PMPortNumber, 
    DEVICE_TYPE                             DeviceType
 )
{

    EFI_STATUS              Status;
    AHCI_COMMAND_LIST       *CommandList = (AHCI_COMMAND_LIST *) SataDevInterface->PortCommandListBaseAddr;
    AHCI_COMMAND_TABLE      *Commandtable = (AHCI_COMMAND_TABLE *)SataDevInterface->PortCommandTableBaseAddr;
    UINT32                  AhciBaseAddr = (UINT32)(SataDevInterface->AhciBaseAddress);
    UINT8                   Port = SataDevInterface->PortNumber;
    UINT8                   Data8;
    ATAPI_DEVICE            *AtapiDevice = &SataDevInterface->AtapiDevice;


    SataDevInterface->PortNumber=PortNumber;
    SataDevInterface->PMPortNumber=PMPortNumber;
    SataDevInterface->DeviceType=DeviceType;

    CommandStructure->LBAMid = (UINT8)(CommandStructure->ByteCount);
    CommandStructure->LBAHigh = (UINT8)(CommandStructure->ByteCount >> 8);
    CommandStructure->Command = PACKET_COMMAND;

    Status = StopController( SataDevInterface,TRUE);
    if (EFI_ERROR(Status)) return Status;

    Status = ReadytoAcceptCmd(SataDevInterface);
    if (EFI_ERROR(Status)) {
        StopController( SataDevInterface,FALSE);
        return Status;
    }

    BuildCommandList(SataDevInterface, CommandList, SataDevInterface->PortCommandTableBaseAddr);
    BuildCommandFIS(SataDevInterface, *CommandStructure, CommandList, Commandtable);
    BuildAtapiCMD(SataDevInterface, *CommandStructure, CommandList, Commandtable);
    BuildPRDT(SataDevInterface, *CommandStructure, CommandList, Commandtable);


    if (READWRITE) {
        CommandList->Ahci_Cmd_W = 1;        
    }
    else {
        CommandList->Ahci_Cmd_W = 0;        
    }
    Commandtable->CFis.Ahci_CFis_C = 1;

    StartController( SataDevInterface, BIT00);

    Status = WaitforCommandComplete(SataDevInterface, PIO_DATA_IN_CMD, 
                    SataDevInterface->DeviceType == ATA? DMA_ATA_COMMAND_COMPLETE_TIMEOUT \
                    : DMA_ATAPI_COMMAND_COMPLETE_TIMEOUT );


    // Handle ATAPI device error
    if (EFI_ERROR(Status) && SataDevInterface->DeviceType == ATAPI) {
        Data8 = HBA_PORT_REG8 (AhciBaseAddr, Port, HBA_PORTS_TFD);
        if (Data8 & CHK ){
            return HandleAtapiError(SataDevInterface);
        }        
    }

    AtapiDevice->Atapi_Status = EFI_SUCCESS;

    CommandStructure->ByteCount = CommandList->Ahci_Cmd_PRDBC;

    //  Stop Controller
    StopController(SataDevInterface,FALSE);

    return Status;    

}


//<AMI_PHDR_START>
//----------------------------------------------------------------------------
// Procedure:   AhciSmmInitPortOnS3Resume
//
// Description: Initilize the Sata port on S3 resume
//
// Input:           
//  IN AHCI_BUS_SMM_PROTOCOL               *SataDevInterface,  
//  UINT8                                   Port,
//
// Output:      
//	EFI_STATUS
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
AhciSmmInitPortOnS3Resume(
    AHCI_BUS_SMM_PROTOCOL               *SataDevInterface, 
    UINT8                               Port
    )
{
    UINT32      AhciBaseAddr=(UINT32)SataDevInterface->AhciBaseAddress;
    // Return error if AhciBase Address is invalid
    if(!AhciBaseAddr) {
        return EFI_DEVICE_ERROR;
    }

    //
    //Set the Spin up device on the port
    //

    HBA_PORT_REG32_OR (AhciBaseAddr, Port, HBA_PORTS_CMD, HBA_PORTS_CMD_SUD);

    WaitForMemSet(AhciBaseAddr, Port, HBA_PORTS_SSTS ,
                                    HBA_PORTS_SSTS_DET_MASK ,
                                    HBA_PORTS_SSTS_DET_PCE ,
                                    HBA_PRESENCE_DETECT_TIMEOUT);

    //
    //Clear Error Regsiter
    //
    HBA_PORT_REG32_OR (AhciBaseAddr, Port,
                                HBA_PORTS_SERR, HBA_PORTS_ERR_CLEAR); // Clear Status register

    HBA_PORT_REG32_OR (AhciBaseAddr, Port, HBA_PORTS_IS, HBA_PORTS_IS_CLEAR); 

    //
    //Set the FIS base address
    //
    gFisBaseAddress=HBA_PORT_REG32(AhciBaseAddr,Port,HBA_PORTS_FB);
    HBA_PORT_WRITE_REG32(AhciBaseAddr,Port,HBA_PORTS_FB,SataDevInterface->PortFISBaseAddr);

    //  Enable FIS Receive Enable
    HBA_PORT_REG32_OR (AhciBaseAddr, Port, HBA_PORTS_CMD, HBA_PORTS_CMD_FRE); 

    // Wait till FIS is running
    WaitForMemSet(AhciBaseAddr, Port, HBA_PORTS_CMD,
                                    HBA_PORTS_CMD_FR,
                                    HBA_PORTS_CMD_FR,
                                    HBA_FR_CLEAR_TIMEOUT);

    // Enable ST
    HBA_PORT_REG32_OR (AhciBaseAddr, Port, HBA_PORTS_CMD, HBA_PORTS_CMD_ST);     

    // Wait till CR list is running
    WaitForMemSet(AhciBaseAddr, Port, HBA_PORTS_CMD,
                                    HBA_PORTS_CMD_CR,
                                    HBA_PORTS_CMD_CR,
                                    HBA_FR_CLEAR_TIMEOUT);

    //
    //Restore the FIS base address
    //
    HBA_PORT_WRITE_REG32(AhciBaseAddr,Port,HBA_PORTS_FB,gFisBaseAddress);

    return EFI_SUCCESS;
   
}

//<AMI_PHDR_START>
//----------------------------------------------------------------------------
//
// Procedure:   InSmmFunction
//
// Description: This function is called from SMM during SMM registration.
//
// Input:
//  IN EFI_HANDLE       ImageHandle
//  IN EFI_SYSTEM_TABLE *SystemTable
//
// Output: EFI_STATUS
//
//----------------------------------------------------------------------------
//<AMI_PHDR_END>
EFI_STATUS InSmmFunction(EFI_HANDLE ImageHandle, EFI_SYSTEM_TABLE *SystemTable)
{
    EFI_STATUS      Status;
    UINT32          FisBaseAddress=0;
    UINT32          PortCommandListBaseAddr=0;
    EFI_SMM_SYSTEM_TABLE            *mSmst;

    //
    //Initilize the Ahci Base addres to 0
    //
    AhciSmm.AhciBaseAddress=0;

    //
    //  Allocate memory for FIS. Should be aligned on 256 Bytes. Each Port will have it own FIS data area.
    //
    Status = pBS->AllocatePool (EfiReservedMemoryType,
                1 * RECEIVED_FIS_SIZE + 0x100,
                (VOID**)&FisBaseAddress);

    ZeroMemorySmm ((VOID *)FisBaseAddress,1 * RECEIVED_FIS_SIZE + 0x100);
    AhciSmm.PortFISBaseAddr =((FisBaseAddress & (~0xFF))+ 0x100);

    //
    //  Allocate memory for Command List (1KB aligned) and Command Table (128KB aligned).
    //  All the ports in the controller will share Command List and Command table data Area.
    //
    Status = pBS->AllocatePool (EfiReservedMemoryType,
                COMMAND_LIST_SIZE_PORT * 2,
                (VOID**)&PortCommandListBaseAddr);

    ZeroMemorySmm ((VOID *)PortCommandListBaseAddr, COMMAND_LIST_SIZE_PORT * 2);

    //
    //  Allocate memory for Sense Data 
    //
    Status = pBS->AllocatePool (EfiReservedMemoryType,
                256,
                (VOID**)&SenseData);

    AhciSmm.PortCommandListBaseAddr = (PortCommandListBaseAddr & (~0x3FF)) + 0x400;
    AhciSmm.PortCommandTableBaseAddr = AhciSmm.PortCommandListBaseAddr + 0x80;

    AhciSmm.AhciSmmInitPortOnS3Resume=AhciSmmInitPortOnS3Resume;
    AhciSmm.AhciSmmExecutePioDataCommand=AhciSmmExecutePioDataCommand;
    AhciSmm.AhciSmmExecuteDmaDataCommand=AhciSmmExecuteDmaDataCommand;
    AhciSmm.AhciSmmExecuteNonDataCommand=AhciSmmExecuteNonDataCommand;
    AhciSmm.AhciSmmExecutePacketCommand=AhciSmmExecutePacketCommand;


    Status = pBS->LocateProtocol(&gEfiSmmBaseProtocolGuid, NULL, &pSmmBase);
    if (EFI_ERROR(Status)) {
        return Status;
    }

    pSmmBase->GetSmstLocation (pSmmBase, &mSmst);

    Status = mSmst->SmmInstallConfigurationTable(
                                        mSmst,
                                        &gAhciSmmProtocolGuid,
                                        &AhciSmm,
                                        sizeof(AHCI_BUS_SMM_PROTOCOL)
                                        );


    ASSERT_EFI_ERROR(Status);

    return Status;
}

//<AMI_PHDR_START>
//----------------------------------------------------------------------------
// Procedure:   AhciSmmDriverEntryPoint
//
// Description: AHCI Smm driver Entry Point
//
// Input:       EFI_HANDLE           ImageHandle,
//              EFI_SYSTEM_TABLE     *SystemTable
//
// Output:      EFI_STATUS
//
// Modified:
//
// Referrals:
//
// Notes:
//----------------------------------------------------------------------------
//<AMI_PHDR_END>
EFI_STATUS AhciSmmDriverEntryPoint(
    IN EFI_HANDLE       ImageHandle,
    IN EFI_SYSTEM_TABLE *SystemTable
)
{
    InitAmiLib(ImageHandle, SystemTable);
    return InitSmmHandler(ImageHandle, SystemTable, InSmmFunction, NULL);   
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
