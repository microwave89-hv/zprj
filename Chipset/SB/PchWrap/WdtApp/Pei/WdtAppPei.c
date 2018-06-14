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
// $Header: /Alaska/BIN/Chipset/Intel/SouthBridge/LynxPoint/Intel Pch SB Chipset/PchWrap/WdtApp/WdtAppPei/WdtAppPei.c 1     2/08/12 8:34a Yurenlai $
//
// $Revision: 1 $
//
// $Date: 2/08/12 8:34a $
//*************************************************************************
// Revision History
// ----------------
// $Log: /Alaska/BIN/Chipset/Intel/SouthBridge/LynxPoint/Intel Pch SB Chipset/PchWrap/WdtApp/WdtAppPei/WdtAppPei.c $
// 
// 1     2/08/12 8:34a Yurenlai
// Intel Lynx Point/SB eChipset initially releases.
// 
//*************************************************************************

#include <Efi.h>
#include <Pei.h>
#include <Token.h>
#include <AmiPeiLib.h>
#include <AmiCspLib.h>

#include "PchAccess.h"
#include "WdtAppVariable.h"
#include <Ppi\Wdt\Wdt.h>
#include <PPI\ReadOnlyVariable.h>

#ifdef EFI_DEBUG
#define WDT_TIMEOUT_BETWEEN_PEI_DXE 30
#else
#define WDT_TIMEOUT_BETWEEN_PEI_DXE 10
#endif

EFI_GUID  gWdtPpiGuid = WDT_PPI_GUID;


//<AMI_PHDR_START>
//----------------------------------------------------------------------------
//
// Procedure:   WdtAppPeiEntryPoint
//
// Description: Turns on WDT during PEI phase according to requests made by
//              OS overclocking application (through WDT status) and BIOS
//              modules (through flash variable)
//
// Input:       *FfsHeader -  Pointer to Firmware File System file header.
//              *PeiServices  - General purpose services available to every PEIM.
//
// Output:      EFI_SUCCESS if everything's OK
//
//----------------------------------------------------------------------------
//<AMI_PHDR_END>
EFI_STATUS
WdtAppPeiEntryPoint (
  IN  EFI_FFS_FILE_HEADER *FfsHeader,
  IN  EFI_PEI_SERVICES    **PeiServices
  )
{
  EFI_STATUS                      Status;
  WDT_PPI                         *WdtPei;
  EFI_GUID                        WdtPersistentData = WDT_PERSISTENT_DATA_GUID;
  EFI_GUID                        gPeiReadOnlyVariablePpiGuid = EFI_PEI_READ_ONLY_VARIABLE_PPI_GUID;
  WDT_PERSISTENT_DATA             WdtStateData;
  EFI_PEI_READ_ONLY_VARIABLE_PPI  *ReadOnlyVariable;
  UINTN                           VariableSize;
  
  PEI_TRACE((-1, PeiServices, "(WdtApp) WdtAppPei Entry Point\n"));

  Status = (*PeiServices)->LocatePpi (
    PeiServices,
    &gPeiReadOnlyVariablePpiGuid,
    0, NULL,
    &ReadOnlyVariable
  );
  ASSERT_PEI_ERROR (PeiServices, Status);

  VariableSize = sizeof(WdtStateData);
  
  Status = ReadOnlyVariable->GetVariable (
    PeiServices,
    WDT_PERSISTENT_DATA_C_NAME,
    &WdtPersistentData,
    NULL,
    &VariableSize,
    &WdtStateData
  );

  if (EFI_ERROR(Status)) {
    WdtStateData.Enable = 0;
  }

  Status = (*PeiServices)->LocatePpi (
    PeiServices,
    &gWdtPpiGuid,
    0,
    NULL,
    &WdtPei
  );

  ASSERT_PEI_ERROR (PeiServices, Status);
 
  if (WdtPei->IsWdtRequired() == TRUE || WdtStateData.Enable == 1) {
    WdtPei->ReloadAndStart(WDT_TIMEOUT_BETWEEN_PEI_DXE);
  }
 
  return EFI_SUCCESS;
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

