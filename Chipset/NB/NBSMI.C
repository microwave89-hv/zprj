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
// $Header: /Alaska/BIN/Chipset/Intel/NorthBridge/Haswell/Intel SystemAgent NB Chipset/NB SMI/NBSMI.C 5     10/14/12 12:17a Jeffch $
//
// $Revision: 5 $
//
// $Date: 10/14/12 12:17a $
//*************************************************************************
// Revision History
// ----------------
// $Log: /Alaska/BIN/Chipset/Intel/NorthBridge/Haswell/Intel SystemAgent NB Chipset/NB SMI/NBSMI.C $
// 
// 5     10/14/12 12:17a Jeffch
// [TAG]         None
// [Severity]    Important
// [Description] Follow MahoBay Update.
// [Files]       NBSMI.c, NBSMI.Dxe
// 
// 3     6/14/12 4:36a Yurenlai
// [TAG]           None
// [Category]      Improvement
// [Description]   Fixed PEG PERR log lost issue.
// [Description]   NBSMI.C
// 
// 2     4/05/12 3:18a Yurenlai
// [TAG]  		EIP87103
// [Category]  	Spec Update
// [Severity]  	Important
// [Description]  	Change for SystemAgent RefCode Revision: 0.5.5 .
// [Files]  		NBDxe.c, NBPEI.c, NBSMI.C, NBGeneric.cm NB.sd, NBSetup.c,
// GetSetupData.c, NbSetupData.h
// 
// 1     2/08/12 4:34a Yurenlai
// Intel Haswell/NB eChipset initially releases.
// 
//*************************************************************************
//<AMI_FHDR_START>
//
// Name:        NBSMI.c
//
// Description: This file contains code for all North Bridge SMI events
//
//<AMI_FHDR_END>
//*************************************************************************

//----------------------------------------------------------------------------
// Include(s)
//----------------------------------------------------------------------------

#include <Token.h>
#include <AmiDxeLib.h>
#include <Protocol\SmmBase.h>
#include <Protocol\SmmSwDispatch.h>
#include <Protocol\SmmSxDispatch.h>
#include <Protocol\NBPlatformData.h>
#include <AmiCspLib.h>
#include <Setup.h>
#if NB_ERROR_LOG_SUPPORT
#include <Edk\Foundation\Framework\Protocol\SmmIchnDispatch\SmmIchnDispatch.h>
#include <Protocol\SmbiosElogSupport.h>
#include <NBSMI.h>
#endif
//----------------------------------------------------------------------------
// Constant, Macro and Type Definition(s)
//----------------------------------------------------------------------------
// Constant Definition(s)

// Macro Definition(s)

// Type Definition(s)

// Function Prototype(s)

//----------------------------------------------------------------------------
// Variable and External Declaration(s)
//----------------------------------------------------------------------------
// Variable Declaration(s)
static BOOLEAN      gEccErrHandleEnable = FALSE;
static BOOLEAN      gPegErrHandleEnable = FALSE;
NB_ASL_BUFFER       *gNbAslBufPtr = NULL;
NB_SETUP_DATA       *gNbSetupData = NULL;
// GUID Definition(s)
#if NB_ERROR_LOG_SUPPORT
EFI_GUID gNbErrorLogDispatchProtocolGuid        = EFI_NB_ERROR_LOG_DISPATCH_PROTOCOL_GUID;
EFI_GUID gIchnDispatchProtocolGuid              = EFI_SMM_ICHN_DISPATCH_PROTOCOL_GUID;
#endif
// Protocol Definition(s)

// External Declaration(s)

// Function Definition(s)
//----------------------------------------------------------------------------
// Variable and External Declaration(s)
//----------------------------------------------------------------------------
// Variable Declaration(s)
#if NB_ERROR_LOG_SUPPORT
NB_ERROR_LOG_DISPATCH_LINK  *gNbErrorLogDispatchHead = 0, *gNbErrorLogDispatchTail = 0;

UINT32 NBPcieBridge[] = 
{
  {(UINT32)NB_PCIE_CFG_ADDRESS(PCIEBRN_BUS, PCIEBRN_DEV, PCIEBRN_FUN, PCI_VID)},
  {(UINT32)NB_PCIE_CFG_ADDRESS(PCIEBRN_BUS, PCIEBRN_DEV, PCIEBRN_FUN1, PCI_VID)},
  {(UINT32)NB_PCIE_CFG_ADDRESS(PCIEBRN_BUS, PCIEBRN_DEV, PCIEBRN_FUN2, PCI_VID)},
  {0xFFFFFFFF}
};

EFI_STATUS NbErrorLogRegister (
    IN EFI_NB_ERROR_LOG_DISPATCH_PROTOCOL   *This,
    IN EFI_NB_ERROR_LOG_DISPATCH            Function,
    OUT EFI_HANDLE                          *Handle 
);

EFI_STATUS NbErrorLogUnregister (
    IN EFI_NB_ERROR_LOG_DISPATCH_PROTOCOL   *This,
    IN EFI_HANDLE                           Handle 
);

EFI_NB_ERROR_LOG_DISPATCH_PROTOCOL gEfiNbErrorLogDispatchProtocol = \
                                   {NbErrorLogRegister, NbErrorLogUnregister};

NB_ERROR_INFO NbErrorInfo;
UINT32        DevBaseAddr = 0;

#if NB_ECC_ERROR_LOG_SUPPORT
EFI_STATUS NBEccErrLogHandle(VOID);
#endif

#endif

#if NB_ERROR_LOG_SUPPORT
//<AMI_PHDR_START>
//----------------------------------------------------------------------------
//
// Procedure:   AddLink
//
// Description: Create and add link to specified list.
//
// Parameters:  Size -
//              Head - 
//              Tail -
//
// Returns:     VOID Pointer
//
// Modified:
//
// Referrals:   SmmAllocatePool
//
// Notes:       Here is the control flow of this function:
//              1. Allocate Link in Smm Pool.
//              2. Add Link to end.
//              3. Return Link address.
//
//----------------------------------------------------------------------------
//<AMI_PHDR_END>

VOID * AddLink (
    IN UINT32       Size,
    IN VOID         **Head,
    IN VOID         **Tail )
{
    VOID *Link;

    if (pSmst->SmmAllocatePool(0, Size, &Link) != EFI_SUCCESS) return 0;

    ((GENERIC_LINK*)Link)->Link = 0;
    if (!*Head) {
        *Head = *Tail = Link;
    } else {
        ((GENERIC_LINK*)*Tail)->Link = Link;
        *Tail = Link;
    }

    return Link;
}

//<AMI_PHDR_START>
//----------------------------------------------------------------------------
//
// Procedure:   RemoveLink
//
// Description: Remove link from specified list.
//
// Parameters:  Handle - EFI Handle
//              Head -
//              Tail -
//
// Returns:     BOOLEAN
//                  TRUE if link was removed. FALSE if link not in the list.
//
// Modified:
//
// Referrals:   SmmFreePool
//
// Notes:       Here is the control flow of this function:
//              1. Search link list for Link.
//              2. Remove link from list.
//              3. Free link.
//
//----------------------------------------------------------------------------
//<AMI_PHDR_END>

BOOLEAN RemoveLink (
    IN EFI_HANDLE   Handle,
    IN VOID         **Head,
    IN VOID         **Tail )
{
    GENERIC_LINK *PrevLink,*Link;

    PrevLink = *Head;

    // Is link first. Link address is the same as the Handle. 
    if (((GENERIC_LINK*)*Head) == Handle) {
        if (PrevLink == *Tail) *Tail = 0; // If Tail = Head, then 0.
        *Head = PrevLink->Link;
        pSmst->SmmFreePool(PrevLink);
        return TRUE;
    }

    // Find Link.
    for (Link=PrevLink->Link; Link; PrevLink=Link, Link=Link->Link) {
        if (Link == Handle) {   // Link address is the same as the Handle.
            if (Link == *Tail) *Tail = PrevLink;
            PrevLink->Link = Link->Link;
            pSmst->SmmFreePool(Link);
            return TRUE;
        }
    }

    return FALSE;
}

//<AMI_PHDR_START>
//----------------------------------------------------------------------------
//
// Procedure:   EfiNbErrorLogEnRegister
//
// Description: Register a Link on NbErrorLog enable SMI.
//
// Parameters:  This - 
//              Function -
//              Context - 
//              
//
// Returns:     Handle -
//              EFI_STATUS
//
// Modified:    gNbErrorLogDispatchHead, gNbErrorLogDispatchTail
//
// Referrals:   AddLink
//
// Notes:       Here is the control flow of this function:
//              1. Verify if Context if valid. If invalid,
//                 return EFI_INVALID_PARAMETER.
//              2. Allocate structure and add to link list.
//              3. Fill link.
//              4. Enable Smi Source.
//
//----------------------------------------------------------------------------
//<AMI_PHDR_END>

EFI_STATUS NbErrorLogRegister (
    IN EFI_NB_ERROR_LOG_DISPATCH_PROTOCOL   *This,
    IN EFI_NB_ERROR_LOG_DISPATCH            Function,
    OUT EFI_HANDLE                  *Handle )
{
    NB_ERROR_LOG_DISPATCH_LINK *NewLink;

    NewLink = AddLink( sizeof(NB_ERROR_LOG_DISPATCH_LINK), \
                       &gNbErrorLogDispatchHead, \
                       &gNbErrorLogDispatchTail );
    if (!NewLink) return EFI_OUT_OF_RESOURCES;

    NewLink->Function = Function;
    *Handle = NewLink;

#if NB_ECC_ERROR_LOG_SUPPORT
    if(((READ_PCI16_NB(0xC8) & (BIT00 | BIT01)) != 0) && gEccErrHandleEnable)
    {
        NBEccErrLogHandle();
    }
#endif

    return EFI_SUCCESS;
}

//<AMI_PHDR_START>
//----------------------------------------------------------------------------
//
// Procedure:   NbErrorLogUnregister
//
// Description: Unregister a Link on NbErrorLog enable SMI.
//
// Parameters:  This -
//              Handle -
//
// Returns:     EFI_STATUS
//
// Modified:    gNbErrorLogDispatchHead, gNbErrorLogDispatchTail
//
// Referrals:   RemoveLink
//
// Notes:       Here is the control flow of this function:
//              1. Remove link. If no link, return EFI_INVALID_PARAMETER.
//              2. Disable SMI Source if no other handlers using source.
//              3. Return EFI_SUCCESS.
//
//----------------------------------------------------------------------------
//<AMI_PHDR_END>

EFI_STATUS NbErrorLogUnregister (
    IN EFI_NB_ERROR_LOG_DISPATCH_PROTOCOL   *This,
    IN EFI_HANDLE                   Handle )
{
    if (!RemoveLink(Handle, &gNbErrorLogDispatchHead, &gNbErrorLogDispatchTail))
        return EFI_INVALID_PARAMETER;
    return EFI_SUCCESS;
}
#endif
//<AMI_PHDR_START>
//----------------------------------------------------------------------------
//
// Procedure:   GetNbSmiContext
//
// Description: This is a template NB SMI GetContext for Porting.
//
// Input:       None
//
// Output:      BOOLEAN
//
// Notes:       Here is the control flow of this function:
//              1. Check if NB Smi source.
//              2. If yes, return TRUE.
//              3. If not, return FALSE.
//----------------------------------------------------------------------------
//<AMI_PHDR_END>

BOOLEAN GetNbSmiContext (VOID)
{
        return FALSE;
}

#if NB_ERROR_LOG_SUPPORT
//<AMI_PHDR_START>
//----------------------------------------------------------------------------
//
// Procedure: NBPcieErrLogHandle
//
// Description: Init NB PCIE Error devices log.
//
// Input: VOID
//
// Output: VOID
//
//----------------------------------------------------------------------------
//<AMI_PHDR_END>
VOID NBPcieErrLogHandle (VOID)
{
  EFI_STATUS Status = EFI_SUCCESS;
  NB_ERROR_LOG_DISPATCH_LINK       *Link;
  UINT8      CapPtr;
  UINT16     PciStatus;
  UINT16     PcieStatus;
  UINT16     DeviceStatus;

//  if (READ_IO8(NMI_SC_PORT) & BIT7) // SERR#_NMI_STS?
//  {               

     MemSet((VOID*)&NbErrorInfo, sizeof(NB_ERROR_INFO), 0);

     PciStatus = READ_MEM16(DevBaseAddr + 0x06);
     PcieStatus = READ_MEM16(DevBaseAddr + 0x1E);

     CapPtr = NbFindCapPtr(DevBaseAddr, 0x10);
     if (CapPtr != 0)
       DeviceStatus = READ_MEM16(DevBaseAddr + CapPtr + 0x0A);
 
     if ((PciStatus & (BIT8 | BIT15)) || (PcieStatus & (BIT8 | BIT15)))
       NbErrorInfo.PcieErrorInfo.ParityError = TRUE;
     else
       NbErrorInfo.PcieErrorInfo.ParityError = FALSE;

     if (READ_IO8(NMI_SC_PORT) & BIT7) // SERR#_NMI_STS?
     {  
        if ((PciStatus & BIT14) || (PcieStatus & BIT14) || ((CapPtr != 0) && (DeviceStatus & 0x7)))
          NbErrorInfo.PcieErrorInfo.SystemError = TRUE;
        else
          NbErrorInfo.PcieErrorInfo.SystemError = FALSE;
     }

     if ((NbErrorInfo.PcieErrorInfo.ParityError) || (NbErrorInfo.PcieErrorInfo.SystemError)) 
     {
       NbErrorInfo.PcieErrorInfo.Bus = (DevBaseAddr >> 20) & ((UINT8)((PCIEX_LENGTH >> 20) - 1));
       NbErrorInfo.PcieErrorInfo.Dev = (DevBaseAddr >> 15) & 0x1F;
       NbErrorInfo.PcieErrorInfo.Fun = (DevBaseAddr >> 12) & 0x07;
       NbErrorInfo.PcieErrorInfo.VendorId   = READ_MEM16(DevBaseAddr + 0x00);
       NbErrorInfo.PcieErrorInfo.DeviceId   = READ_MEM16(DevBaseAddr + 0x02);
       NbErrorInfo.PcieErrorInfo.PciCommand = READ_MEM16(DevBaseAddr + 0x04);
       NbErrorInfo.PcieErrorInfo.PciCCode   = READ_MEM16(DevBaseAddr + 0x0A);
       NbErrorInfo.PcieErrorInfo.BridgeControl = READ_MEM16(DevBaseAddr + 0x3E);
       NbErrorInfo.PcieErrorInfo.Version    = READ_MEM8(DevBaseAddr + CapPtr + 0x02) & 0x0F;
       NbErrorInfo.PcieErrorInfo.PortType   = (UINT32)((READ_MEM8(DevBaseAddr + CapPtr + 0x02) & 0xF0) >> 4);

       if (CapPtr != 0) {
         NbErrorInfo.PcieErrorInfo.Correctable = (DeviceStatus & BIT0)? TRUE : FALSE;
         NbErrorInfo.PcieErrorInfo.NonFatal = (DeviceStatus & BIT1)? TRUE : FALSE;
         NbErrorInfo.PcieErrorInfo.Fatal = (DeviceStatus & BIT2)? TRUE : FALSE;
       }

       NbErrorInfo.ErrorType = NbPcieError; // PCIE Error

       // Clear Error status
       WRITE_MEM16(DevBaseAddr + 0x06, PciStatus);
       WRITE_MEM16(DevBaseAddr + 0x1E, PcieStatus);

       if (CapPtr != 0)
         // Clear Error Status
         WRITE_MEM16(DevBaseAddr + CapPtr + 0x0A, DeviceStatus);

       // Clear DMISERR
       SET_IO16((TCO_BASE_ADDRESS + 0x04), BIT12);

       // Clear SERR#_NMI_STS & NMI2SMI_STS by set Port 61h[2] = 1 then set it to 0.
       if(NbErrorInfo.PcieErrorInfo.SystemError) 
       {
          SET_IO8(NMI_SC_PORT, BIT02);
          RESET_IO8(NMI_SC_PORT, BIT02);
       }

       for(Link = gNbErrorLogDispatchHead; Link; Link = Link->Link) {
         Link->Function(Link, NbErrorInfo);
       }
     }
//   }// SERR#_NMI_STS?
}

//<AMI_PHDR_START>
//----------------------------------------------------------------------------
//
// Procedure:   GetNbPcieContext
//
// Description: The function will check PCIE error event.
//
// Input:       N/A
//
// Output:      EFI_SUCCESS - ECC error event generated.
//              Other - No ECC error event
//
//----------------------------------------------------------------------------
//<AMI_PHDR_END>

BOOLEAN GetNbPcieContext(
)
{
  UINT8      i;

  if(!gPegErrHandleEnable) return FALSE;

  for (i = 0; NBPcieBridge[i] != 0xFFFFFFFF; i++)
  {
    DevBaseAddr = NBPcieBridge[i];
    if (READ_MEM32(DevBaseAddr) == 0xFFFFFFFF)
      continue;

    if(((READ_MEM16(DevBaseAddr + PCI_CMD) & (BIT6 | BIT8)) == (BIT6 | BIT8)) &&
      (((READ_MEM16(DevBaseAddr + 0x06) & (BIT08 | BIT14 | BIT15)) != 0) ||
       ((READ_MEM16(DevBaseAddr + 0x1E) & (BIT08 | BIT14 | BIT15)) != 0)))
    {
      return TRUE;
    }
  }
  return FALSE;
}
#endif

#if NB_ECC_ERROR_LOG_SUPPORT
//<AMI_PHDR_START>
//----------------------------------------------------------------------------
//
// Procedure:   EccEnableFunction
//
// Description: The function will check what ECC feature is enable or disable.
//
// Input:       N/A
//
// Output:      EFI_SUCCESS - ECC feature is support.
//              EFI_UNSUPPORTED - ECC feature is not support
//
//----------------------------------------------------------------------------
//<AMI_PHDR_END>
EFI_STATUS EccEnableFunction(VOID)
{
    if (((READ_MEM32_MCH(0x5004) & (BIT24 | BIT25)) != 0) || \
        ((READ_MEM32_MCH(0x5008) & (BIT24 | BIT25)) != 0))
    {
        RW_MEM32_MCH(0x40B8, 0, (BIT14 | BIT16 | BIT17));
        RW_MEM32_MCH(0x44B8, 0, (BIT14 | BIT16 | BIT17));

        // Disable Error and SCI Commands
        RW_PCI16_NB(0xCA, 0, (BIT00 | BIT01));
        RW_PCI16_NB(0xCE, 0, (BIT00 | BIT01));

        // Enable SMI Command
//        RW_PCI16_NB(0xC8, (BIT00 | BIT01), 0);
        RW_PCI16_NB(0xCC, (BIT00 | BIT01), 0);

        return EFI_SUCCESS;
    }

    return EFI_UNSUPPORTED;
}
//<AMI_PHDR_START>
//----------------------------------------------------------------------------
//
// Procedure:   GetNbEccContext
//
// Description: The function will check ECC error event.
//
// Input:       N/A
//
// Output:      EFI_SUCCESS - ECC error event generated.
//              Other - No ECC error event
//
//----------------------------------------------------------------------------
//<AMI_PHDR_END>

BOOLEAN GetNbEccContext(VOID)
{
    if (gEccErrHandleEnable)
    {
        if (((READ_PCI16_NB(0xCC) & (BIT00 | BIT01)) != 0) && 
            ((READ_PCI16_NB(0xC8) & (BIT00 | BIT01)) != 0))
        {
            return TRUE;
        }
    }

    return FALSE;
}

//<AMI_PHDR_START>
//----------------------------------------------------------------------------
//
// Procedure:   NBEccErrLogHandle
//
// Description: This function handles ECC error.
//
// Input:       *This - NB SMI Context pointer
//
// Output:      EFI_SUCCESS - ECC error is handled.
//
//----------------------------------------------------------------------------
//<AMI_PHDR_END>
EFI_STATUS NBEccErrLogHandle(VOID)
{

    NB_ERROR_INFO                    NbErrorInfo;
    NB_ERROR_LOG_DISPATCH_LINK       *Link;

    MemSet((VOID*)&NbErrorInfo, sizeof(NB_ERROR_INFO), 0);

    if ((READ_MEM32_MCH(0x4CC8) & (BIT00 | BIT01)) != 0)
    {
        NbErrorInfo.EccErrorInfo.EccErrLog0 = READ_MEM32_MCH(0x4CC8);
        NbErrorInfo.EccErrorInfo.EccErrLog1 = READ_MEM32_MCH(0x4CCC);
    }

    // Channel 0
    if ((READ_MEM32_MCH(0x40C8) & (BIT00 | BIT01)) != 0)
    {
        NbErrorInfo.EccErrorInfo.Ch0_EccErrLog0 = READ_MEM32_MCH(0x40C8);
        NbErrorInfo.EccErrorInfo.Ch0_EccErrLog1 = READ_MEM32_MCH(0x40CC);
        // [28:27] 00 or 01 = DimmNum 0, 10 or 11 = DimmNum 1
        NbErrorInfo.EccErrorInfo.EccErrDimmNum = (READ_MEM32_MCH(0x40C8) & BIT28) ? 1 : 0;
    }

    // Channel 1
    if ((READ_MEM32_MCH(0x44C8) & (BIT00 | BIT01)) != 0)
    {
        NbErrorInfo.EccErrorInfo.Ch1_EccErrLog0 = READ_MEM32_MCH(0x44C8);
        NbErrorInfo.EccErrorInfo.Ch1_EccErrLog1 = READ_MEM32_MCH(0x44CC);
        // [28:27] 00 or 01 = DimmNum 0, 10 or 11 = DimmNum 1
        NbErrorInfo.EccErrorInfo.EccErrDimmNum = (READ_MEM32_MCH(0x44C8) & BIT28) ? 3 : 2;
    }

    if ((READ_PCI16_NB(0xC8) & BIT00) != 0)
        NbErrorInfo.EccErrorInfo.Correctable = 1;

    if ((READ_PCI16_NB(0xC8) & BIT01) != 0)
        NbErrorInfo.EccErrorInfo.UnCorrectable = 1;

    NbErrorInfo.ErrorType = NbEccError; // Ecc Error

    for(Link = gNbErrorLogDispatchHead; Link; Link = Link->Link) {
       Link->Function(Link, NbErrorInfo);
    }

    RW_PCI16_NB(0xC8, (BIT00 | BIT01), 0);

#if ECC_MULTI_BIT_TYPE_HANG == 1
    if (NbErrorInfo.EccErrorInfo.UnCorrectable == 1){
         EFI_DEADLOOP()
    }
#endif

    return EFI_SUCCESS;
}
#endif

#if NB_ERROR_LOG_SUPPORT
//<AMI_PHDR_START>
//----------------------------------------------------------------------------
//
// Procedure: NBErrLogHandler
//
// Description: North Bridge error logging handler.
//
// Input: DispatchHandle  - Handle of dispatch function, for when interfacing
//                          with the parent SMM driver, will be the address of linked
//                          list link in the call back record.
//        DispatchContext - Pointer to the dispatch function's context.
//
// Output: None
//
//----------------------------------------------------------------------------
//<AMI_PHDR_END>
VOID NBErrLogHandler (
    IN EFI_HANDLE                       DispatchHandle,
    IN EFI_SMM_ICHN_DISPATCH_CONTEXT    *DispatchContext
)
{
//#if NB_PCIE_ERROR_LOG_SUPPORT
//    if (GetNbPcieContext()) NBPcieErrLogHandle();
//#endif
}

#endif

//<AMI_PHDR_START>
//----------------------------------------------------------------------------
//
// Procedure:   NbSmiHandler
//
// Description: This is a template NB SMI Handler for Porting.
//
// Input:       None
//
// Output:      None
//----------------------------------------------------------------------------
//<AMI_PHDR_END>

VOID NbSmiHandler (VOID)
{

}

//<AMI_PHDR_START>
//----------------------------------------------------------------------------
//
// Procedure:   NbSwSmiIgfxGetSetupHandler
//
// Description: This is a NB software SMI Handler for IGFX int15 get setup data.
//
// Input:       DispatchHandle  - EFI Handle
//              DispatchContext - Pointer to the EFI_SMM_SW_DISPATCH_CONTEXT
//
// Output:      None
//----------------------------------------------------------------------------
//<AMI_PHDR_END>

VOID NbSwSmiIgfxGetSetupHandler (
    IN EFI_HANDLE                   DispatchHandle,
    IN EFI_SMM_SW_DISPATCH_CONTEXT  *DispatchContext )
{
    EFI_SMM_CPU_SAVE_STATE  *pCpuSaveState = pSmst->CpuSaveState;
    UINTN                   Cpu = pSmst->CurrentlyExecutingCpu - 1;
    UINT8                   RegBL;

    // Nb int 15 go to here
    RegBL = (UINT8)pCpuSaveState[Cpu].Ia32SaveState.EBX;

    switch (RegBL) {
        case IGFX_LCD_PANEL_TYPE:  // 0x80
             pCpuSaveState[Cpu].Ia32SaveState.EBX = (UINT8)gNbSetupData->LcdPanelType;
             break;
        case IGFX_LCD_PANEL_SCALING: // 0x81
             pCpuSaveState[Cpu].Ia32SaveState.EBX = (UINT8)gNbSetupData->LcdPanelScaling;
             break;
        case IGFX_BOOT_TYPE: // 0x82
             pCpuSaveState[Cpu].Ia32SaveState.EBX = (UINT8)gNbSetupData->IgdBootType;
             break;
        case IGFX_BACKLIGHT_TYPE: // 0x83
             pCpuSaveState[Cpu].Ia32SaveState.EBX = (UINT8)gNbSetupData->IgdLcdBlc;
             break;
        case IGFX_LFP_PANEL_COLOR_DEPTH_TYPE: // 0x84
             pCpuSaveState[Cpu].Ia32SaveState.EBX = (UINT8)gNbSetupData->LfpColorDepth;
             break;
        case IGFX_EDP_ACTIVE_LFP_CONFIG_TYPE: // 0x85
             pCpuSaveState[Cpu].Ia32SaveState.EBX = (UINT8)gNbSetupData->ActiveLFP;
             break;
        case IGFX_PRIMARY_DISPLAY_TYPE: // 0x86
             pCpuSaveState[Cpu].Ia32SaveState.EBX = (UINT8)gNbSetupData->PrimaryDisplay;
             break;
        case IGFX_DISPLAY_PIPE_B_TYPE: // 0x87
             pCpuSaveState[Cpu].Ia32SaveState.EBX = (UINT8)gNbSetupData->DisplayPipeB;
             break;
        case IGFX_SDVO_PANEL_TYPE: // 0x88
             pCpuSaveState[Cpu].Ia32SaveState.EBX = (UINT8)gNbSetupData->SdvoPanelType;
             break;
        default:
             break;
    } // switch

}

//<AMI_PHDR_START>
//----------------------------------------------------------------------------
//
// Procedure:   NbSxSmiHandler
//
// Description: This is a template NB Sx SMI Handler for Porting.
//
// Input:       DispatchHandle  - EFI Handle
//              DispatchContext - Pointer to the EFI_SMM_SX_DISPATCH_CONTEXT
//
// Output:      None
//----------------------------------------------------------------------------
//<AMI_PHDR_END>

VOID NbSxSmiHandler (
    IN EFI_HANDLE                   DispatchHandle,
    IN EFI_SMM_SX_DISPATCH_CONTEXT  *DispatchContext )
{
/*
    // SMBAVUMA Workaround
    WRITE_IO8(0x3c4, 0x01);
    SET_IO8(0x3c5, 0x20);
*/
}

//<AMI_PHDR_START>
//----------------------------------------------------------------------------
//
// Procedure:   NbChildDispatcher
//
// Description: North Bridge SMM Child Dispatcher Handler.
//
// Input:       SmmImageHandle - 
//              *CommunicationBuffer - OPTIONAL
//              *SourceSize - OPTIONAL
//
// Output:      EFI_STATUS
//
// Modified:
//
// Referrals:   EfiSmmSwDispatch EfiSmmSxDispatch 
//
// Notes:       Here is the control flow of this function:
//              1. Read SMI source status registers.
//              2. If source, call handler.
//              3. Repeat #2 for all sources registered.
//----------------------------------------------------------------------------
//<AMI_PHDR_END>

EFI_STATUS NbChildDispatcher (
    IN EFI_HANDLE       SmmImageHandle,
    IN OUT VOID         *CommunicationBuffer OPTIONAL,
    IN OUT UINTN        *SourceSize OPTIONAL )
{
    if (GetNbSmiContext()) NbSmiHandler();
#if NB_ECC_ERROR_LOG_SUPPORT
    if (GetNbEccContext()) NBEccErrLogHandle();
#endif
#if NB_PCIE_ERROR_LOG_SUPPORT
    if (GetNbPcieContext()) NBPcieErrLogHandle();
#endif
    return EFI_HANDLER_SUCCESS;
}

//----------------------------------------------------------------------------

//<AMI_PHDR_START>
//----------------------------------------------------------------------------
//
// Procedure:   InSmmFunction
//
// Description: Installs North Bridge SMM Child Dispatcher Handler.
//
// Input:       ImageHandle  - Image handle
//              *SystemTable - Pointer to the system table
//
// Output:      EFI_STATUS
//----------------------------------------------------------------------------
//<AMI_PHDR_END>

EFI_STATUS InSmmFunction (
    IN EFI_HANDLE           ImageHandle,
    IN EFI_SYSTEM_TABLE     *SystemTable )
{
    EFI_STATUS                        Status;
    EFI_STATUS                        IchnDispatchStatus = EFI_SUCCESS;
    EFI_SMM_SW_DISPATCH_PROTOCOL      *pSwDispatch;
    EFI_SMM_SX_DISPATCH_PROTOCOL      *pSxDispatch;
    EFI_SMM_SW_DISPATCH_CONTEXT       SwContext = {NB_SWSMI_IGFX_GET_SETUP};
    EFI_SMM_SX_DISPATCH_CONTEXT       SxContext = {SxS3, SxEntry};
    EFI_HANDLE                        DummyHandle = NULL;
    EFI_HANDLE                        Handle;
    EFI_SMM_BASE_PROTOCOL             *SmmBaseProtocol;
    EFI_GUID                          NbAslBufPtrGuid = NB_ASL_BUFFER_PTR_GUID;
    CHAR16                            NbAslBufPtrVar[] = \
                                                    NB_ASL_BUFFER_PTR_VARIABLE;
    UINTN                             VarSize = sizeof(UINT32);
    UINT32                            NbAslBufPtr;
    UINTN                             VariableSize = sizeof(NB_SETUP_DATA);
#if NB_ERROR_LOG_SUPPORT
    EFI_SMM_ICHN_DISPATCH_PROTOCOL    *IchnDispatch;
    EFI_SMM_ICHN_DISPATCH_CONTEXT     IchnContext;
#endif

    //
    // Get SETUP variables and change defaults for some boards.
    //

    Status = pRS->GetVariable( NbAslBufPtrVar, \
                               &NbAslBufPtrGuid, \
                               NULL, \
                               &VarSize, \
                               &NbAslBufPtr );
    if (!EFI_ERROR(Status)) gNbAslBufPtr = (NB_ASL_BUFFER *)NbAslBufPtr;

    Status = pBS->LocateProtocol( &gEfiSmmBaseProtocolGuid, \
                                  NULL, \
                                  &SmmBaseProtocol );
    if (EFI_ERROR(Status)) return Status;

    Status = SmmBaseProtocol->SmmAllocatePool( \
                            SmmBaseProtocol, \
                            EfiRuntimeServicesData, \
                            VariableSize, \
                            &gNbSetupData );
    if (!EFI_ERROR (Status)){
        GetNbSetupData( pRS, gNbSetupData, FALSE ); 
    } else {
        gNbSetupData->EccSupport = 0;
        gNbSetupData->LcdPanelType = 0;
        gNbSetupData->SdvoPanelType = 0;
        gNbSetupData->LcdPanelScaling = 0;
        gNbSetupData->IgdBootType = 0;
        gNbSetupData->DisplayPipeB = 0;
        gNbSetupData->IgdLcdBlc = 0;
        gNbSetupData->ActiveLFP = 1;
        gNbSetupData->LfpColorDepth = 0;
        gNbSetupData->PrimaryDisplay = 3;
    }

    Status  = pBS->LocateProtocol( &gEfiSmmSwDispatchProtocolGuid, \
                                   NULL, \
                                   &pSwDispatch );
    if (!EFI_ERROR(Status)) {

        if (READ_PCI32_IGD (R_SA_IGD_VID) != 0xFFFFFFFF) {

            Status  = pSwDispatch->Register( pSwDispatch, \
                                             NbSwSmiIgfxGetSetupHandler, \
                                             &SwContext, \
                                             &Handle );

        }
    }

    Status  = pBS->LocateProtocol( &gEfiSmmSxDispatchProtocolGuid, \
                                   NULL, \
                                   &pSxDispatch );
    if (!EFI_ERROR(Status)) {
        Status  = pSxDispatch->Register( pSxDispatch, \
                                         NbSxSmiHandler, \
                                         &SxContext, \
                                         &Handle );
    }

#if NB_ERROR_LOG_SUPPORT

    if (gNbSetupData->SmbiosLogging == 1)
    {

       Status = pBS->LocateProtocol ( &gIchnDispatchProtocolGuid, \
                                      NULL, \
                                      &IchnDispatch );

#if NB_ECC_ERROR_LOG_SUPPORT

        if(gNbSetupData->EccSupport)
        {
           if (!EFI_ERROR(Status))
           {
              IchnContext.Type = IchnMch; //TCO DMI SMI
              IchnDispatchStatus = IchnDispatch->Register( IchnDispatch, \
                                                     NBErrLogHandler, \
                                                     &IchnContext, \
                                                     &Handle );
              ASSERT_EFI_ERROR (IchnDispatchStatus);

              if (!EFI_ERROR(IchnDispatchStatus)) gEccErrHandleEnable = TRUE;
             // Enable ECC error log function
             //EccEnableFunction();
           }
        }

#endif

#if NB_PCIE_ERROR_LOG_SUPPORT

        if (!EFI_ERROR(Status))
        {
           IchnContext.Type = IchnNmi; //TCO NMI2 SMI
           IchnDispatchStatus = IchnDispatch->Register( IchnDispatch, \
                                                  NBErrLogHandler, \
                                                  &IchnContext, \
                                                  &Handle );
           ASSERT_EFI_ERROR (IchnDispatchStatus);

           if (!EFI_ERROR(IchnDispatchStatus)) gPegErrHandleEnable = TRUE;

        }

#endif 

   

//        pBS->FreePool( NBSetupData );

       Status = pBS->InstallProtocolInterface( &DummyHandle, \
                                               &gNbErrorLogDispatchProtocolGuid, \
                                               EFI_NATIVE_INTERFACE, \
                                               &gEfiNbErrorLogDispatchProtocol );
    } 
#endif

    // Register Callbacks
    SmmBaseProtocol->RegisterCallback( SmmBaseProtocol, \
                                       ImageHandle, \
                                       NbChildDispatcher, \
                                       FALSE, \
                                       FALSE );

    return EFI_SUCCESS;

}

//<AMI_PHDR_START>
//----------------------------------------------------------------------------
//
// Procedure:   InitializeNBSmm
//
// Description: Installs North Bridge SMM Child Dispatcher Handler.
//
// Input:       ImageHandle  - Image handle
//              *SystemTable - Pointer to the system table
//
// Output:      EFI_STATUS
//----------------------------------------------------------------------------
//<AMI_PHDR_END>

EFI_STATUS InitializeNBSmm (
    IN EFI_HANDLE           ImageHandle,
    IN EFI_SYSTEM_TABLE     *SystemTable )
{
    InitAmiLib(ImageHandle, SystemTable);
    return InitSmmHandler(ImageHandle, SystemTable, InSmmFunction, NULL);
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
