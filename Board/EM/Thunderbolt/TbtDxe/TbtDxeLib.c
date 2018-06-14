//*************************************************************************
//*************************************************************************
//**                                                                     **
//**        (C)Copyright 1985-2012, American Megatrends, Inc.            **
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
// $Header: /Alaska/SOURCE/Modules/Thunderbolt/TbtDxe/TbtDxeLib.c 4     5/16/14 6:02p Barretlin $
//
// $Revision: 4 $
//
// $Date: 5/16/14 6:02p $
//*************************************************************************
// Revision History
// ----------------
//
//*************************************************************************
//---------------------------------------------------------------------------
// Include(s)
//---------------------------------------------------------------------------

#include <Efi.h>
#include <Token.h>
#include <Setup.h>
#include <AmiPeiLib.h>
#include <AmiDxeLib.h>
#include <AmiCspLib.h>

// Produced Protocols

// Consumed Protocols

//---------------------------------------------------------------------------
// Constant, Macro and Type Definition(s)
//---------------------------------------------------------------------------
// Constant Definition(s)

// Macro Definition(s)

// Type Definition(s)

// Function Prototype(s)

//---------------------------------------------------------------------------
// Variable and External Declaration(s)
//---------------------------------------------------------------------------
// Variable Declaration(s)

// GUID Definition(s)

// Protocol Definition(s)

// External Declaration(s)

// Function Definition(s)

//<AMI_PHDR_START>
//----------------------------------------------------------------------------
//
// Procedure:   TbtProtectedPciDevice
//
// Description: This function is called by PCI Bus Driver before configuring
//              or disabling any PCI device. This function should examine the
//              Vendor/Device ID or PCI Bus, Device and Function numbers to
//              make sure it is not a south bridge device or any other device
//              which should no be configured by PCI Bus Driver.
//
// Input:       *PciDevice - Pointer to PCI Device Info structure.
//
// Output:      EFI_STATUS
//                  EFI_SUCCESS     - SKIP this device, do not touch
//                                    PCI Command register.
//                  EFI_UNSUPPORTED - DON'T SKIP this device do complete
//                                    enumeration as usual.
//----------------------------------------------------------------------------
//<AMI_PHDR_END>
EFI_STATUS TbtProtectedPciDevice (
  IN PCI_DEV_INFO *PciDevice )
{
    AMI_TBT_PLATFORM_POLICY_PROTOCOL  *gAmiTbtPlatformPolicy = NULL;
    EFI_GUID      gOemTbtProtocolGuid = AMI_TBT_PLATFROM_POLICY_PROTOCOL_GUID;
    EFI_STATUS    Status;
    UINT8         TBus = TBT_UP_PORT_BUS;
    UINT8         TDev = TBT_UP_PORT_DEV;
    UINT8         TFun = TBT_UP_PORT_FUNC;

    TRACE((-1, "\nTbtDxe: TbtProtectedPciDevice Entry !!!\n"));
    Status = pBS->LocateProtocol( &gOemTbtProtocolGuid, \
                                  NULL, \
                                  &gAmiTbtPlatformPolicy);
    if (EFI_ERROR(Status) || (!(gAmiTbtPlatformPolicy->TbtEnable))){
        return EFI_UNSUPPORTED;
    }

    if ((!EFI_ERROR(Status)) && (gAmiTbtPlatformPolicy->TbtAICSupport == 1)){
        if (gAmiTbtPlatformPolicy->Dev == 0x1c){
            TFun   = gAmiTbtPlatformPolicy->Fun;
        } else {
            TBus   = gAmiTbtPlatformPolicy->Bus;
            TDev   = gAmiTbtPlatformPolicy->Dev;
            TFun   = gAmiTbtPlatformPolicy->Fun;
        }
    }
    TRACE((-1, "TbtDxe: PciDevice @B:%x|D:%x|F:%x !!!\n", PciDevice->Address.Addr.Bus, PciDevice->Address.Addr.Device, PciDevice->Address.Addr.Function));
#if defined TBT_PCIBUS_SKIP && TBT_PCIBUS_SKIP == 1
    while ((PciDevice->Type != tPciRootBrg) && (PciDevice->ParentBrg != NULL)) {
        PciDevice = PciDevice->ParentBrg;
        if (PciDevice->Address.Addr.Bus != TBus) continue;
        if (PciDevice->Address.Addr.Device != TDev) continue;
        if (PciDevice->Address.Addr.Function != TFun) continue;
    
        TRACE((-1, "TbtDxe: Skip thunderbolt device before PCI BUS assign resource.\n"));
        return EFI_SUCCESS;
    }
#endif

  return EFI_UNSUPPORTED;
}

//<AMI_PHDR_START>
//----------------------------------------------------------------------------
//
// Procedure:   TbtDxeInvokeSmiHandler
//
// Description: Invoke SW SMI befor boot for reaource adjust.
//
// Input:       None
//
// Output:      None
//----------------------------------------------------------------------------
//<AMI_PHDR_END>
VOID TbtDxeInvokeSmiHandler(){
    AMI_TBT_PLATFORM_POLICY_PROTOCOL  *gAmiTbtPlatformPolicy = NULL;
    EFI_GUID      gOemTbtProtocolGuid = AMI_TBT_PLATFROM_POLICY_PROTOCOL_GUID;
    EFI_STATUS    Status;
	
    TRACE((-1, "TbtDxe: TbtDxeInvokeSmiHandler\n"));
	Status = pBS->LocateProtocol( &gOemTbtProtocolGuid, \
                                  NULL, \
                                  &gAmiTbtPlatformPolicy);
    if ((!EFI_ERROR(Status)) && (gAmiTbtPlatformPolicy->TbtEnable)){
        IoWrite8 (SW_SMI_IO_ADDRESS, TBT_SWSMI_VALUE); //trigger SwSMI for Thunderbolt
    }
}

#if defined ULT_SUPPORT && ULT_SUPPORT == 1
//<AMI_PHDR_START>
//----------------------------------------------------------------------------
//
// Procedure:   IsULTPchSeries
//
// Description: This function is to get PCH series is ULT series or not
//
// Input:       None
//
// Output:      None
//----------------------------------------------------------------------------
//<AMI_PHDR_END>
BOOLEAN
IsULTPchSeries( VOID ){
    UINT16   PchDeviceId;
    
    PchDeviceId = MmPciRead16 (0x00, LPC_DEVICE, LPC_FUNC, 0x02);
    switch(PchDeviceId){
       case 0x9C40:   ///< LynxPoint LP Unfuse
       case 0x9C41:   ///< LynxPoint LP Mobile Super SKU
       case 0x9C42:   ///< LynxPoint LP Mobile TBD SKU
       case 0x9C43:   ///< LynxPoint LP Mobile Premium SKU
       case 0x9C44:   ///< LynxPoint LP Mobile TBD SKU
       case 0x9C45:   ///< LynxPoint LP Mobile Mainstream SKU
       case 0x9C46:   ///< LynxPoint LP Mobile TBD SKU
       case 0x9C47:   ///< LynxPoint LP Mobile Value SKU
       case 0x9CC1:   ///< WildcatPoint LP Mobile Super SKU HSW
       case 0x9CC2:   ///< WildcatPoint LP Mobile Super SKU BDW U
       case 0x9CC3:   ///< WildcatPoint LP Mobile Premium SKU BDW U
       case 0x9CC4:   ///< WildcatPoint LP Mobile TBD SKU
       case 0x9CC5:   ///< WildcatPoint LP Mobile Base SKU BDW U
       case 0x9CC6:   ///< WildcatPoint LP Mobile Super SKU BDW Y
       case 0x9CC7:   ///< WildcatPoint LP Mobile Premium SKU BDW Y
       case 0x9CC8:   ///< WildcatPoint LP Mobile TBD SKU
       case 0x9CC9:   ///< WildcatPoint LP Mobile Base SKU BDW Y
       case 0x9CCA:   ///< WildcatPoint LP Mobile TBD SKU
       case 0x9CCB:   ///< WildcatPoint LP Mobile Performance SKU
           return TRUE;
    }
    return FALSE;
}
#endif

//*************************************************************************
//*************************************************************************
//**                                                                     **
//**        (C)Copyright 1985-2012, American Megatrends, Inc.            **
//**                                                                     **
//**                       All Rights Reserved.                          **
//**                                                                     **
//**      5555 Oakbrook Parkway, Suite 200, Norcross, GA 30093           **
//**                                                                     **
//**                       Phone: (770)-246-8600                         **
//**                                                                     **
//*************************************************************************
//*************************************************************************
