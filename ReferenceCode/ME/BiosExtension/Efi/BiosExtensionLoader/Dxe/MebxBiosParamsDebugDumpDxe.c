/** @file
  Dump whole MEBX_BPF and serial out.

@copyright
  Copyright (c) 2012 Intel Corporation. All rights reserved This
  software and associated documentation (if any) is furnished
  under a license and may only be used or copied in accordance
  with the terms of the license. Except as permitted by such
  license, no part of this software or documentation may be
  reproduced, stored in a retrieval system, or transmitted in any
  form or by any means without the express written consent of
  Intel Corporation.

  This file contains an 'Intel Peripheral Driver' and uniquely
  identified as "Intel Reference Module" and is
  licensed for Intel CPUs and chipsets under the terms of your
  license agreement with Intel or your vendor.  This file may
  be modified by the user, subject to additional terms of the
  license agreement
**/

#if !defined(EDK_RELEASE_VERSION) || (EDK_RELEASE_VERSION < 0x00020000)
#include "EdkIIGlueDxe.h"
#include "BiosExtensionLoader.h"
#endif

/**
  Dump MEBx BIOS Params

  @param[in] MebxBiosParams       MEBx BIOS params

  @retval None
**/
VOID
DxeMebxBiosParamsDebugDump (
  IN MEBX_BPF                     *MebxBiosParams
  )
{
  DEBUG ((EFI_D_INFO, "\n------------------------ MebxBiosParams Dump Begin -----------------\n"));
  DEBUG ((EFI_D_INFO, " BpfVersion : 0x%x\n", MebxBiosParams->BpfVersion));
  DEBUG ((EFI_D_INFO, " CpuReplacementTimeout : 0x%x\n", MebxBiosParams->CpuReplacementTimeout));
  DEBUG ((EFI_D_INFO, " ActiveRemoteAssistanceProcess : 0x%x\n", MebxBiosParams->ActiveRemoteAssistanceProcess));
  DEBUG ((EFI_D_INFO, " CiraTimeout : 0x%x\n", MebxBiosParams->CiraTimeout));
  DEBUG ((EFI_D_INFO, " OemFlags : 0x%x\n", MebxBiosParams->OemFlags));
  DEBUG ((EFI_D_INFO, "MebxDebugFlags ---\n"));
  DEBUG ((EFI_D_INFO, " Port80 : 0x%x\n", MebxBiosParams->MebxDebugFlags.Port80));
  DEBUG ((EFI_D_INFO, " MeBiosSyncDataPtr : 0x%x\n", MebxBiosParams->MeBiosSyncDataPtr));
  DEBUG ((EFI_D_INFO, " UsbKeyDataStructurePtr : 0x%x\n", MebxBiosParams->UsbKeyDataStructurePtr));
  DEBUG ((EFI_D_INFO, "OemResolutionSettings ---\n"));
  DEBUG ((EFI_D_INFO, " MebxNonUiTextMode : 0x%x\n", MebxBiosParams->OemResolutionSettings.MebxNonUiTextMode));
  DEBUG ((EFI_D_INFO, " MebxUiTextMode : 0x%x\n", MebxBiosParams->OemResolutionSettings.MebxUiTextMode));
  DEBUG ((EFI_D_INFO, " MebxUiTextMode : 0x%x\n", MebxBiosParams->OemResolutionSettings.MebxGraphicsMode));
  DEBUG ((EFI_D_INFO, "\n------------------------ MebxBiosParams Dump End -------------------\n"));
}

