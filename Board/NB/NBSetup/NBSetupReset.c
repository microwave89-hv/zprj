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
// $Header: /Alaska/BIN/Chipset/Intel/NorthBridge/Haswell/Intel SystemAgent NB Board/NBSetup/NBSetupReset.c 4     3/13/14 11:16p Dennisliu $
//
// $Revision: 4 $
//
// $Date: 3/13/14 11:16p $
//*************************************************************************
// Revision History
// ----------------
// $Log: /Alaska/BIN/Chipset/Intel/NorthBridge/Haswell/Intel SystemAgent NB Board/NBSetup/NBSetupReset.c $
// 
// 4     3/13/14 11:16p Dennisliu
// [TAG]           None
// [Category]      Improvement
// [Description]   Add new item "PrimaryDisplay" in NBSetupResetHook.
// [Files]         NBSetupReset.c
// 
// 3     10/14/12 12:38a Jeffch
// [TAG]          None
// [Severity]     Important
// [Description]  Follow Update by Mahobay.
// [Files]        NBPei.c, NBDxe.c;
// 
// 2     4/26/12 2:57a Yurenlai
// [TAG]           None
// [Category]      Improvement
// [Severity]      Important
// [Description]   Adjust Intel System Agent module the Setup item and
// Policy.
// [Description]   GetSetupData.c, NB.sdl, NB.sd, NB.uni, NBDxe.c,
// NBPEI.c,
//                 NBSetup.c, NBSetupReset.c, NbSetupData.h
// 
// 1     2/08/12 4:33a Yurenlai
// Intel Haswell/NB eChipset initially releases.
// 
//*************************************************************************
//<AMI_FHDR_START>
//
// Name:        NBSetupReset.c
//
// Description: North Bridge Setup Reset Rountines
//
//<AMI_FHDR_END>
//*************************************************************************
#include <EFI.h>
#include <Token.h>
#include <AmiLib.h>
#include <AmiDxeLib.h>
#include <Setup.h>
#if defined(RESET_RUNTIME_SERVICES_SUPPORT) && (RESET_RUNTIME_SERVICES_SUPPORT == 0)
#include <Protocol\PchReset\PchReset.h>
#else
#include <AmiCSPLib.h>
#include <PchRegsLpc.h>
#endif
//----------------------------------------------------------------------------
// Variable and External Declaration(s)
//----------------------------------------------------------------------------
// Variable Declaration(s)
static SETUP_DATA            gNewSetupData;
static SETUP_DATA            gOldSetupData;

// GUID Definition(s)
static EFI_GUID              gEfiSetupGuid = SETUP_GUID;


//<AMI_PHDR_START>
//----------------------------------------------------------------------------
// Procedure:	NBProcessEnterSetup
//
// Description:	This function is a hook called when TSE determines
//              that it has to load the boot options in the boot
//              order. This function is available as ELINK.
//
// Input:               VOID
//
// Output:              VOID
//
//----------------------------------------------------------------------------
//<AMI_PHDR_END>
VOID NBProcessEnterSetup(VOID)
{
  EFI_STATUS            Status;
  UINTN                 VariableSize;

  VariableSize = sizeof (SETUP_DATA);
  Status = pRS->GetVariable (
                  L"Setup",
                  &gEfiSetupGuid,
                  NULL,
                  &VariableSize,
                  &gOldSetupData
                  );

}

//<AMI_PHDR_START>
//----------------------------------------------------------------------------
// Procedure:	NBSetupResetHook
//
// Description:	This function is a hook called after some control 
//              modified in the setup utility by user. This
//              function is available as ELINK.
//
// Input:               VOID
//
// Output:              VOID
//
//----------------------------------------------------------------------------
//<AMI_PHDR_END>
VOID NBSetupResetHook(VOID)
{

  EFI_STATUS            Status;
  UINTN                 VariableSize;

  VariableSize = sizeof (SETUP_DATA);
  Status = pRS->GetVariable (
                  L"Setup",
                  &gEfiSetupGuid,
                  NULL,
                  &VariableSize,
                  &gNewSetupData
                  );
  if (!EFI_ERROR (Status)) {
      if ((gNewSetupData.EnableVtd != gOldSetupData.EnableVtd) ||
      (gNewSetupData.BdatAcpiTableSupport != gOldSetupData.BdatAcpiTableSupport) ||
      (gNewSetupData.PegGenx0 != gOldSetupData.PegGenx0) ||
      (gNewSetupData.PegGenx1 != gOldSetupData.PegGenx1) ||
      (gNewSetupData.PegGenx2 != gOldSetupData.PegGenx2) ||
      (gNewSetupData.ExitMode != gOldSetupData.ExitMode) ||
      (gNewSetupData.DmiGen2 != gOldSetupData.DmiGen2) ||
      (gNewSetupData.NBDmiAspm != gOldSetupData.NBDmiAspm) ||
      (gNewSetupData.NBDmiExtSync != gOldSetupData.NBDmiExtSync) ||
      (gNewSetupData.DetectNonComplaint != gOldSetupData.DetectNonComplaint) ||
      (gNewSetupData.AlwaysEnablePeg != gOldSetupData.AlwaysEnablePeg) ||
      (gNewSetupData.PowerDownMode0 != gOldSetupData.PowerDownMode0) ||
      (gNewSetupData.PrimaryDisplay != gOldSetupData.PrimaryDisplay) ||
      (gNewSetupData.PowerDownMode1 != gOldSetupData.PowerDownMode1)) {
          //
          // Powe Cycle Reset
          //
#if defined(RESET_RUNTIME_SERVICES_SUPPORT) && (RESET_RUNTIME_SERVICES_SUPPORT == 0)
          pRS->ResetSystem (PowerCycleReset, EFI_SUCCESS, 0, NULL);
#else
          SBLib_ExtResetSystem (SbResetFull);
#endif

      }
  }


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