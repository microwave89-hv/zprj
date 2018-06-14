//****************************************************************************
//****************************************************************************
//**                                                                        **
//**             (C)Copyright 1985-2009, American Megatrends, Inc.          **
//**                                                                        **
//**                          All Rights Reserved.                          **
//**                                                                        **
//**             5555 Oakbrook Pkwy, Suite 200, Norcross, GA 30093          **
//**                                                                        **
//**                          Phone (770)-246-8600                          **
//**                                                                        **
//****************************************************************************
//****************************************************************************
// $Header: /Alaska/BIN/Modules/Terminal/InitTerminalStrings.c 22    12/12/11 6:51a Rajeshms $
//
// $Revision: 22 $
//
// $Date: 12/12/11 6:51a $
//**********************************************************************
// Revision History
// ----------------
// $Log: /Alaska/BIN/Modules/Terminal/InitTerminalStrings.c $
// 
// 22    12/12/11 6:51a Rajeshms
// [TAG]  		EIP71636 
// [Category]  	New Feature
// [Description]  	Implement the AMI_SERIAL_PROTOCOL for non-generic PCI
// Serial Device.
// [Files]  		AmiSerial.c, AmiSerial.sdl, AmiSerial.mak, AmiSerial.chm,
// AmiSerial.dxs, AmiSerial.cif, Terminal.c, SerialIo.c, TerminalSetup.c,
// InitTerminalStrings.c, TerminalSetupVar.h, Terminal.cif,
// TerminalAmiSerial.h, LegacySredir_Setup.c
// 
// 21    3/02/11 3:15a Rameshr
// [TAG]- EIP 54313
// [Category]-IMPROVEMENT
// [Description]- Terminal driver Getvariable calls assumed to have valid
// values. Added code to return the error code when there is an failure in
// the getvariable call. 
// [Files]- TerminalSetup.c, InitTerminalString.c
// 
// 20    11/02/10 4:17a Lavanyap
// [TAG] - EIP42299
// [Category] - IMPROVEMENT
// [Description] - Console Redirection can support 10 COM Ports.
// [Files] - InitTerminalStrings.c, SerialIo.c, Terminal.sd, 
//           Terminal.sdl, Terminal.uni, TerminalSetup.c
// 
// 19    10/19/10 8:35a Rajeshms
// [TAG]- EIP 39562
// [Category]-IMPROVEMENT
// [Description]- Show entire PCI address of redirection device in Setup
// [Files]- Terminal.c, TerminalSetup.c, InitTerminalStrings.c
// 
// 18    1/20/10 4:47p Artems
// EIP 34000 - made UEFI 2.1 changes backward compatible
// 
// 17    12/16/09 4:33p Artems
// EIP 31619 added UEFI 2.1 support
// 
// 16    11/18/09 10:28a Fasihm
// EIP#30023 - Fix added to resolve the NVRAM Corruption issue in the
// projects.
// 
// 15    7/02/09 5:01p Rameshr
// Coding Standard and File header updated.
// 
// 14    4/14/08 4:55p Ambikas
// 
// 13    4/14/08 2:33p Ambikas
// 
// 12    6/18/07 6:38p Ambikas
// 
// 11    6/12/07 3:53p Ambikas
// 
// 10    6/11/07 11:35a Ambikas
// 
// 9     6/10/07 6:02p Ambikas
// 
// 8     6/06/07 7:55p Ambikas
// We no longer print segment and bus numbers of pci serial device, just
// device and function numbers.
// 
// 7     6/05/07 6:26p Ambikas
// 
// 6     6/05/07 6:16p Ambikas
// 
// 5     6/05/07 11:44a Ambikas
// 
// 4     6/05/07 11:43a Ambikas
// 
// 3     6/05/07 11:40a Ambikas
// 
// 2     6/04/07 7:32p Ambikas
// -Increased the max number of pci serial ports to 4.  Added extra strings
//  for the additional ports.
// -If TOTAL_SERIAL_PORTS is 0, then the setup data structures for the 
//  serial ports in Terminal.sd will not be defined.  So, we comment out
//  code which references those data structures and just return default 
//  values.  
//
// 1     5/24/2007 2:33p Ambikas
//
//**********************************************************************
//<AMI_FHDR_START>
//
// Name: InitTerminalStrings.c
//
// Description: Contains InitTerminalStrings(), which is linked to 
//              SetupStringInit in the sdl page.  Before entering setup,
//              we do any modification or updating needed for the serial
//              port name strings (STR_SIO_SERIAL_PORT0, etc.).
//
//<AMI_FHDR_END>
//**********************************************************************

#include <AmiLib.h>
#include <AmiDxeLib.h>
#include <Setup.h>
#include <SetupStrTokens.h>
#include <Token.h>
#include "TerminalSetupVar.h"

#ifndef HII_LIBRARY_FUNCTIONS_SUPPORT
EFI_STATUS HiiLibGetString(
	IN EFI_HII_HANDLE HiiHandle, 
    IN STRING_REF StringId, 
	IN OUT UINTN *StringSize, 
    OUT EFI_STRING String
);
EFI_STATUS HiiLibSetString(
	IN EFI_HII_HANDLE HiiHandle, 
    IN STRING_REF StringId, 
    IN EFI_STRING String
);
#endif


STRING_REF gSioSerialPortStrRef[MAX_SIO_SERIAL_PORTS] = {
    STRING_TOKEN(STR_SIO_SERIAL_PORT0), 
    STRING_TOKEN(STR_SIO_SERIAL_PORT1), 
    STRING_TOKEN(STR_SIO_SERIAL_PORT2), 
    STRING_TOKEN(STR_SIO_SERIAL_PORT3),
    STRING_TOKEN(STR_SIO_SERIAL_PORT4), 
    STRING_TOKEN(STR_SIO_SERIAL_PORT5), 
    STRING_TOKEN(STR_SIO_SERIAL_PORT6), 
    STRING_TOKEN(STR_SIO_SERIAL_PORT7), 
    STRING_TOKEN(STR_SIO_SERIAL_PORT8), 
    STRING_TOKEN(STR_SIO_SERIAL_PORT9)
};

STRING_REF gPciSerialPortStrRef[MAX_PCI_SERIAL_PORTS] = {
    STRING_TOKEN(STR_PCI_SERIAL_PORT0), 
    STRING_TOKEN(STR_PCI_SERIAL_PORT1), 
    STRING_TOKEN(STR_PCI_SERIAL_PORT2), 
    STRING_TOKEN(STR_PCI_SERIAL_PORT3) 
};

UINT32 gTotalSioSerialPorts = TOTAL_SIO_SERIAL_PORTS;
UINT32 gTotalPciSerialPorts = TOTAL_PCI_SERIAL_PORTS;

EFI_GUID gTerminalVarGuid = TERMINAL_VAR_GUID;

//**********************************************************************
//<AMI_PHDR_START>
//
// Procedure: StrCat
//
// Description: Wrapper function around Wcscpy.  
//              Concantenates the second Unicode string to the first.
//
// Input: 
//      IN OUT CHAR16 *Destination
//      IN CHAR16 *Source
//
// Output: VOID
//
//<AMI_PHDR_END>
//**********************************************************************  
VOID StrCat (IN OUT CHAR16 *Destination, IN CHAR16 *Source)
{
    Wcscpy (Destination + Wcslen (Destination), Source);
}

//**********************************************************************
//<AMI_PHDR_START>
//
// Procedure: InitTerminalStrings
//
// Input: 
//      IN EFI_HII_HANDLE HiiHandle
//      IN UINT16 Class
//
// Output: VOID
//
// Description: Certain strings in the terminal setup page can only be 
//              updated at runtime, which is what this function does.  
//              The pci serial port names are changed to contain the 
//              location (device and function numbers) of the port.  
//              If any serial ports are disabled, "Disabled" 
//              is concatenated to their names.  
//
// Output:
//
//<AMI_PHDR_END>
//**********************************************************************  
VOID InitTerminalStrings(IN EFI_HII_HANDLE HiiHandle, IN UINT16 Class)
{
#if (TOTAL_SERIAL_PORTS > 0)

    EFI_STATUS Status = EFI_SUCCESS;

    UINTN SerialPortsEnabledVarSize = sizeof(SERIAL_PORTS_ENABLED_VAR);
    SERIAL_PORTS_ENABLED_VAR SerialPortsEnabledVar; 
    UINT32 SerialPortsEnabledVarAttributes=0;

#if (TOTAL_PCI_SERIAL_PORTS > 0)
    UINTN PciSerialPortsLocationVarSize 
                                = sizeof(PCI_SERIAL_PORTS_LOCATION_VAR);
    PCI_SERIAL_PORTS_LOCATION_VAR PciSerialPortsLocationVar; 
    UINT32 PciSerialPortsLocationVarAttributes=0;
#endif

    UINT32 i = 0; 

    CHAR16 Str[512]=L"";
    CHAR16 Str2[512]=L"";
    UINTN Size=512;

    if (Class==ADVANCED_FORM_SET_CLASS) {
        Status = pRS->GetVariable(SERIAL_PORTS_ENABLED_VAR_C_NAME, 
                                    &gTerminalVarGuid,
                                    &SerialPortsEnabledVarAttributes, 
                                    &SerialPortsEnabledVarSize,
                                    &SerialPortsEnabledVar);
	
	if (EFI_ERROR(Status)) {
		return;
	}

#if (TOTAL_PCI_SERIAL_PORTS > 0)
        Status = pRS->GetVariable(PCI_SERIAL_PORTS_LOCATION_VAR_C_NAME, 
                                    &gTerminalVarGuid, 
                                    &PciSerialPortsLocationVarAttributes, 
                                    &PciSerialPortsLocationVarSize,
                                    &PciSerialPortsLocationVar);
        ASSERT_EFI_ERROR(Status);

        if (EFI_ERROR(Status)) {
            return;
        }
#endif

        for (i = 0; i < gTotalSioSerialPorts; i++) {
            if (!SerialPortsEnabledVar.PortsEnabled[i]) {
                Size = 512;
                Status = HiiLibGetString(HiiHandle, 
                                            gSioSerialPortStrRef[i],
                                            &Size, Str);
                if (!EFI_ERROR(Status)) {
                    StrCat(Str, L" (Disabled)");
                    InitString(HiiHandle,  gSioSerialPortStrRef[i], Str);
                }
            }
        }

#if (TOTAL_PCI_SERIAL_PORTS > 0)
        for (i = 0; i < gTotalPciSerialPorts; i++) {
            Size = 512;
            Status = HiiLibGetString(HiiHandle, 
                                        gPciSerialPortStrRef[i],
                                        &Size, Str);
            if (!EFI_ERROR(Status)) {
                if(PciSerialPortsLocationVar.AmiPciSerialPresent[i] == TRUE) {
                    //
                    // If AMI Serial Protcocol was installed for this PCI Serial device,
                    // then display the device like COM3(Pci Bus2,Dev10,Func1,Port0)
                    // with Port information.
                    //
                    Swprintf(Str2, L"COM%X(Pci Bus%d,Dev%d,Func%d,Port%d)",
                                        gTotalSioSerialPorts+i,
                                        PciSerialPortsLocationVar.Bus[i],
                                        PciSerialPortsLocationVar.Device[i],
                                        PciSerialPortsLocationVar.Function[i],
                                        PciSerialPortsLocationVar.Port[i]);
                } else {
                    Swprintf(Str2, L"COM%X(Pci Bus%d,Dev%d,Func%d)",
                                        gTotalSioSerialPorts+i,
                                        PciSerialPortsLocationVar.Bus[i],
                                        PciSerialPortsLocationVar.Device[i],
                                        PciSerialPortsLocationVar.Function[i]);
                }                
    
                StrCat(Str, Str2); 
                if (!SerialPortsEnabledVar.PortsEnabled[gTotalSioSerialPorts+i]) {
                    StrCat(Str, L" (Disabled)");
                }
                InitString(HiiHandle, gPciSerialPortStrRef[i], Str);
            }
        }
#endif
    }
#endif
}

#ifndef HII_LIBRARY_FUNCTIONS_SUPPORT
#include <Protocol/Hii.h>

static EFI_HII_PROTOCOL *Hii = NULL;

static EFI_STATUS HiiLibGetString(
	IN EFI_HII_HANDLE HiiHandle, 
    IN STRING_REF StringId, 
	IN OUT UINTN *StringSize, 
    OUT EFI_STRING String
)
{
    if (Hii == NULL && EFI_ERROR(pBS->LocateProtocol(&gEfiHiiProtocolGuid, NULL, &Hii))) 
        return EFI_NOT_FOUND;

    return Hii->GetString(Hii, HiiHandle, StringId, TRUE, NULL, StringSize, String);
}

static EFI_STATUS HiiLibSetString(
	IN EFI_HII_HANDLE HiiHandle, 
    IN STRING_REF StringId, 
    IN EFI_STRING String
)
{
    if (Hii == NULL && EFI_ERROR(pBS->LocateProtocol(&gEfiHiiProtocolGuid, NULL, &Hii))) 
        return EFI_NOT_FOUND;

    return Hii->NewString(Hii, L"   ", HiiHandle, &StringId, String);
}
#endif

//****************************************************************************
//****************************************************************************
//**                                                                        **
//**             (C)Copyright 1985-2009, American Megatrends, Inc.          **
//**                                                                        **
//**                          All Rights Reserved.                          **
//**                                                                        **
//**             5555 Oakbrook Pkwy, Suite 200, Norcross, GA 30093          **
//**                                                                        **
//**                          Phone (770)-246-8600                          **
//**                                                                        **
//****************************************************************************
//****************************************************************************