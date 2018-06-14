//*************************************************************************
//*************************************************************************
//**                                                                     **
//**        (C)Copyright 1985-2011, American Megatrends, Inc.            **
//**                                                                     **
//**                       All Rights Reserved.                          **
//**                                                                     **
//**      5555 Oakbrook Parkway, Suite 200, Norcross, GA 30093           **
//**                                                                     **
//**                       Phone: (770)-246-8600                         **
//**                                                                     **
//*************************************************************************
//*************************************************************************

//*************************************************************************
// $Header: /Alaska/BIN/Modules/Terminal/TerminalAcpi.c 1     12/22/11 1:34a Rajeshms $
//
// $Revision: 1 $
//
// $Date: 12/22/11 1:34a $
//*************************************************************************
// Revision History
// ----------------
// $Log: /Alaska/BIN/Modules/Terminal/TerminalAcpi.c $
// 
// 1     12/22/11 1:34a Rajeshms
// [TAG]  		EIP57579
// [Category]  	Improvement
// [Description]  	PCI legacy console redirection causes Legacy OS
// installation slow because when Redirection is enabled for Legacy OS,
// Legacy Serial Redirection enables the PCI Serial interrupt for
// redirection and sometime after that OS uses its own IVT but still PCI
// Serial interrupt is generated and not handled.So, disable redirection
// at OS level. we disable redirection on ACPI enable/disable call and
// reset the Interrupt Enable Register so that interrupt is not generated.
// [Files]  		Terminal.sdl, Terminal.mak, Terminal.cif, TerminalAcpi.c
// 
// 
//*************************************************************************
//<AMI_FHDR_START>
//
// Name:        TerminalAcpi.c
//
// Description: This file contains function to disable the PCI redirection 
//              at ACPI enable call.
//
//<AMI_FHDR_END>
//*************************************************************************

//----------------------------------------------------------------------------
// Include(s)
//----------------------------------------------------------------------------

#include <Token.h>
#include <AmiDxeLib.h>
#if defined(PI_SPECIFICATION_VERSION)&&(PI_SPECIFICATION_VERSION>=0x0001000A)
#include <Protocol\SmmSwDispatch2.h>
#define AMI_SMM_SW_DISPATCH_CONTEXT  EFI_SMM_SW_REGISTER_CONTEXT
#else
#include <Protocol\SmmSwDispatch.h>
#define AMI_SMM_SW_DISPATCH_CONTEXT  EFI_SMM_SW_DISPATCH_CONTEXT
#endif
#include "TerminalSetupVar.h"

#define     CFG_SPACE_INDEX_REG         0xCF8
#define     CFG_SPACE_DATA_REG          0xCFC
#define     PCI_BAR0                    0x0010
#define     INT08h_SEGMENT              0xF000             
#define     INT08h_OFFSET               0xFEA5

//<AMI_PHDR_START>
//----------------------------------------------------------------------------
//
// Procedure:   TerminalAcpiEnableDisableCallBack
//
// Description: This routine will be called to disable PCI redirection at ACPI
//              enable/disable call and reset Interrupt Enable Register to 
//              disable interrupt from PCI Serial device & replace actual INT08h.
//
// Input:       None 
//
// Output:      None
//
// Notes:       None
//----------------------------------------------------------------------------
//<AMI_PHDR_END>

VOID
TerminalAcpiEnableDisableCallBack(
    IN EFI_HANDLE                   DispatchHandle,
    IN AMI_SMM_SW_DISPATCH_CONTEXT  *DispatchContext
)
{
#if (TOTAL_PCI_SERIAL_PORTS > 0)
    EFI_STATUS  Status;
    UINT8       RegNum = PCI_BAR0;
    UINT32      PciAddr;
    UINT32      BarAddress;
    UINT8       i,DevFunc;

    UINT8   gTotalSioSerialPorts = TOTAL_SIO_SERIAL_PORTS;
    EFI_GUID gTerminalVarGuid   = TERMINAL_VAR_GUID;
    UINTN PciSerialPortsLocationVarSize = 
                                    sizeof(PCI_SERIAL_PORTS_LOCATION_VAR);
    PCI_SERIAL_PORTS_LOCATION_VAR PciSerialPortsLocationVar; 

    UINTN SerialPortsEnabledVarSize = sizeof(SERIAL_PORTS_ENABLED_VAR); 
    UINT32 SerialPortsEnabledVarAttributes=0;
    SERIAL_PORTS_ENABLED_VAR SerialPortsEnabledVar;


    Status = pRS->GetVariable(SERIAL_PORTS_ENABLED_VAR_C_NAME, 
                                &gTerminalVarGuid,
                                &SerialPortsEnabledVarAttributes, 
                                &SerialPortsEnabledVarSize, 
                                &SerialPortsEnabledVar);

    if (!EFI_ERROR(Status)) {
        Status = pRS->GetVariable(PCI_SERIAL_PORTS_LOCATION_VAR_C_NAME, 
                                &gTerminalVarGuid, 
                                NULL, 
                                &PciSerialPortsLocationVarSize, 
                                &PciSerialPortsLocationVar);

        if (!EFI_ERROR(Status)) {
            for (i = 0; i < TOTAL_PCI_SERIAL_PORTS; i++) {
                //
                // Look for the PCI device that are enabled.
                //
                if (SerialPortsEnabledVar.PortsEnabled[gTotalSioSerialPorts+i]) {
                    if ((PciSerialPortsLocationVar.Bus[i] == 0) &&
                        (PciSerialPortsLocationVar.Device[i] == 0) &&
                        (PciSerialPortsLocationVar.Function[i] == 0)) {
                        continue;
                    }
                    
                    DevFunc = (PciSerialPortsLocationVar.Device[i] << 3) + PciSerialPortsLocationVar.Function[i];
                    PciAddr = ((UINT32) (( (UINT16) PciSerialPortsLocationVar.Bus[i] ) << 8) +  DevFunc) << 8;
                    PciAddr += (RegNum & 0xfc);
                    PciAddr |= 0x80000000;

                    IoWrite32(CFG_SPACE_INDEX_REG, PciAddr);
                    BarAddress = IoRead32(CFG_SPACE_DATA_REG);
                    //
                    // Reset the IER register of UART.
                    //
                    if(BarAddress & 1) {
                        IoWrite32(BarAddress, 0);
                    } else {
                        *(UINTN*)( (BarAddress & 0xfffffff0) + 1) = 0;
                    }
                }
            }
            //
            // Replace the Actual INT08h routine which was hooked by Legacy console Redirection 
            //
            *(UINT16*)0x0020 = (UINT16)INT08h_OFFSET;
            *(UINT16*)0x0022 = (UINT16)INT08h_SEGMENT;

            IoWrite8(0x80,0x99);
        }
    }
#endif
    return;
}

//*************************************************************************
//*************************************************************************
//**                                                                     **
//**        (C)Copyright 1985-2011, American Megatrends, Inc.            **
//**                                                                     **
//**                       All Rights Reserved.                          **
//**                                                                     **
//**      5555 Oakbrook Parkway, Suite 200, Norcross, GA 30093           **
//**                                                                     **
//**                       Phone: (770)-246-8600                         **
//**                                                                     **
//*************************************************************************
//*************************************************************************